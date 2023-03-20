#pragma once

#include "CTank.h"

namespace game_framework {
	class Enemy : public CTank
	{
	public:
		Enemy();
		void SetEnemyType(int _num);
		void LoadBitmap();
		void SpawnAfter5Second();
	private:
		enum EnemyType{
			LightTank,
			QuickTank,
			ArmorTank,
			HeavyTank,
		};
		int _EnemyType;
		int _Invicible;
	};

}
