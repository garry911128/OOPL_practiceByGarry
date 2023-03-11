#include <vector>
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
}
void CBullet::OnInit() {
	_Bulletimage.LoadBitmapByString({ "resources/Bullet0.bmp","resources/Bullet1.bmp","resources/Bullet2.bmp","resources/Bullet3.bmp" }, RGB(0, 0, 0));
	_Boom.LoadBitmapByString({ "resources/Boom0.bmp","resources/Boom1.bmp","resources/Boom2.bmp" }, RGB(0, 0, 0));
	_FlySpeed = 4;
	_Direction = 3; // Tank initial is north,so bullet as well;
}

bool CBullet::BulletFly(int TankX,int TankY) {
	int now_x = TankX , now_y = TankY;
	_Bulletimage.SetFrameIndexOfBitmap(_Direction);
	_Bulletimage.SetTopLeft(now_x, now_y);
	if (_Direction == 0) {
		while (now_x < 832) {
			now_x += _FlySpeed;
		}
	}
	else if (_Direction == 2) {
		while (now_x > 0) {
			now_x -= _FlySpeed;
		}
	}
	else if (_Direction == 1) {
		while (now_y < 832) {
			now_y += _FlySpeed;
		}
	}
	else if (_Direction == 3) {
		while (now_y < 0) {
			now_y -= _FlySpeed;
		}
	}
	return false;
}
void CBullet::OnShow() {
	_Bulletimage.ShowBitmap();
}