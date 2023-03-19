#include <vector>
#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "CTank.h"

// Tank Parent
using namespace game_framework;

CTank::CTank():Width(32), Height(32) {
	_X = Width*8+100;
	_Y = Height*24;
	_Level = 1;								// 等級
	_Life = 1;								// 生命
	//_FrontX =0;								// 面對方向的前方格子X座標
	//_FrontY =0;								// 面對方向的前方格子Y座標
	_OriginAngle = Up;						// 面對角度 0 is east,1 south, 2 west,3 north
	_TurnAngle = Up;							// 轉向角度
	_FrameTime = 0;							// 計時器
	_Frameindex = 4;						// 動畫偵 (0 is east,1 south, 2 west,3 north)*2
	_FrameSecond = 3;						// 動畫變換速度
	_LocationDistance = Height;				// 定位點距離
	_OffsetX = 0;							// 偏移X
	_OffsetY = 0;							// 偏移Y
	_PointX = (_X - 100) / Width;			// 轉換定位X
	_PointY = (_Y / Height);				// 轉換定位Y
	_MovementSpeed = 2;						// 移動速度
	_AttackSpeedUP = false;
	_CanBreakIron = false;
	_DoubleAttack = false;
	_Tank.SetAnimation(1,true);
	_IfFire = false;
	_FrontXY = { {0,0},{0,0} };
	//_Bullet.LoadBitmap();
}
bool CTank::GetIfFire() {
	return _IfFire;
}
int CTank::GetX1(){
	return _X;
}
int CTank::GetY1() {
	return _Y;
}
int CTank::GetOriginAngle() {
	return _OriginAngle;
}
bool CTank::isBreak() {
	if (_Life ==0){
		return true;
	}
	return false;
}
void CTank::SetXY(int _x, int _y) {
	_X = _x;
	_Y = _y;
}

void CTank::FireBullet() {
	if (clock() - _Last_time >= 10) {
		if (_OriginAngle == Right || _OriginAngle == Left) {
			_Bullet.SetBulletFire(_X, _Y + 25, _OriginAngle);
		}
		else {
			_Bullet.SetBulletFire(_X + 25, _Y, _OriginAngle);
		}
		_Last_time = clock();
		_IfFire = _Bullet.GetAlreadyFire();
	}
}

void CTank::Move() {
	if (_OriginAngle == Right){
		_OffsetX += _MovementSpeed;
		_X += _MovementSpeed;
	}
	if (_OriginAngle == Left){
		_OffsetX -= _MovementSpeed;
		_X -= _MovementSpeed;
	}
	if (_OriginAngle == Up){
		_OffsetY -= _MovementSpeed;
		_Y -= _MovementSpeed;
	}
	if (_OriginAngle == Down) {
		_OffsetY += _MovementSpeed;
		_Y += _MovementSpeed;
	}
	if (abs(_OffsetX) == _LocationDistance) {
		if (_OffsetX > 0) _PointX += 1;
		else _PointX -= 1;
	}
	if (abs(_OffsetY) == _LocationDistance) {
		if(_OffsetY>0) _PointY += 1;
		else _PointY -= 1;
	}
	if (abs(_OffsetX) == Width * 2)_OffsetX = 0;
	if (abs(_OffsetY) == Height * 2)_OffsetY = 0;
}
void CTank::TurnFace(UINT nChar) {
	if (nChar == VK_RIGHT) {
		_TurnAngle = Right;
	}
	else if (nChar == VK_LEFT) {
		_TurnAngle = Left;
	}
	else if (nChar == VK_UP) {
		_TurnAngle = Up;
	}
	else if (nChar == VK_DOWN) {
		_TurnAngle = Down;
	}
	if (_TurnAngle != _OriginAngle) {
		LocationPoint(_OffsetX, _OffsetY);
		_OriginAngle = _TurnAngle;
		if (_OriginAngle == Right) {
			_Frameindex = 0;
		}
		else if (_OriginAngle == Left) {
			_Frameindex = 2;
		}
		else if (_OriginAngle == Up) {
			_Frameindex = 4;
		}
		else if (_OriginAngle == Down) {
			_Frameindex = 6;
		}
		_FrameTime= 0;
	}
	_Tank.SetFrameIndexOfBitmap(_Frameindex);
}
void CTank::Animation() {
	if (_FrameTime%_FrameSecond==0){
		if (_Frameindex%2==0){
			_Tank.SetFrameIndexOfBitmap(_Frameindex + 1);
			_Frameindex += 1;
		}
		else {
			_Tank.SetFrameIndexOfBitmap(_Frameindex - 1);
			_Frameindex -= 1;
		}
	}
	_FrameTime += 1;
}
void CTank::LocationPoint(int _x, int _y) {
	/*if (abs(_x) > _LocationDistance){
		_PointX += _x / Width;
	}
	if (abs(_y) > _LocationDistance) {
		_PointY += _y / Height;
	}*/
	_OffsetX = 0;
	_OffsetY = 0;
	SetXY(_PointX*Width+100, _PointY*Height);
}

