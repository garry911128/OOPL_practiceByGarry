﻿#include "stdafx.h"
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
void CPlayer::FireBullet(int BulletOrder) {
	if (BulletOrder == 1) {
		if (_OriginAngle == Right || _OriginAngle == Left) {
			_Bullet.SetBulletFire(_X, _Y + 25, _OriginAngle, _BulletFlySpeed);
		}
		else {
			_Bullet.SetBulletFire(_X + 25, _Y, _OriginAngle, _BulletFlySpeed);
		}
		_IfFire = true;
	}
	else if(BulletOrder == 2){
		if (_OriginAngle == Right || _OriginAngle == Left) {
			_SecondBullet.SetBulletFire(_X, _Y + 25, _OriginAngle, _BulletFlySpeed);
		}
		else {
			_SecondBullet.SetBulletFire(_X + 25, _Y, _OriginAngle, _BulletFlySpeed);
		}
		_IfSecondFire = true;
	}
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

void CPlayer::SetBulletStatus(int BulletOrder, bool Status) { // 1 is first bullet , 2 is second bullet
	if (BulletOrder == 1) {
		if (_Bullet.GetAlreadyFire() == true && Status == false) {
			_Bullet.SetIfBoom(true);
		}
		_Bullet.SetBulletAlreadyFire(Status);
	}
	else if (BulletOrder == 2) {
		if (_SecondBullet.GetAlreadyFire() == true && Status == false) {
			_SecondBullet.SetIfBoom(true);
		}
		_SecondBullet.SetBulletAlreadyFire(Status);
	}
}
void CPlayer::SetIfFire(int FireOrder, bool Status) {
	if (FireOrder == 1) {
		_IfFire = Status;
	}
	else if(FireOrder == 2){
		_IfSecondFire = Status;
	}
}
void CPlayer::SetIfGetShip(bool Status) {
	_IfGetShip = Status;
}
bool CPlayer::GetIfFire(int FireOrder) {
	if (FireOrder == 1) {
		return _IfFire;
	}
	else if (FireOrder == 2) {
		return _IfSecondFire;
	}
	return false;
}
bool CPlayer::GetIfGetShip() {
	return _IfGetShip;
}
void CPlayer::SetMoveOnIce(bool IfOnIce) {
	
}
void CPlayer::LevelUP() {
	if (_Level < 4) {
		_Level += 1;
		if (_Level == 2) {
			_AttackSpeedUP = true;
			_BulletFlySpeed = 24;
		}
		else if (_Level == 3) {
			_DoubleAttack = true;
		}
		else if (_Level == 4) {
			_CanBreakIron = true;
		}
	}
}

void CPlayer::OnShow() {
	if (_IfBattle && !isBreak()) {
		if (!GetSpawnAnimationDone()) {
			CTank::LoadBitmap();
			ShowSpawnAnimation();
		}
		else {
			_Tank.SetFrameIndexOfBitmap(_Frameindex);
			_Tank.SetTopLeft(_X, _Y);
			_Tank.ShowBitmap();
		}
		_Bullet.OnShow();
	}
	else if (isBreak() && !_isTankBrokenAnimationDone) {
		_TankBrokenAnimation.SetTopLeft(_X, _Y);
		TankbeHit();
	}
}


