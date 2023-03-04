#include "stdafx.h"
#include "../Core/Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "./Map.h"
#include "./MapItem.h"
#include <vector>

using namespace game_framework;

Map::Map(vector<vector<int>> stage) {
	for (int i = 0; i < 26; i++) {
		vector<MapItem> temp;
		_Stage.push_back(temp);
		for (int j = 0; j < 26; j++) {
			_Stage[i].push_back(MapItem(stage[i][j]));
		}
	}
}

void Map::OnShow() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			_Stage[i][j].OnShow();
		}
	}
}