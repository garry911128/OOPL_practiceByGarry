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
	_OriginAngle = 90;
	_TurnAngle = 90;
	_Level = 1;
	_Life = 1;
	_OffsetX = 0;
	_OffsetY = 0;
	_PointX = _X;
	_PointY = _Y;
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
void CTank::Move(UINT nChar) {
	if (nChar == VK_RIGHT){
		_TurnAngle = 90;
		_OffsetX += 2;
		_X += 2;
	}
	else if (nChar == VK_LEFT){
		_TurnAngle = -90;
		_OffsetX -= 2;
		_X -= 2;
	}
	else if (nChar ==VK_UP){
		_TurnAngle = 0;
		_OffsetY -= 2;
		_Y -= 2;
	}
	else if (nChar == VK_DOWN) {
		_TurnAngle = 180;
		_OffsetY += 2;
		_Y += 2;
	}
	if (_TurnAngle != _OriginAngle) {
		LocationPoint(_OffsetX, _OffsetY);
		_OriginAngle = _TurnAngle;
		TurnFace();
	}


}

void CTank::TurnFace() {
	if (_OriginAngle == 90){
		_Tank.SetFrameIndexOfBitmap(0);
	}
	else if (_OriginAngle == -90){
		_Tank.SetFrameIndexOfBitmap(2);
	}
	else if (_OriginAngle == 0) {
		_Tank.SetFrameIndexOfBitmap(4);
	}
	else if (_OriginAngle == 180){
		_Tank.SetFrameIndexOfBitmap(6);
	}
}
void CTank::LocationPoint(int _x, int _y) {
	if (abs(_x) > 16){
		_PointX += _x;
		_OffsetX = 0;
	}
	if (abs(_y) > 16) {
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

void CTank::AnimationOnce() {
	_Tank.ToggleAnimation();
}