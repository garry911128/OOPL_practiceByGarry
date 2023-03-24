#pragma once

#include "Menu.h"
#include "Map.h"
namespace game_framework {
	class Event {
	public:
		Event();
		static void TrigLobbyMenu(Menu &LobbyMenu); // If u lose your 3 health,or first time login,you will go lobby (include select)
		static void TrigSelectingStage(Menu &GrayMenu); //use this func when choosing stage,and battle 
		static void TrigSetBattleMap(int& NowStage,Map& StageMap,int& EnemyNum, Menu& BattleMenu);
	private:
		bool _IfStart; // the attribute that can decide the Battle start or not
	};
}
