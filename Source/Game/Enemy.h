#pragma once

#include "CTank.h"

namespace game_framework {
	class Enemy : public CTank
	{
	public:
		Enemy();
		int GetEnemyScore();
		bool isEnemuHaveItem();
		void SetEnemyHaveItem();
		void SetEnemyType(int _num);
		void SetEnemyInit();
		void LoadBitmap();
		void SetOriginAngle(int _direction);
	private:
		int _EnemyType;
		int _EnemyScore;
		bool _EnemyHaveItem;
	};

}
