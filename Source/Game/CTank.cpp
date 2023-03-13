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
	_FrontX =0;								// 面對方向的前方格子X座標
	_FrontY =0;								// 面對方向的前方格子Y座標
	_OriginAngle = 3;						// 面對角度 0 is east,1 south, 2 west,3 north
	_TurnAngle = 3;							// 轉向角度
	_FrameTime = 0;							// 計時器
	_Frameindex = 4;						// 動畫偵 (0 is east,1 south, 2 west,3 north)*2
	_FrameSecond = 3;						// 動畫變換速度
	_LocationDistance = Height / 2;			// 定位點距離
	_OffsetX = 0;							// 偏移X
	_OffsetY = 0;							// 偏移Y
	_PointX = _X;							// 轉換定位X
	_PointY = _Y;							// 轉換定位Y
	_MovementSpeed = 2;						// 移動速度
	_AttackSpeedUP = false;
	_CanBreakIron = false;
	_DoubleAttack = false;
	//_Tank.SetAnimation(1,true);
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
int CTank::GetFrontX() {
	if (_FrontX < 0){
		return 0;
	}
	else if (_FrontX > 25){
		return 25;
	}
	return _FrontX;
}
int CTank::GetFrontY() {
	if (_FrontY < 0) {
		return 0;
	}
	else if (_FrontY > 25) {
		return 25;
	}
	return _FrontY;
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
void CTank::Move() {
	if (_OriginAngle == 0){
		_OffsetX += _MovementSpeed;
		_X += _MovementSpeed;
	}
	if (_OriginAngle == 2){
		_OffsetX -= _MovementSpeed;
		_X -= _MovementSpeed;
	}
	if (_OriginAngle == 3){
		_OffsetY -= _MovementSpeed;
		_Y -= _MovementSpeed;
	}
	if (_OriginAngle == 1) {
		_OffsetY += _MovementSpeed;
		_Y += _MovementSpeed;
	}
}
void CTank::TurnFace(UINT nChar) {
	if (nChar == VK_RIGHT) {
		_TurnAngle = 0;
	}
	else if (nChar == VK_LEFT) {
		_TurnAngle = 2;
	}
	else if (nChar == VK_UP) {
		_TurnAngle = 3;
	}
	else if (nChar == VK_DOWN) {
		_TurnAngle = 1;
	}
	if (_TurnAngle != _OriginAngle) {
		LocationPoint(_OffsetX, _OffsetY);
		_OriginAngle = _TurnAngle;
		if (_OriginAngle == 0) {
			_Frameindex = 0;
		}
		else if (_OriginAngle == 2) {
			_Frameindex = 2;
		}
		else if (_OriginAngle == 3) {
			_Frameindex = 4;
		}
		else if (_OriginAngle == 1) {
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
	if (abs(_x) > _LocationDistance){
		_PointX += _x;
		_OffsetX = 0;
	}
	if (abs(_y) > _LocationDistance) {
		_PointY += _y;
		_OffsetY = 0;
	}
	SetXY(_PointX, _PointY);
}

void CTank::OnShow() {
	_Tank.SetFrameIndexOfBitmap(_Frameindex);
	_Tank.SetTopLeft(_X, _Y);
	_Tank.ShowBitmap();
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
void CTank::TankFront(int grid) {		// ./resource/TankFrontAxis.png
	int Cal_X = (_X - 100) / Width;
	int Cal_Y = _Y / Height;
	if (_OriginAngle == 0) {
		_FrontX = Cal_X + 2;
		_FrontY = Cal_Y + grid;
	}
	else if (_OriginAngle == 2) {
		_FrontX = Cal_X + grid;
		_FrontY = Cal_Y;
	}
	else if (_OriginAngle == 3) {
		_FrontX = Cal_X + grid;
		_FrontY = Cal_Y;
	}
	else if (_OriginAngle == 1) {
		_FrontX = Cal_X + grid;
		_FrontY = Cal_Y +2;
	}
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