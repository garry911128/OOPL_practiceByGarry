#pragma once

namespace game_framework {
	class MapItem { //地圖的物件(格子)
	public:
		MapItem();
		MapItem(int Type);
		void SetTopLeft(int x, int y);
		void OnShow();
		void ChangeGridState(int Direction,int Attack); // 子彈方向
		bool GetIfShoot();
		bool GetIfBreak();
		bool GetIfWalk();
		int GetType();
	private:
		CMovingBitmap _OneGrid;
		int _Health;
		int _Type;
		bool _IfShoot;  //是否可以射擊 false 不行,true可以
		bool _IfBreak;  //是否可以破壞 false 不行,true可以
		bool _IfWalk;   //是否可以走上去(格子) false 不行,true可以
	};
}