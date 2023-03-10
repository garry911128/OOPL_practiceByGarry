#pragma once
namespace game_framework {
	class CTank
	{
	public:
		CTank();
		int GetX1();
		int GetY1();
		int GetOriginAngle();
		bool isBreak();
		void Animation();
		//void AnimationOnce();
		void Attacke();
		void LevelUP();
		void LocationPoint(int x,int y);
		void Move(UINT nChar);
		void OnShow();
		void SetXY(int x, int y);
		void TurnFace();
	protected:
		CMovingBitmap _Tank;
		clock_t last_time;
		int _X;
		int _Y;
		int _FrameIndex;
		int _OriginAngle,_TurnAngle;
		int _Level;
		int _Life;
		int _OffsetX, _OffsetY;
		int _PointX, _PointY;
		int _MovementSpeed;
		int _LocationDistance;
		bool _AttackSpeedUP;
		bool _CanBreakIron;
		bool _DoubleAttack;
	};

}
