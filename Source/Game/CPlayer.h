#pragma once
#include "CTank.h"
namespace game_framework {
	class CPlayer :public CTank 
	{
	public:
		CPlayer();
		/*int GetX1();
		int GetY1();
		void SetXY(int x, int y);
		void Attacke();
		void Move(UINT nChar);
		void TurnFace();
		void OnShow();
		void LevelUP();*/
		void LoadBitmap();
		void SpawnAfter5Second();
	private:
		/*CMovingBitmap _Tank;
		int _X;
		int _Y;
		int _Angle;
		int _Level;
		bool _AttackSpeedUP;
		bool _CanBreakIron;
		bool _DoubleAttack;*/
		int _Invicible;
	};

}
