#pragma once

#include "CTank.h"
#include "Bullet.h"
namespace game_framework {
	class CPlayer :public CTank 
	{
	public:
		CPlayer();
		void KillEnemy(int type);
		void LoadBitmap();
		void SpawnAfter5Second();
		void PlusPlayerScore(int score);
		void LevelUP();

		int GetPlayerScore();
		bool GetIfGetShip();

		void SetIfGetShip(bool Status);
		void SetMoveOnIce(bool IfOnIce);

		void SetBulletStatus(int BulletOrder, bool Status) override;
		void SetIfFire(int FireOrder, bool Status) override;
		bool GetIfFire(int FireOrder) override;
		void FireBullet(int BulletOrder) override;
		CBullet _SecondBullet;

		void OnShow();
	private:
		bool _IfSecondFire;

		bool _IfGetShip;

		int _Invicible;
		int _PlayerScore;
		vector<int> _KillEnemyList;

	};
}
