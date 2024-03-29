﻿#include <vector>
#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <random>
#include "Enemy.h"

// Tank Child
using namespace game_framework;

Enemy::Enemy() : CTank() {
	_EnemyType = 0;
	_X = Width * 14 + 100;
	_Y = Height * 0;
	_OriginAngle = Down;
	_TurnAngle = Down;
	_NowGrid = { (_X - 100) / Width, _Y / Height };
	_TimeStart = clock();
	_TimeFinish = clock();
	SetFaceDirection();
}
int Enemy::GetEnemyScore() {
	return _EnemyScore;
}

bool Enemy::isEnemyHaveItem() {
	return _EnemyHaveItem;
}

void Enemy::SetEnemyHaveItem() {
	_EnemyHaveItem = true;
}

void Enemy::SetEnemyInit() {
	//_X = Width * 14 + 100;
	//_Y = Height * 0;
	//_Life = 1;
	//_FrameTime = 0;
	if (_EnemyType == LightTank){
		_EnemyScore = 100;						// 坦克分數
	}
	else if (_EnemyType == QuickTank) {
		_AttackSpeedUP = true;					// 射速
		_EnemyScore = 300;						// 坦克分數
	}
	else if (_EnemyType == ArmorTank) {
		_MovementSpeed = 4;						// 移動速度
		_EnemyScore = 200;						
	}
	else if (_EnemyType == HeavyTank) {
		_Life = 4;								// 生命
		_EnemyScore = 400;						
	}
	//SetFaceDirection();
}
void Enemy::SetEnemyType(int num) {
	_EnemyType = num;
}
void Enemy::SetOriginAngle(int direction) {
	_OriginAngle = direction;
}
void Enemy::EnemyRandomDirection(){
	_RandomDirection = rand() % 4;		// 隨機移動四個方向
	_RandomMoveTime = rand() % 5 + 1;	// 移動時間 1~6sec
	_TimeFinish = clock();
	if ((_TimeFinish - _TimeStart) / CLOCKS_PER_SEC > _RandomMoveTime) {	// > :因為要播放重生動畫
		switch (_RandomDirection)
		{
		case Right:
			TurnFace(VK_RIGHT);
			break;
		case Up:
			TurnFace(VK_UP);
			break;
		case Down:
			TurnFace(VK_DOWN);
			break;
		case Left:
			TurnFace(VK_LEFT);
			break;
		}
		_TimeStart = clock();			// 重新開始計時
	}
}
void Enemy::LoadBitmap() {
	if (_EnemyType == LightTank){
		_Tank.LoadBitmapByString({  "resources/Enemy_LightTank_Right1.bmp" ,"resources/Enemy_LightTank_Right2.bmp",
									"resources/Enemy_LightTank_Left1.bmp"  ,"resources/Enemy_LightTank_Left2.bmp",
									"resources/Enemy_LightTank_Top1.bmp"   ,"resources/Enemy_LightTank_Top2.bmp",
									"resources/Enemy_LightTank_Bottom1.bmp","resources/Enemy_LightTank_Bottom2.bmp" }, RGB(0, 0, 0));
	}
	else if (_EnemyType == QuickTank){
		_Tank.LoadBitmapByString({ "resources/Enemy_QuickTank_Right1.bmp" ,"resources/Enemy_QuickTank_Right2.bmp",
									"resources/Enemy_QuickTank_Left1.bmp"  ,"resources/Enemy_QuickTank_Left2.bmp",
									"resources/Enemy_QuickTank_Top1.bmp"   ,"resources/Enemy_QuickTank_Top2.bmp",
									"resources/Enemy_QuickTank_Bottom1.bmp","resources/Enemy_QuickTank_Bottom2.bmp" }, RGB(0, 0, 0));
	}
	else if (_EnemyType == ArmorTank) {
		_Tank.LoadBitmapByString({ "resources/Enemy_ArmorTank_Right1.bmp" ,"resources/Enemy_ArmorTank_Right2.bmp",
									"resources/Enemy_ArmorTank_Left1.bmp"  ,"resources/Enemy_ArmorTank_Left2.bmp",
									"resources/Enemy_ArmorTank_Top1.bmp"   ,"resources/Enemy_ArmorTank_Top2.bmp",
									"resources/Enemy_ArmorTank_Bottom1.bmp","resources/Enemy_ArmorTank_Bottom2.bmp" }, RGB(0, 0, 0));
	}
	else if (_EnemyType == HeavyTank) {
		_Tank.LoadBitmapByString({ "resources/Enemy_HeavyTank_Right1.bmp" ,"resources/Enemy_HeavyTank_Right2.bmp",
									"resources/Enemy_HeavyTank_Left1.bmp"  ,"resources/Enemy_HeavyTank_Left2.bmp",
									"resources/Enemy_HeavyTank_Top1.bmp"   ,"resources/Enemy_HeavyTank_Top2.bmp",
									"resources/Enemy_HeavyTank_Bottom1.bmp","resources/Enemy_HeavyTank_Bottom2.bmp" }, RGB(0, 0, 0));
	}
	_Bullet.LoadBitmap();
}
//void Enemy::EnemyRespawn(int type) {
//	SetEnemyType(type);
//	SetEnemyInit();
//	//SetIfBattle(true);
//	LoadBitmap();
//}