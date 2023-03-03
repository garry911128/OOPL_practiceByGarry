#pragma once

namespace game_framework {
	class MapItem { //地圖的物件(格子)
	public:
		MapItem(int Type);
		int _Type;
		bool _IfShoot;  //是否可以射擊 false 不行 , true可以
		bool _IfBreak;  //是否可以破壞 false 不行 , true可以
		bool _IfWalk;	//是否可以走上去(格子) false 不行 , true可以
		CMovingBitmap _OneGrid;

		void OnShow();
	};
}