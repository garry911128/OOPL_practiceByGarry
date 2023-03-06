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
	for (int i = 0; i < 26; i++) {
		vector<MapItem> temp;
		for (int j = 0; j < 26; j++) {
			temp.push_back(MapItem(stage[i][j]));
			if (temp[j].GetType() != 1) {
				temp[j].SetTopLeft(j * 32, i * 32);
			}
		}
		_Stage.push_back(temp);
	}
}

void Map::OnShow() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			_Stage[i][j].OnShow();
		}
	}
}