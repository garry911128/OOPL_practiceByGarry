#include <vector>
#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "Enemy.h"

// Tank Child
using namespace game_framework;

Enemy::Enemy() : CTank() {
	_EnemyType = 0;
	_X = Width * 12 + 100;
	_Y = Height * 0;
	_OriginAngle = Down;
	_TurnAngle = Down;
	SetFaceDirection();
}
int Enemy::GetEnemyScore() {
	return _EnemyScore;
}

bool Enemy::isEnemuHaveItem() {
	return _EnemyHaveItem;
}

void Enemy::SetEnemyHaveItem() {
	_EnemyHaveItem = true;
}

void Enemy::SetEnemyInit() {
	if (_EnemyType == LightTank){
		_EnemyScore = 100;						// 坦克分數
	}
	else if (_EnemyType == QuickTank) {
		_AttackSpeedUP = true;
		_EnemyScore = 300;						// 坦克分數
	}
	else if (_EnemyType == ArmorTank) {
		_MovementSpeed = 4;						// 移動速度
		_EnemyScore = 200;						// 坦克分數
	}
	else if (_EnemyType == HeavyTank) {
		_Life = 4;								// 生命
		_EnemyScore = 400;						// 坦克分數
	}
}

void Enemy::SetEnemyType(int num) {
	_EnemyType = num;
}
void Enemy::SetOriginAngle(int direction) {
	_OriginAngle = direction;
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