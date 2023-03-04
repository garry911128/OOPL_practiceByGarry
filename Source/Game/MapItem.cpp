#include "stdafx.h"
#include "../Core/Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "./MapItem.h"

using namespace game_framework;

MapItem::MapItem(int Type) { //傳某一個格子 type 進去
	_Type = Type;
	if (_Type == 1) { // 1是 黑色格子(可以走,不行射擊(穿過), 不行破壞)
		_IfShoot = false;
		_IfBreak = false;
		_IfWalk = true;
	}
	else if (_Type == 2) { //2是 水 (無法行走(拿道具可走), 不行射擊(穿過) ,不行破壞 )
		_IfShoot = false;
		_IfBreak = false;
		_IfWalk = false;
		_OneGrid.LoadBitmapByString({ "resources/Water1.bmp","resource/Water2" ,"resources/Water3.bmp" }, RGB(0, 0, 0));
	}
	else if (_Type == 3) { //3是 斜面 (可行走 , 不行射擊(穿過) ,不行破壞 )
		_IfShoot = false;
		_IfBreak = false;
		_IfWalk = true;
		_OneGrid.LoadBitmapByString({ "resources/Ice"}, RGB(0, 0, 0));
	}
	else if (_Type == 4) { //4是 磚牆(無法行走(可破壞後走), 可射擊(無法穿過) ,可破壞 )
		_IfShoot = true;
		_IfBreak = true;
		_IfWalk = false;
		_OneGrid.LoadBitmapByString({ "resources/Wall", "resources/WallBottomBreak","resources/WallLeftBreak","resources/WallRightBreak","resources/WallTopBreak" }, RGB(0, 0, 0));
	}
	else if (_Type == 5) { //5是 鐵牆(無法行走(可破壞後走), 可射擊(無法穿過) ,不可破壞(拿道具後可破壞) )
		_IfShoot = true;
		_IfBreak = false;
		_IfWalk = false;
		_OneGrid.LoadBitmapByString({ "resources/IronWall" }, RGB(0, 0, 0));
	}
	else if (_Type == 6) { //6是 草叢(可行走, 不可射擊(穿過) ,不可破壞 )
		_IfShoot = false;
		_IfBreak = false;
		_IfWalk = true;
		_OneGrid.LoadBitmapByString({ "resources/Grass" }, RGB(0, 0, 0));
	}
}
void MapItem::OnShow() {
	if (_Type != 1) {
		_OneGrid.ShowBitmap();
	}
}