#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "./GameProps.h"
#include <string>

using namespace game_framework;
GameProps::GameProps() {
}
void GameProps::OnInit(int Type) {
	_Type = Type;
	_IfShow = false;
	string filename = "resources/Prop" + to_string(Type) + ".bmp";
	_Props.LoadBitmapByString({ filename }, RGB(0, 0, 0));
	_Props.SetTopLeft(100, 20);
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
	if (_IfShow) {
		_Props.ShowBitmap();
	}
}
