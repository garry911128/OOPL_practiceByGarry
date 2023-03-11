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

CTank::CTank() {
	_X = 256+100;
	_Y = 768;
	_OriginAngle = 3; // 0 is east,1 south, 2 west,3 north
	_TurnAngle = 3;
	_Level = 1;
	_Life = 1;
	_LocationDistance = 16;
	_OffsetX = 0;
	_OffsetY = 0;
	_FrameTime = 0;
	_Frameindex = 4; // (0 is east,1 south, 2 west,3 north)*2
	_PointX = _X;
	_PointY = _Y;
	_MovementSpeed = 2;
	_AttackSpeedUP = false;
	_CanBreakIron = false;
	_DoubleAttack = false;
	_Tank.SetAnimation(1,true);
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
	if (_FrameTime%2==0){
		_Tank.SetFrameIndexOfBitmap(_Frameindex + 1);
		_Frameindex += 1;
	}
	else {
		_Tank.SetFrameIndexOfBitmap(_Frameindex - 1);
		_Frameindex -= 1;
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
void CTank::Attacke() {
	if (_OriginAngle == 90) {
		/*spawn Bullet
		Bullet.setXY(_X+_Width,_Y+_Height/2);
		*/
	}
	else if (_OriginAngle == -90) {
		
	}
	else if (_OriginAngle == 0) {
		
	}
	else {
		
	}
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
//CMovingBitmap CTank::GetTankBitmap() {
//	return _Tank;
//}
//void CTank::AnimationOnce() {
//	_Tank.ToggleAnimation();
//}