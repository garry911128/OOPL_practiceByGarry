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
}

int Menu::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	const char KEY_UP = 0x26;
	const char KEY_DOWN = 0x28;
	const char KEY_ENTER = 0x0D;

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
		return tempselect;
	 }
	_Arrow.SetTopLeft(380, 500 + 70 * tempselect);
	return -1;
}

void Menu::LoadBitMap() {
	_Menu.LoadBitmapByString({ "resources/LobbyMenu.bmp" });
	_Menu.SetTopLeft(100, 0);
	_Arrow.LoadBitmapByString({ "resources/LobbyArrow.bmp" });
	_Arrow.SetTopLeft(380, 500);
}
void Menu::OnShow() {
	_Menu.ShowBitmap();
	_Arrow.ShowBitmap();
}
void Menu::OnShowText(CDC *pDC, CFont* &fp) {

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(180, 180, 180));
	CTextDraw::ChangeFontLog(pDC, 40, "STZhongsong", RGB(180, 180, 180));
	CTextDraw::Print(pDC, 200, 60, to_string(_TotalScore).c_str());

}
