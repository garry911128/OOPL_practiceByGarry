#pragma once

namespace game_framework {
	class Menu {
	public:
		Menu();
		int tempselect;
		CMovingBitmap _Menu;
		CMovingBitmap _Arrow;
		void LoadBitmap();
		int _TotalScore;
		int _TheHightestScore;
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnShow();
		void OnShowText(CDC *pDC, CFont* &fp);
	};

}