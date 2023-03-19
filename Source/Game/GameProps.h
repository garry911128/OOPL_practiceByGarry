#pragma once

namespace game_framework {
	class GameProps { //地圖的物件(格子)
	public:
		GameProps();
		void OnInit(int Type);
		void SetTopLeft(int x, int y);
		void OnShow();
		int GetType();

	private:
		CMovingBitmap _Props;
		int _Type; // 0 is chariot,1 is Star, 2 is handgrenade, 3 is clock,4 is steel helmet, 5 is shovel, 6 is pistol
		
	};
}