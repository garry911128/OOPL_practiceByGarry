#pragma once

namespace game_framework {
	class CBullet
	{
	public:
		CBullet();
		void LoadBitmap();
		void SetBulletFire(int TankX, int TankY,int TankDirect);
		void OnShow();
		void SetBulletAlreadyFire(bool AlreadyFire);
		bool _IfFlying;
		bool GetAlreadyFire();
		int GetDirection();
		static vector<vector<int>> _Move;
		vector<vector<int>> _GetNowPlace();
	private:
		enum Move {
			Right, Down, Left, Up
		};
		bool _AlreadyFire;
		vector<vector<int>> _NowPlace; //the place that stand on your left and right
		int _Direction;
		vector<vector<int>> _NextMove;
		int _FlySpeed;
		CMovingBitmap _Bulletimage; //all bullet image in here ,index 0 is Go to east Bullet image,1 is south,2 is west,3 is north
		CMovingBitmap _Boom; // the Animation of Boom (Bullet touch the wall or sth)
	};

}