#pragma once

#include "CTank.h"
namespace game_framework {
	class CPlayer :public CTank 
	{
	public:
		CPlayer();
		int GetPlayerScore();
		void KillEnemy(int type);
		void LoadBitmap();
		void SpawnAfter5Second();
		void PlusPlayerScore(int score);
		void LevelUP();

		bool GetIfGetShip();
		void SetIfGetShip(bool Status);

		void SetMoveOnIce(bool IfOnIce);
	private:
		bool _IfGetShip;
		int _Invicible;
		int _PlayerScore;
		vector<int> _KillEnemyList;
	};
}
