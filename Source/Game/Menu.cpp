#include "stdafx.h"
#include "../Core/Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "./Menu.h"
#include <string>

using namespace game_framework;

Menu::Menu() {
	_TotalScore = 0;
	_TheHightestScore = 0;
	tempselect = 0;
	finalselect = 0;
	_MenuType = 0;

	_RaiseDelay = 10;
	_RaiseSpeed = 10;
	_Menuing = false;
	_Selecting = false;
	_ChoosingStage = false;
	_Animationing = false;
	_Battleing = false;
}

void Menu::SetSelecting(bool select) {
	_Selecting = select;
}
bool Menu::GetSelecting() {
	return _Selecting;
}

void Menu::SetMenuing(bool menu) {
	_Menuing = menu;
}
bool Menu::GetMenuing() {
	return _Menuing;
}
int Menu::GetMenuY(int type) {
	if (type == Lobby) {
		return _Menu.GetTop();
	}
	else if (type == ChooseStage) {
		return _ChooseStageMenuTop.GetTop();
	}
	return 0;
}
void Menu::SetLobbyRaise() {
	_MenuType = Lobby;
	_Menuing = true;
	_Animationing = true;
	if (clock() - _Last_time >= _RaiseDelay && _Animationing) {
		_Menu.SetTopLeft(100, _Menu.GetTop() - _RaiseSpeed);
		_Last_time = clock();
	}
}

void Menu::SetChoosingStageanimation() {
	_MenuType = ChooseStage;
	_ChoosingStage = true;
	_Animationing = true;
	if (clock() - _Last_time >= _RaiseDelay) {
		_ChooseStageMenuTop.SetTopLeft(0,_ChooseStageMenuTop.GetTop() + _RaiseSpeed + 15);
		_ChooseStageMenuDown.SetTopLeft(0,_ChooseStageMenuDown.GetTop() - _RaiseSpeed - 15);
		_Last_time = clock();
	}
}
bool Menu::GetChoosingStage() {
	return _ChoosingStage;
}
void Menu::SetChoosingStage(bool choosingstage) {
	_ChoosingStage = choosingstage;
}

bool Menu::GetAnimationing() {
	return _Animationing;
}
void Menu::SetAnimationing(bool Status) {
	_Animationing = Status;
}

void Menu::SetBattleing(bool Status) {
	_Battleing = Status;
}
int Menu::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	const char KEY_UP = 0x26;
	const char KEY_DOWN = 0x28;
	const char KEY_ENTER = 0x0D;
	const char Key_Z = 0x5A;
	const char Key_X = 0x58;

	if (_Animationing == true && _MenuType == Lobby) {
		_Menu.SetTopLeft(100, 0);
		_Animationing = false;
		return -1;
	}
	if (_Selecting && _MenuType == Lobby) {
		if (nChar == KEY_DOWN) {
			tempselect += 1;
			tempselect %= 2;
		}
		else if (nChar == KEY_UP) {
			tempselect -= 1;
			tempselect += 2;
			tempselect %= 2;
		}
		else if (nChar == KEY_ENTER) {
			_ChooseStageMenuTop.SetTopLeft(0, -450);
			_ChooseStageMenuDown.SetTopLeft(0, 900);
			_Selecting = false;
			_Menuing = false;
			_Menu.SetTopLeft(100, 900);
			finalselect = tempselect;
			tempselect = 0;
			return finalselect;
		}
		_Arrow.SetTopLeft(380, 500 + 70 * tempselect);
		return -1;
	}
	else if (_Selecting && _MenuType == ChooseStage) {
		if (nChar == Key_Z) {
			tempselect -= 1;
			if (tempselect < 0) {
				tempselect += 1;
			}
		}
		else if (nChar == Key_X) {
			tempselect += 1;
			if (tempselect > 34) {
				tempselect -= 1;
			}
		}
		else if (nChar == KEY_ENTER) {
			_ChoosingStage = false;
			finalselect = tempselect + 1;
			return finalselect;
		}
	}
	return 0;
}

void Menu::LoadBitMap() {
	_Menu.LoadBitmapByString({ "resources/LobbyMenu.bmp" });
	_Menu.SetTopLeft(100, 900);
	_Arrow.LoadBitmapByString({ "resources/LobbyArrow.bmp" });
	_Arrow.SetTopLeft(380, 500);
	_BattleMenuGray.LoadBitmapByString({ "resources/GrayScreen_Background.bmp" });
	_BattleMenuGray.SetTopLeft(0, 0);
	_ChooseStageMenuTop.LoadBitmapByString({ "resources/GrayScreen.bmp" });
	_ChooseStageMenuTop.SetTopLeft(0, -450);
	_ChooseStageMenuDown.LoadBitmapByString({ "resources/GrayScreen.bmp" });
	_ChooseStageMenuDown.SetTopLeft(0, 900);
}
void Menu::OnShow() {

	if (_MenuType == Lobby) {
		if (_Menuing) {
			_Menu.ShowBitmap();
		}
		if (_Selecting) {
			_Arrow.ShowBitmap();
		}
	}
	if (_ChoosingStage && _MenuType == ChooseStage) {
		_ChooseStageMenuTop.ShowBitmap();
		_ChooseStageMenuDown.ShowBitmap();
	}
	if (_Battleing) {
		_BattleMenuGray.ShowBitmap();
	}
}
void Menu::OnShowText(CDC *pDC, CFont* &fp) {

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(180, 180, 180));
	CTextDraw::ChangeFontLog(pDC, 40, "STZhongsong", RGB(180, 180, 180));
	if (_Menuing && _Selecting) {
		CTextDraw::Print(pDC, 200, 60, to_string(_TotalScore).c_str());
	}
	if (_ChoosingStage && _Selecting) {
		CTextDraw::Print(pDC, 600, 400, string("Stage") + to_string(tempselect+1).c_str());
	}
}
