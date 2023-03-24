#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()                            // 移動遊戲元素
{
	if (_NowStage == -1) { // NowStage == -1  代表正在選 , == 0 代表正在戰鬥(已經選地圖了), == 1 ~ 35代表已經選完了
		event.TrigSelectingStage(ChooseStageScreen);
	}
	if (_NowStage >= 1) {
		event.TrigSetBattleMap(_NowStage,Stage1, _EnemyNum,ChooseStageScreen);
		_PlayerTank.SetIfBattle(true);
	}
	vector<vector<int>> _tempcollision;
	if (_isHoldRightKey == true ||_isHoldLeftKey == true || _isHoldDownKey == true || _isHoldUpKey == true){
		_PlayerTank.TurnFace(_HoldKey);
		_PlayerTank.TankFront();
		_tempcollision = Stage1.GetFrontGridsIndex(_PlayerTank.GetTankFront());
		if (Stage1.GetMapItemInfo(_tempcollision[0][1], _tempcollision[0][0], 0) && \
			Stage1.GetMapItemInfo(_tempcollision[1][1], _tempcollision[1][0], 0) && \
			Stage1.GetIfBoardEdge(_PlayerTank.GetX1(), _PlayerTank.GetY1(), _PlayerTank.GetHeight(), _PlayerTank.GetWidth(), _PlayerTank.GetOriginAngle())){
			_PlayerTank.Move();
		}
		_PlayerTank.Animation();
	}
	if (_PlayerTank.GetIfFire()) {
		_PlayerTank.FireBullet();
		_tempcollision = Stage1.GetFrontGridsIndex(_PlayerTank.GetBulletPlace());
		if (Stage1.GetIfBoardEdge(_PlayerTank.GetBulletX(), _PlayerTank.GetBulletY(), _PlayerTank.GetBulletHeight(), _PlayerTank.GetBulletWidth(), _PlayerTank.GetBulletDirection()) == true) {
			if (Stage1.GetMapItemInfo(_tempcollision[0][1], _tempcollision[0][0], 1) == true || Stage1.GetMapItemInfo(_tempcollision[1][1], _tempcollision[1][0], 1) == true) {
				if (Stage1.GetType(_tempcollision[0][1], _tempcollision[0][0]) == 4) {
					Stage1.ShootWall(_PlayerTank.GetBulletDirection(), 1, _tempcollision[0][1], _tempcollision[0][0]);
				}
				if (Stage1.GetType(_tempcollision[1][1], _tempcollision[1][0]) == 4) {
					Stage1.ShootWall(_PlayerTank.GetBulletDirection(), 1, _tempcollision[1][1], _tempcollision[1][0]);
				}
				_PlayerTank.SetBulletStatus(false);
				_PlayerTank.SetIfFire(false);
			}
		}
		else {
			_PlayerTank.SetBulletStatus(false);
			_PlayerTank.SetIfFire(false);
		}
	}
}
void CGameStateRun::OnInit()                                  // 遊戲的初值及圖形設定
{
	_NowStage = -1;
	ChooseStageScreen.LoadBitMap();
	vector<vector<int>> tempstage1,tempstage2,tempstage5,tempstage17;
	tempstage1= { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	,{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 5, 5, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 5, 5, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	,{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	,{ 4, 4, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 4, 4 }
	,{ 5, 5, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 5, 5 }
	,{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	,{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
	,{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 5, 5, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	,{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 5, 5, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};
	tempstage2 = { { 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
,{ 1, 1, 4, 4, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
,{ 1, 1, 4, 4, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
,{ 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 4, 4, 5, 5, 4, 4, 1, 1 }
,{ 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 4, 4, 5, 5, 4, 4, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1 }
,{ 6, 6, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 4, 4, 6, 6, 4, 4, 5, 5 }
,{ 6, 6, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 4, 4, 6, 6, 4, 4, 5, 5 }
,{ 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 5, 5, 1, 1, 6, 6, 1, 1, 1, 1 }
,{ 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 5, 5, 1, 1, 6, 6, 1, 1, 1, 1 }
,{ 1, 1, 4, 4, 4, 4, 4, 4, 6, 6, 6, 6, 6, 6, 5, 5, 1, 1, 1, 1, 6, 6, 4, 4, 1, 1 }
,{ 1, 1, 4, 4, 4, 4, 4, 4, 6, 6, 6, 6, 6, 6, 5, 5, 1, 1, 1, 1, 6, 6, 4, 4, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 5, 5, 6, 6, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 5, 5, 6, 6, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
,{ 5, 5, 4, 4, 1, 1, 5, 5, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1 }
,{ 5, 5, 4, 4, 1, 1, 5, 5, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1 }
,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 5, 5, 4, 4, 1, 1 }
,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 5, 5, 4, 4, 1, 1 }
,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
,{ 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
,{ 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 4, 5, 5, 4, 1, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1 }
,{ 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 4, 5, 5, 4, 1, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1 }
	};
	tempstage5 = { { 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 1, 1, 1, 1 } 
,{ 5, 5, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1 }
,{ 5, 5, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
,{ 5, 5, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
,{ 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2 }
,{ 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2 }
,{ 4, 4, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 4, 4, 4, 4 }
,{ 1, 1, 1, 1, 4, 4, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 4, 4, 4, 4 }
,{ 4, 4, 4, 4, 1, 1, 1, 1, 2, 2, 4, 4, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1 } 
,{ 4, 4, 4, 4, 1, 1, 1, 1, 2, 2, 4, 4, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1 }
,{ 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 1, 1, 5, 5, 1, 1, 4, 4, 1, 1, 1, 5, 1, 1, 1, 1 }
,{ 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 1, 1, 5, 5, 1, 1, 4, 4, 1, 1, 1, 5, 1, 1, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 4, 4, 4, 4 }
,{ 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 4, 4, 4, 4 }
,{ 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1 }
,{ 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1 } 
,{ 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1 }
,{ 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 5, 5, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
,{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 5, 5, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};
	tempstage17 = { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
					,{ 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1 }
					,{ 1, 1, 4, 4, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 1, 1 }//2
					,{ 1, 1, 4, 4, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 1, 1 }
					,{ 1, 1, 4, 4, 1, 1, 1, 1, 4, 4, 1, 1, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1 }
					,{ 1, 1, 4, 4, 1, 1, 1, 1, 4, 4, 1, 1, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1 }//5
					,{ 3, 3, 3, 3, 3, 3, 5, 1, 4, 4, 1, 1, 1, 1, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1 }
					,{ 3, 3, 3, 3, 3, 3, 5, 1, 4, 4, 1, 1, 1, 1, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1 }
					,{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1 }//8
					,{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1 }
					,{ 1, 1, 1, 1, 1, 5, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 1, 4, 4, 1, 1, 1, 5, 5, 5, 5 }
					,{ 1, 1, 1, 1, 1, 5, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1 }//11
					,{ 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4 }
					,{ 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4 }
					,{ 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1 }//14
					,{ 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1 }
					,{ 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 1, 1, 4, 4, 1, 1 }
					,{ 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 1, 1, 4, 4, 1, 1 }//17
					,{ 3, 3, 3, 3, 3, 3, 4, 4, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
					,{ 3, 3, 3, 3, 3, 3, 4, 4, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
					,{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1 }//20
					,{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1 }
					,{ 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1 }
					,{ 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 1, 4, 4, 4, 4, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1 }//23
					,{ 4, 4, 4, 4, 5, 1, 1, 1, 1, 1, 1, 4, 5, 5, 4, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }
					,{ 4, 4, 4, 4, 5, 1, 1, 1, 1, 1, 1, 4, 5, 5, 4, 1, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1 }//25
	};
	Stage1.OnInit(tempstage5);
	_MouseX = 0;
	_MouseY = 0;
	_PlayerTank.LoadBitmap();
	_PlayerTankFrontX = 0;
	_PlayerTankFrontY = 0;
	Prop.OnInit(7);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x5A || nChar == 0x58) {
		_PlayerTank.FireBullet();
	}
	if (nChar == VK_DOWN)	_isHoldDownKey = true;
	if (nChar == VK_UP)		_isHoldUpKey   = true;
	if (nChar == VK_LEFT)	_isHoldLeftKey = true;
	if (nChar == VK_RIGHT)	_isHoldLeftKey = true;
	if (nChar == VK_DOWN || nChar == VK_RIGHT|| nChar == VK_LEFT|| nChar == VK_UP) _HoldKey = nChar;
	/*if (GetKeyState(VK_UP) || GetKeyState(VK_DOWN) || GetKeyState(VK_RIGHT) || GetKeyState(VK_LEFT)) {
		_HoldKey = nChar;
		_PlayerTank.TurnFace(_HoldKey);
		_PlayerTank.Move();
		_PlayerTank.Animation();
	}*/
	_NowStage = ChooseStageScreen.OnKeyDown(nChar, nRepCnt, nFlags);

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN)	_isHoldDownKey = false;
	if (nChar == VK_UP)		_isHoldUpKey   = false;
	if (nChar == VK_LEFT)	_isHoldLeftKey = false;
	if (nChar == VK_RIGHT)	_isHoldLeftKey = false;
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
	_MouseX = point.x;
	_MouseY = point.y;
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	ChooseStageScreen.OnShow();
	Stage1.OnShow();
	_PlayerTank.OnShow();
	Prop.OnShow();
	OnShowText();
}
void CGameStateRun::OnShowText() {
	CDC *pDC = CDDraw::GetBackCDC();
	CFont *fp;
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 180, 0));

	vector<vector<int>> _tempcollision;
	_tempcollision = Stage1.GetFrontGridsIndex(_PlayerTank.GetBulletPlace());
	CTextDraw::Print(pDC, 0, 0, (to_string(_PlayerTankFrontY) + " " + to_string(_PlayerTankFrontX).c_str()));
	CTextDraw::Print(pDC, 0, 25, (to_string(_MouseX) + " " + to_string(_MouseY).c_str()));
	CTextDraw::Print(pDC, 0, 50, (to_string(_tempcollision[0][0]) + "," + to_string(_tempcollision[0][1]).c_str()));
	CTextDraw::Print(pDC, 0, 75, (to_string(_tempcollision[1][0]) + "," + to_string(_tempcollision[1][1]).c_str()));
	CTextDraw::Print(pDC, 0, 95, ( to_string(_1POr2P).c_str()));
	ChooseStageScreen.OnShowText(pDC,fp);
	/*
	CTextDraw::ChangeFontLog( pDC, 10, "TRANSPARENT", RGB(0, 180, 0));
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			CTextDraw::Print(pDC, j * 32 + 110, i * 32, (to_string(i) + "," + to_string(j).c_str()));
		}
	}
	*/

	CDDraw::ReleaseBackCDC();
}