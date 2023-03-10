#pragma once

namespace game_framework {
	class CBullet
	{
	public:
		CBullet();

	private:
		int _FlySpeed;	
		int _Direction; // 0 is east, 1 is south, 2 is west,3 is north
		CMovingBitmap _Bulletimage; //all bullet image in here ,index 0 is Go to east Bullet image,1 is south,2 is west,3 is north
		CMovingBitmap _Boom; // the Animation of Boom (Bullet touch the wall or sth)
	};

}