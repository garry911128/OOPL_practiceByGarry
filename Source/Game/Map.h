#pragma once
#include "MapItem.h"

namespace game_framework {
	class Map { //地圖的物件(格子)
	public:
		Map(vector<vector<int>> stage); //要傳某一個stage的每個格子 type
		vector<vector<MapItem>> _Stage; //每一個stage
		int _BoardX; //棋盤的x
		int _BoardY; //棋盤的y
		void OnShow(); 
	};
}