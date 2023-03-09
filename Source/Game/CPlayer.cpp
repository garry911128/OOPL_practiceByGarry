#include <vector>
#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "CPlayer.h"

// Tank Child
using namespace game_framework;

CPlayer::CPlayer() {
}
void CPlayer::SpawnAfter5Second() {
	_Invicible = true;
}
void CPlayer::LoadBitmap() {
	_Tank.LoadBitmapByString({  "resources/Tank_Right_1.bmp" ,"resources/Tank_Right_2.bmp",
							    "resources/Tank_Left_1.bmp"  ,"resources/Tank_Left_2.bmp", 
								"resources/Tank_Top_1.bmp"   ,"resources/Tank_Top_2.bmp", 
								"resources/Tank_Bottom_1.bmp","resources/Tank_Bottom_2.bmp"},RGB(0,0,0));
}
