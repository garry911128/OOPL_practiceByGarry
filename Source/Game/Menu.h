#pragma once

namespace game_framework {
	class Menu {
	public:
		Menu();
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnShow();
		void OnShowText(CDC *pDC, CFont* &fp);
		void LoadBitMap();
	private:
		int tempselect; //option arrow locate (temp,not the final location)
		int _TotalScore;
		int _TheHightestScore;
		CMovingBitmap _Menu;
		CMovingBitmap _Arrow;
	};

}