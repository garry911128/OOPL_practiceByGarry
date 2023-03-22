#pragma once

namespace game_framework {
	class Menu {
	public:
		Menu();
		void SetLobbyRaise();
		int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnShow();
		void OnShowText(CDC *pDC, CFont* &fp);

		void SetSelecting(bool select);
		bool GetSelecting();
		void SetMenuing(bool menu);
		bool GetMenuing();
		int GetMenuY(int type); // type = 0 Lobby Menu,type = 1 GrayScreen(Top) 

		void SetChoosingStageanimation();
		bool GetChoosingStage();
		void SetChoosingStage(bool choosingstage);

		bool GetAnimationing();
		void SetAnimationing(bool Status);

		void SetBattleing(bool Status);

		void LoadBitMap();
	private:
		enum MenuType{
			Lobby,ChooseStage
		};

		int tempselect; //option arrow locate (temp,not the final location)
		int finalselect;
		int _TotalScore;
		int _TheHightestScore;
		int _MenuType;

		bool _Battleing;
		CMovingBitmap _BattleMenuGray; //GrayMenu(background)

		bool _Animationing;
		bool _Selecting; // If Selecting (in Main Menu)
		bool _Menuing; // If Menuing (in Main Menu)
		bool _ChoosingStage; // Choosing Stage will appear gray Menu and let player choose stage 
		CMovingBitmap _ChooseStageMenuTop; //GrayMenu from Top
		CMovingBitmap _ChooseStageMenuDown; //GrayMenu from Down

		int _RaiseSpeed; // Lobby raise speed (animation)
		int _RaiseDelay; // Lobby raise animation delay
		clock_t _Last_time; // Lobby animation need now time to cal delay
		CMovingBitmap _Menu;
		CMovingBitmap _Arrow;
	};

}