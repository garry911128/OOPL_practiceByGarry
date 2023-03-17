#pragma once

namespace game_framework {
	class CBullet
	{
	public:
		CBullet();
		void LoadBitmap();
		void SetBulletFire(int TankX, int TankY,int TankDirect);
		void OnShow();
		bool _IfFlying;
		bool GetAlreadyFire();
		int GetDirection();
		int GetNowX();
		int GetNowY();
		static vector<int> localRight;
		static vector<int> localDown;
		static vector<int> localLeft;
		static vector<int> localUp;
	private:
		enum Direction {
			Right, Down, Left, Up
		};
		bool _AlreadyFire;
		int _NowX, _NowY;
		int _Direction;
		int _DestinationX, _DestinationY;
		int _FlySpeed;
		CMovingBitmap _Bulletimage; //all bullet image in here ,index 0 is Go to east Bullet image,1 is south,2 is west,3 is north
		CMovingBitmap _Boom; // the Animation of Boom (Bullet touch the wall or sth)
	};

}