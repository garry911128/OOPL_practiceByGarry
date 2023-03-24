#pragma once

#include "CTank.h"

namespace game_framework {
	class Enemy : public CTank
	{
	public:
		Enemy();
		void SetEnemyType(int _num);
		void SetEnemyInit();
		void LoadBitmap();
	private:
		enum EnemyType{
			LightTank,
			QuickTank,
			ArmorTank,
			HeavyTank,
		};
		int _EnemyType;
	};

}
