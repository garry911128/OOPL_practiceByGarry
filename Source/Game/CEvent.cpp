#include <vector>
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

CEvent::CEvent() {
	_HomeBreak = false;
	_EnemyNum = 20;
}
void CEvent::WhoBeingtHit(string object) { //誰被擊中
	if (object == "Tank")
	{
		_EnemyNum -= 1; 
	}
	else if (object == "Home")
	{
		_HomeBreak = true;
	}
	else if (object == "Wall")
	{

	}
};
bool CEvent::isEnemyClean() { //是否清光敵人
	if (_EnemyNum == 0)
	{
		return true;
	}
	return false;
};
bool CEvent::isHomeBreak() { //主堡是否被擊中
	return _HomeBreak;
}