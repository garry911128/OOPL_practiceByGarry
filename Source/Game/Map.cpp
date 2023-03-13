#include <vector>
#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "./MapItem.h"
#include "./Map.h"

using namespace game_framework;

Map::Map() {
	_BoardX = 0;
	_BoardY = 0;
}
void Map::OnInit(vector<vector<int>> stage) {
	_BlackGrid.LoadBitmapByString({ "resources/BlackGrid.bmp" }, RGB(105, 105, 105));
	_BlackGrid.SetTopLeft(100, 0);
	for (int i = 0; i < 26; i++) {
		vector<MapItem> temp;
		for (int j = 0; j < 26; j++) {
			temp.push_back(MapItem(stage[i][j]));
			if (stage[i][j] != 1) {
				temp[j].SetTopLeft(j * 32 + 100, i * 32);
			}
		}
		_Stage.push_back(temp);
	}
	for (int i = 0; i < 20; i++) {
		CMovingBitmap temp;
		temp.LoadBitmapByString({ "resources/BattleMenuCount.bmp" }, RGB(105, 105, 105));
		_EnemySign.push_back(temp);
		if (i % 2 == 0) {
			_EnemySign[i].SetTopLeft(1010,i * 20);
		}
		else {
			_EnemySign[i].SetTopLeft(1080, _EnemySign[i-1].GetTop());
		}
	}
	CMovingBitmap temp1, temp2; // give to playersign
	_OnePlayerHealth.LoadBitmapByString({ "resources/BattleMenu1PHealth.bmp" }, RGB(105, 105, 105));
	_OnePlayerHealth.SetTopLeft(1010, 480);
	_SecondPlayerHealth.LoadBitmapByString({ "resources/BattleMenu2PHealth.bmp" }, RGB(105, 105, 105));
	_SecondPlayerHealth.SetTopLeft(1010, 580);
	_BattleMenuFlag.LoadBitmapByString({ "resources/BattleMenuFlag.bmp" }, RGB(105, 105, 105));
	_BattleMenuFlag.SetTopLeft(1000, 700);

	temp1.LoadBitmapByString({ "resources/BattleMenuHealthSign.bmp" }, RGB(105, 105, 105));
	temp2.LoadBitmapByString({ "resources/BattleMenuHealthSign.bmp" }, RGB(105, 105, 105));
	
	_PlayerSign.push_back(temp1);
	_PlayerSign.push_back(temp2);
	_PlayerSign[0].SetTopLeft(1010, 520);
	_PlayerSign[1].SetTopLeft(1010, 620);
}
void Map::OnShow() {
	_BlackGrid.ShowBitmap();
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			_Stage[i][j].OnShow();
		}
	}
	for (int i = 0; i < (int)_EnemySign.size(); i++) {
		_EnemySign[i].ShowBitmap();
	}
	_OnePlayerHealth.ShowBitmap();
	_SecondPlayerHealth.ShowBitmap();
	for (int i = 0; i < 2; i++) {
		_PlayerSign[i].ShowBitmap();
	}
	_BattleMenuFlag.ShowBitmap();
}

bool Map::GetMapItemInfo(int x, int y, int info) {
	if (info == 0){
		return _Stage[x][y].GetIfWalk();
	}
	else if (info == 1){
		return _Stage[x][y].GetIfShoot();
	}
	else if (info == 2)
	{
		return _Stage[x][y].GetIfBreak();
	}
	return true;
}
int Map::GetType(int x, int y) {
	return _Stage[x][y].GetType();
}