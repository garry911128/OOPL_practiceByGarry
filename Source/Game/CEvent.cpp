﻿#include <vector>
#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <string>
#include "CEvent.h"

// 地圖物件發生事件
using namespace game_framework;

Event::Event() {
	_IfStart = false;
}
void Event::TrigLobbyMenu(Menu& LobbyMenu) {
	if (LobbyMenu.GetMenuY(0) > 0) {
		LobbyMenu.SetLobbyRaise();
	}
	else {
		LobbyMenu.SetSelecting(true);
	}
}
void Event::TrigSelectingStage(Menu& GrayScreen) {
	if (GrayScreen.GetMenuY(1) < 0) {
		GrayScreen.SetChoosingStageanimation();
	}
	else {
		GrayScreen.SetSelecting(true);
	}
}

void Event::TrigSetBattleMap(int& NowStage,Map& StageMap,int& EnemyNum, Menu& BattleMenu) {
	StageMap.SetIfShowMap(true);
	BattleMenu.SetBattleing(true);
	NowStage = 0;
	EnemyNum = 20;
}
void Event::TrigSetProps(GameProps& Props) {
	Props.SetGameProps();
}
void Event::TrigGetProps(GameProps& Props,Map& StageMap,CPlayer& Player) {
	Props.SetIfShow(false);
	int type = Props.GetType();
	if (type == 0) {
		//Player
	}
	else if (type == 1) {
		Player.LevelUP();
	}
	else if (type == 5) {
		StageMap.SetGetShovel(Props.IfEffectExit());
	}
	else if (type == 7) {
		Player.SetIfGetShip(true);
	}
}