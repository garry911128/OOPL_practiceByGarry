#include "stdafx.h"
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
	//_Type = rand() % 8;
	_Type = 5;
	_Props.SetFrameIndexOfBitmap(_Type);
	_X = 100 + rand() % 768;
	_Y = rand() % 768;
	_Props.SetTopLeft(_X,_Y);
}

void GameProps::SetPropDisapear() {
	_Type = -1;
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
void GameProps::OnShow() {
	if (_IfShow && _Type != -1) {
		_Props.ShowBitmap();
	}
}
int GameProps::GetPropLeftX() {
	return _X;
}
int GameProps::GetPropRightX() {
	return _X + _Props.GetWidth();
}
int GameProps::GetPropTopY() {
	return _Y;
}
int GameProps::GetPropDownY() {
	return _Y + _Props.GetHeight();
}
CMovingBitmap GameProps::GetPropBitmap() {
	return _Props;
}