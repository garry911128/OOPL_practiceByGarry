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

CBullet::CBullet() {
	//"resources/Bullet0.bmp","resources/Bullet1.bmp","resources/Bullet2.bmp","resources/Bullet3.bmp"
	//_Boom.LoadBitmapByString({ "resources/Boom0.bmp","resources/Boom1.bmp","resources/Boom2.bmp" }, RGB(0, 0, 0));
	_FlySpeed = 5;
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
		if (TankDirect == 0) {
			_DestinationX = 932;
			_DestinationY = TankY;
		}
		else if (TankDirect == 1) {
			_DestinationX = TankX;
			_DestinationY = 832;
		}
		else if (TankDirect == 2) {
			_DestinationX = 100;
			_DestinationY = TankY;
		}
		else if (TankDirect == 3) {
			_DestinationX = TankX;
			_DestinationY = 0;
		}
		_NowX = TankX;
		_NowY = TankY;
		_Direction = TankDirect;
		_Bulletimage.SetFrameIndexOfBitmap(TankDirect);
		_Bulletimage.SetTopLeft(_NowX, _NowY);
	}
	else {
		if (_Direction == 0) {
			if (_NowX >= 932) {
				_AlreadyFire = false;
			}
			_NowX += _FlySpeed;
		}
		else if (_Direction == 1) {
			if (_NowY >= 832) {
				_AlreadyFire = false;
			}
			_NowY += _FlySpeed;
		}
		else if (_Direction == 2) {
			if (_NowX <= 100) {
				_AlreadyFire = false;
			}
			_NowX -= _FlySpeed;
		}
		else if (_Direction == 3) {
			if (_NowY <= 0) {
				_AlreadyFire = false;
			}
			_NowY -= _FlySpeed;
		}
		_Bulletimage.SetTopLeft(_NowX, _NowY);
	}
}
void CBullet::OnShow() {
	if (_AlreadyFire == true) {
		_Bulletimage.ShowBitmap();
	}
}