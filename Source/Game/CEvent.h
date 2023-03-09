#pragma once
namespace game_framework {
	class CEvent
	{
	public:
		CEvent();
		bool isEnemyClean();
		bool isHomeBreak();
		void WhoBeingtHit(string object);
	private:
		int _EnemyNum;
		bool _HomeBreak;
	};

}
