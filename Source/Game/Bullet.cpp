#include <vector>
#include <string>
#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "Bullet.h"


using namespace game_framework;
vector<int> CBullet::localRight = { 0,2 };
vector<int> CBullet::localDown = { 2,0 };
vector<int> CBullet::localLeft = { 0, -2 };
vector<int> CBullet::localUp = { -2,0 };
CBullet::CBullet() {
	//"resources/Bullet0.bmp","resources/Bullet1.bmp","resources/Bullet2.bmp","resources/Bullet3.bmp"
	//_Boom.LoadBitmapByString({ "resources/Boom0.bmp","resources/Boom1.bmp","resources/Boom2.bmp" }, RGB(0, 0, 0));
	_FlySpeed = 15;
	_IfFlying = false;
	_AlreadyFire = false;
	_DestinationX = 0;
	_DestinationY = 0;
}

void CBullet::LoadBitmap() {
	_Bulletimage.LoadBitmapByString({ "resources/Bullet0.bmp","resources/Bullet1.bmp","resources/Bullet2.bmp","resources/Bullet3.bmp" }, RGB(105, 105, 105));
	_Boom.LoadBitmapByString({ "resources/Boom0.bmp","resources/Boom1.bmp","resources/Boom2.bmp" }, RGB(0, 0, 0));
}
bool CBullet::GetAlreadyFire() {
	return _AlreadyFire;
}
void CBullet::SetBulletFire(int TankX,int TankY,int TankDirect) {
	if (_AlreadyFire == false) {
		_AlreadyFire = true;
		if (TankDirect == Right) {
			_DestinationX = 932;
			_DestinationY = TankY;
		}
		else if (TankDirect == Down) {
			_DestinationX = TankX;
			_DestinationY = 832;
		}
		else if (TankDirect == Left) {
			_DestinationX = 100;
			_DestinationY = TankY;
		}
		else if (TankDirect == Up) {
			_DestinationX = TankX;
			_DestinationY = 0;
		}
		_NowX = TankX;
		_NowY = TankY;
		_Direction = TankDirect;
		_Bulletimage.SetFrameIndexOfBitmap(TankDirect);
	}
	else {
		if (_Direction == Right) {
			if (_NowX >= 932) {
				_AlreadyFire = false;
			}
			_NowX += _FlySpeed;
		}
		else if (_Direction == Down) {
			if (_NowY >= 832) {
				_AlreadyFire = false;
			}
			_NowY += _FlySpeed;
		}
		else if (_Direction == Left) {
			if (_NowX <= 100) {
				_AlreadyFire = false;
			}
			_NowX -= _FlySpeed;
		}
		else if (_Direction == Up) {
			if (_NowY <= 0) {
				_AlreadyFire = false;
			}
			_NowY -= _FlySpeed;
		}
	}
	_Bulletimage.SetTopLeft(_NowX, _NowY);
}

void CBullet::OnShow() {
	if (_AlreadyFire == true) {
		_Bulletimage.ShowBitmap();
	}
}

int CBullet::GetDirection() {
	return _Direction;
}

int CBullet::GetNowX() {
	return _NowX;
}

int CBullet::GetNowY() {
	return _NowY;
}