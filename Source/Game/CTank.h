#pragma once
namespace game_framework {
	class CTank
	{
	public:
		CTank();
		int GetX1();
		int GetY1();
		bool isBreak();
		void SetXY(int x, int y);
		void Attacke();
		void Move(UINT nChar);
		void TurnFace();
		void OnShow();
		void LevelUP();
		void AnimationOnce();
	protected:
		CMovingBitmap _Tank;
		int _X;
		int _Y;
		int _Angle;
		int _Level;
		int _Life;
		bool _AttackSpeedUP;
		bool _CanBreakIron;
		bool _DoubleAttack;
	};

}
