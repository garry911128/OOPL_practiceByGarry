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

vector<vector<int>> CBullet::_Move = { {1,0},{0,1},{-1,0},{0,-1} }; //Vector 2D

CBullet::CBullet() {
	//"resources/Bullet0.bmp","resources/Bullet1.bmp","resources/Bullet2.bmp","resources/Bullet3.bmp"
	//_Boom.LoadBitmapByString({ "resources/Boom0.bmp","resources/Boom1.bmp","resources/Boom2.bmp" }, RGB(0, 0, 0));
	_FlySpeed = 15;
	_IfFlying = false;
	_AlreadyFire = false;
	_NextMove = { {0,0},{0,0} };
	_NowPlace = { {0,0},{0,0} };
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
		_NowPlace[0][0] = TankX;
		_NowPlace[0][1] = TankY;
		_Direction = TankDirect;
		if (_Direction == Right || _Direction == Left) {
			_NowPlace[1][0] = TankX;
			_NowPlace[1][1] = TankY + 4;
		}
		else if (_Direction == Down || _Direction == Up) {
			_NowPlace[1][0] = TankX + 4;
			_NowPlace[1][1] = TankY;
		}
		_Bulletimage.SetFrameIndexOfBitmap(TankDirect);
		_NextMove[0][0] = _NowPlace[0][0] + _Move[TankDirect][0] * _FlySpeed;
		_NextMove[0][1] = _NowPlace[0][1] + _Move[TankDirect][1] * _FlySpeed;
		_NextMove[1][0] = _NowPlace[1][0] + _Move[TankDirect][0] * _FlySpeed;
		_NextMove[1][1] = _NowPlace[1][1] + _Move[TankDirect][1] * _FlySpeed;
		_Bulletimage.SetTopLeft(_NowPlace[0][0], _NowPlace[0][1]);
	}
	else {
		_NowPlace[0][0] = _NextMove[0][0];
		_NowPlace[0][1] = _NextMove[0][1];
		_NowPlace[1][0] = _NextMove[1][0];
		_NowPlace[1][1] = _NextMove[1][1];

		_NextMove[0][0] = _NowPlace[0][0] + _Move[_Direction][0] * _FlySpeed;
		_NextMove[0][1] = _NowPlace[0][1] + _Move[_Direction][1] * _FlySpeed;
		_NextMove[1][0] = _NowPlace[1][0] + _Move[_Direction][0] * _FlySpeed;
		_NextMove[1][1] = _NowPlace[1][1] + _Move[_Direction][1] * _FlySpeed;
		if (_Direction == 0) {
			if (_NowPlace[0][0] >= 932) {
				_AlreadyFire = false;
			}
		}
		else if (_Direction == 1) {
			if (_NowPlace[0][1] >= 832) {
				_AlreadyFire = false;
			}
		}
		else if (_Direction == 2) {
			if (_NowPlace[0][0] <= 100) {
				_AlreadyFire = false;
			}
		}
		else if (_Direction == 3) {
			if (_NowPlace[0][1] <= 0) {
				_AlreadyFire = false;
			}
		}
		_Bulletimage.SetTopLeft(_NowPlace[0][0], _NowPlace[0][1]);
	}
}
void CBullet::OnShow() {
	if (_AlreadyFire == true) {
		_Bulletimage.ShowBitmap();
	}
}
void CBullet::SetBulletAlreadyFire(bool BulletAlreadyFire) {
	_AlreadyFire = BulletAlreadyFire;
}
vector<vector<int>> CBullet::_GetNowPlace() {
	return _NowPlace;
}
int CBullet::GetDirection() {
	return _Direction;
}
