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
	_X = 0;
	_Y = 0;
	_Angle = 0;
	_Level = 1;
	_Life = 1;
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
		_Angle = 90;
		TurnFace();
		_X += 2;
	}
	else if (nChar == VK_LEFT){
		_Angle = -90;
		TurnFace();
		_X -= 2;
	}
	else if (nChar ==VK_UP){
		_Angle = 0;
		TurnFace();
		_Y += 2;
	}
	else{
		_Angle = 180;
		TurnFace();
		_Y -= 2;
	}
}

void CTank::TurnFace() {
	if (_Angle == 90){
		_Tank.SetFrameIndexOfBitmap(0);
	}
	else if (_Angle == -90){
		_Tank.SetFrameIndexOfBitmap(2);
	}
	else if (_Angle == 0) {
		_Tank.SetFrameIndexOfBitmap(4);
	}
	else{
		_Tank.SetFrameIndexOfBitmap(6);
	}
}

void CTank::Attacke() {
	if (_Angle == 90) {
		/*spawn Bullet
		Bullet.setXY(_X+_Width,_Y+_Height/2);
		*/
	}
	else if (_Angle == -90) {
		
	}
	else if (_Angle == 0) {
		
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