void CTank::OnShow() {
	_Tank.SetFrameIndexOfBitmap(_Frameindex);
	_Tank.SetTopLeft(_X, _Y);
	_Tank.ShowBitmap();
	_Bullet.OnShow();
}

void CTank::LevelUP() {
	if (_Level <5){
		_Level += 1;
		if (_Level == 2){
			_AttackSpeedUP = true;
		}
		else if (_Level == 3) {
			_DoubleAttack = true;
		}
		else if (_Level == 4) {
			_CanBreakIron = true;
		}
	}
}
void CTank::TankFront() {		// ./resource/TankFrontAxis.png
	if (_OriginAngle == Right) {
		_FrontXY[0][0] = _X + Width * 2;
		_FrontXY[0][1] = _Y + Height / 2;
		_FrontXY[1][0] = _X + Width * 2;
		_FrontXY[1][1] = _Y + Height * 3 / 2;
	}
	else if (_OriginAngle == Left) {
		_FrontXY[0][0] = _X ;
		_FrontXY[0][1] = _Y + Height / 2;
		_FrontXY[1][0] = _X ;
		_FrontXY[1][1] = _Y + Height * 3 / 2;
	}
	else if (_OriginAngle == Up) {
		_FrontXY[0][0] = _X + Width / 2;
		_FrontXY[0][1] = _Y ;
		_FrontXY[1][0] = _X + Width * 3 / 2;
		_FrontXY[1][1] = _Y ;
	}
	else if (_OriginAngle == Down) {
		_FrontXY[0][0] = _X + Width / 2;
		_FrontXY[0][1] = _Y + Height * 2;
		_FrontXY[1][0] = _X + Width * 3 / 2;
		_FrontXY[1][1] = _Y + Height * 2;
	}
}
vector<vector<int>> CTank::GetTankFront(){
	return _FrontXY;
}
vector<vector<int>> CTank::GetBulletPlace() {
	return _Bullet._GetNowPlace();
}
void CTank::SetBulletStatus(bool Status) {
	_Bullet.SetBulletAlreadyFire(Status);
}
void CTank::SetIfFire(bool Status) {
	_IfFire = Status;
}
int CTank::GetBulletDirection() {
	return _Bullet.GetDirection();
}
int CTank::GetHeight() {
	return _Tank.GetHeight();
}
int CTank::GetWidth() {
	return _Tank.GetWidth();
}
int CTank::GetBulletX() {
	return _Bullet._GetNowPlace()[0][0];
}
int CTank::GetBulletY() {
	return _Bullet._GetNowPlace()[0][1];
}
int CTank::GetBulletHeight() {
	return _Bullet.GetHeight();
}
int CTank::GetBulletWidth() {
	return _Bullet.GetWidth();
}
//CMovingBitmap CTank::GetTankBitmap() {
//	return _Tank;
//}
//void CTank::AnimationOnce() {
//	_Tank.ToggleAnimation();
//}
//void CTank::Attacke() {
//	if (_OriginAngle == 90) {
//		/*spawn Bullet
//		Bullet.setXY(_X+_Width,_Y+_Height/2);
//		*/
//	}
//	else if (_OriginAngle == -90) {
//		
//	}
//	else if (_OriginAngle == 0) {
//		
//	}
//	else {
//		
//	}
//}

