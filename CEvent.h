#pragma once
namespace game_framework{
	class CEvent
	{
	public:
		CEvent();
		bool isHit(int x1,int y1, int x2,int y2);
		bool isEnemyClean(int EnemyNum);
		bool isHomeBreak(int Home);
	private:
		const int Width, Height;
	};
}

