﻿#include <vector>
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
	_X = 0;
	_Y = 0;
	_OriginAngle = 0; // 0 is east,1 south, 2 west,3 north
	_TurnAngle = 0;
	_Level = 1;
	_Life = 1;
	_LocationDistance = 16;
	_OffsetX = 0;
	_OffsetY = 0;
	_FrameTime = 0;
	_Frameindex = 0;
	_PointX = _X;
	_PointY = _Y;
	_MovementSpeed = 2;
	_AttackSpeedUP = false;
	_CanBreakIron = false;
	_DoubleAttack = false;
	_Tank.SetAnimation(1,true);
	//_Bullet.OnInit();
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
	if (_Life ==0)
	{
		return true;
	}
	return false;
}
void CTank::SetXY(int _x, int _y) {
	_X = _x;
	_Y = _y;
}
/*
void CTank::FireBullet() {
	bool temp;
	temp = _Bullet.BulletFly(_X, _Y);
}
*/
void CTank::Move(UINT nChar) {
	TurnFace(nChar);
	if (_OriginAngle == 0){
		_TurnAngle = 0;
		_OffsetX += _MovementSpeed;
		_X += _MovementSpeed;
	}
	if (_OriginAngle == 2){
		_TurnAngle = 2;
		_OffsetX -= _MovementSpeed;
		_X -= _MovementSpeed;
	}
	if (_OriginAngle == 3){
		_TurnAngle = 3;
		_OffsetY -= _MovementSpeed;
		_Y -= _MovementSpeed;
	}
	if (_OriginAngle == 1) {
		_TurnAngle = 1;
		_OffsetY += _MovementSpeed;
		_Y += _MovementSpeed;
	}
	Animation();
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
void CTank::TurnFace(UINT nChar) {
	if (nChar== VK_RIGHT){
		_TurnAngle = 0;
		_Tank.SetFrameIndexOfBitmap(_Frameindex);
	}
	else if (nChar == VK_LEFT){
		_TurnAngle = 2;
		_Tank.SetFrameIndexOfBitmap(_Frameindex);
	}
	else if (nChar == VK_UP) {
		_TurnAngle = 3;
		_Tank.SetFrameIndexOfBitmap(_Frameindex);
	}
	else if (nChar == VK_DOWN){
		_TurnAngle = 1;
		_Tank.SetFrameIndexOfBitmap(_Frameindex);
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

//void CTank::AnimationOnce() {
//	_Tank.ToggleAnimation();
//}