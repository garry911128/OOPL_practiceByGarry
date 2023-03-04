#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "CEvent.h"
namespace game_framework {
	CEvent::CEvent():Width(40),Height(40) {
	};
	bool CEvent::isHit(int _x1, int _y1, int _x2, int _y2) {
		if ((_x1/Width ==_x2/Width )&& (_y1/Height == _y2/Height))
		{
			return true;
		}
		return false;
	};
	bool CEvent::isEnemyClean(int _EnemyClean) {
		if (_EnemyClean==0)
		{
			return true;
		}
		return false;
	};
	bool CEvent::isHomeBreak(int _Home) {
		if (_Home == 1)
		{
			return true;
		}
		return false;
	};
}