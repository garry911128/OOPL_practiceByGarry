#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <vector>
#include "CPlayer.h"

// Tank Child
using namespace game_framework;

CPlayer::CPlayer() : CTank(){
	_IfGetShip = false;
	_X = Width * 8 + 100;
	_Y = Height * 24;
	_PlayerScore = 0;
	_KillEnemyList = {};
	_OriginAngle = Up;
	_TurnAngle = Up;
	SetFaceDirection();
}
int CPlayer::GetPlayerScore() {
	return _PlayerScore;
}

void CPlayer::SpawnAfter5Second() {
	_Invicible = true;
}

void CPlayer::LoadBitmap() {
	_Tank.LoadBitmapByString({  "resources/Tank_Right_1.bmp" ,"resources/Tank_Right_2.bmp",
							    "resources/Tank_Left_1.bmp"  ,"resources/Tank_Left_2.bmp", 
								"resources/Tank_Top_1.bmp"   ,"resources/Tank_Top_2.bmp", 
								"resources/Tank_Bottom_1.bmp","resources/Tank_Bottom_2.bmp"},RGB(0,0,0));
	_Bullet.LoadBitmap();
}

void CPlayer::KillEnemy(int type) {
	_KillEnemyList.push_back(type);
	if (type == LightTank) {
		PlusPlayerScore(100);						
	}
	else if (type == QuickTank) {
		PlusPlayerScore(300);						
	}
	else if (type == ArmorTank) {					
		PlusPlayerScore(200);						
	}
	else if (type == HeavyTank) {					
		PlusPlayerScore(400);						
	}
}

void CPlayer::PlusPlayerScore(int score) {
	_PlayerScore += score;
}

void CPlayer::SetIfGetShip(bool Status) {
	_IfGetShip = Status;
}
bool CPlayer::GetIfGetShip() {
	return _IfGetShip;
}

void CPlayer::LevelUP() {
	if (_Level < 5) {
		_Level += 1;
		if (_Level == 2) {
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

