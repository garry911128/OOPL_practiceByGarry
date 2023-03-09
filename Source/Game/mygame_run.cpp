#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()                            // 移動遊戲元素
{

}
void CGameStateRun::OnInit()                                  // 遊戲的初值及圖形設定
{
	vector<vector<int>> tempstage;
	tempstage = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 2row一大格(4*4)
				{1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1},{1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1},
				{1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1},{1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1},
				{1,1,4,4,1,1,4,4,1,1,4,4,5,5,4,4,1,1,4,4,1,1,4,4,1,1},{1,1,4,4,1,1,4,4,1,1,4,4,5,5,4,4,1,1,4,4,1,1,4,4,1,1},
				{1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1},{1,1,4,4,1,1,4,4,1,1,1,1,1,1,1,1,1,1,4,4,1,1,4,4,1,1},
				{1,1,4,4,1,1,4,4,1,1,1,1,1,1,1,1,1,1,4,4,1,1,4,4,1,1},{1,1,1,1,1,1,1,1,1,1,4,4,1,1,4,4,1,1,1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1,1,1,4,4,1,1,4,4,1,1,1,1,1,1,1,1,1,1},{4,4,1,1,4,4,4,4,1,1,1,1,1,1,1,1,1,1,4,4,4,4,1,1,4,4},
				{5,5,1,1,4,4,4,4,1,1,1,1,1,1,1,1,1,1,4,4,4,4,1,1,5,5},{1,1,1,1,1,1,1,1,1,1,4,4,1,1,4,4,1,1,1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,1,1,1,1,1,1,1,1,1,1},{1,1,4,4,1,1,4,4,1,1,4,4,4,4,4,4,1,1,4,4,1,1,4,4,1,1},
				{1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1},{1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1},
				{1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1,4,4,1,1},{1,1,4,4,1,1,4,4,1,1,1,1,1,1,1,1,1,1,4,4,1,1,4,4,1,1},
				{1,1,4,4,1,1,4,4,1,1,1,1,1,1,1,1,1,1,4,4,1,1,4,4,1,1},{1,1,4,4,1,1,4,4,1,1,1,4,4,4,4,1,1,1,4,4,1,1,4,4,1,1},
				{1,1,1,1,1,1,1,1,1,1,1,4,5,5,4,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,4,5,5,4,1,1,1,1,1,1,1,1,1,1,1} };
	Stage1.OnInit(tempstage);
	_MouseX = 0;
	_MouseY = 0;
	_PlayerTank.LoadBitmap();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	_PlayerTank.Move(nChar);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
	_MouseX = point.x;
	_MouseY = point.y;
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	Stage1.OnShow();
	OnShowText();
	_PlayerTank.OnShow();
}
void CGameStateRun::OnShowText() {
	CDC *pDC = CDDraw::GetBackCDC();
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));
	CTextDraw::Print(pDC, 0, 0, (to_string(_MouseX) + " " + to_string(_MouseY).c_str()));

	CDDraw::ReleaseBackCDC();
}