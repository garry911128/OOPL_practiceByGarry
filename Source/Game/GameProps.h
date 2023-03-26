#pragma once

namespace game_framework {
	class GameProps { //地圖的物件(格子)
	public:
		GameProps();
		void OnInit();
		void SetGameProps();
		void OnShow();

		int GetType();
		void SetIfShow(bool IfShow);
		bool GetIfShow();

		int GetPropLeftX();
		int GetPropRightX();
		int GetPropTopY();
		int GetPropDownY();

		void SetPropDisapear();

		CMovingBitmap GetPropBitmap();
	private:
		CMovingBitmap _Props;
		int _X, _Y; //top left x,top y
		bool _IfShow; // 甚麼時候要出現
		int _Type; // 0 is chariot,1 is Star, 2 is handgrenade, 3 is clock,4 is steel helmet, 5 is shovel, 6 is pistol
		
	};
}