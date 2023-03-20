#pragma once
#include "CTank.h"
namespace game_framework {
	class CPlayer :public CTank 
	{
	public:
		CPlayer();
		void LoadBitmap();
		void SpawnAfter5Second();
	private:
		int _Invicible;
	};

}
