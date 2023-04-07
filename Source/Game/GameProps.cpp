﻿#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "./GameProps.h"
#include <string>
#include <random>

using namespace game_framework;
GameProps::GameProps() {
}
void GameProps::OnInit() {
	vector<string> filename;
	for (int i = 0; i < 8; i++) {
		filename.push_back("resources/Prop" + to_string(i) + ".bmp");
	}
	_Props.LoadBitmapByString( filename , RGB(0, 0, 0));
}
void GameProps::SetGameProps() {
	_IfShow = true;
	_IfExist = true;
	_IfCountDown = false;
	_IfTouched = false;
	//_Type = rand() % 8;
	_Type = 6;
	_Props.SetFrameIndexOfBitmap(_Type);
	_X = 100 + rand() % 768;
	_Y = rand() % 768;
	_Props.SetTopLeft(_X,_Y);
}

bool GameProps::GetIfTouched() {
	return _IfTouched;
}
int GameProps::GetType() {
	return _Type;
}
void GameProps::SetIfShow(bool Status) {
	_IfShow = Status;
}
bool GameProps::GetIfShow() {
	return _IfShow;
}

void GameProps::SetIfExist(bool IfExist) {
	_IfExist = IfExist;
}
bool GameProps::GetIfExist() {
	return _IfExist;
}
void GameProps::OnShow() {
	if (_IfShow && _IfExist) {
		_Props.ShowBitmap();
	}
}

CMovingBitmap GameProps::GetPropBitmap() {
	return _Props;
}

int GameProps::IfEffectExit() { // 1 is effect,-1 is no effect, 0 is 19second
	int EffectTime = 0;
	if (!_IfCountDown) {
		_IfCountDown = true;
		_IfTouched = true;
		_StartTime = clock();
	}
	if (_Type == 5) {
		EffectTime = 21000;
	}
	if (_Type == 3) {
		EffectTime = 10000;
	}
	if (_Type == 5 && EffectTime > clock() - _StartTime && clock() - _StartTime  >= EffectTime - 3000) {
		return 0;
	}
	if (clock() - _StartTime >= EffectTime) {
		_IfCountDown = false;
		_IfTouched = false;
		_Type = -1;
		return -1;
	}
	return 1;
}
