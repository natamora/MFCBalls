#include "stdafx.h"
#include "CBall.h"

CBall::CBall(const CRect& rect, COLORREF ballColor, int offX, int offY)
{
	SetBallSize(rect);
	SetOffset(offX, offY);
	InitObjects(ballColor);
}

CBall::CBall(const CPoint& point, const CSize& size, COLORREF ballColor, int offX, int offY) : CRect(point, size)
{
	SetBallSize(CRect(point, size));
	SetOffset(offX, offY);
	InitObjects(ballColor);
}

CBall::CBall(int l, int t, int r, int b, COLORREF ballColor, int offX, int offY) : CRect(l, t, r, b)
{
	SetBallSize(CRect(l, t, r, b));
	SetOffset(offX, offY);
	InitObjects(ballColor);
}

CBall::~CBall()
{
	delete m_pBallPen;
	delete m_pBallBrush;
}

void CBall::PaintBall(CDC *pDC)					//narysuj kulkê
{
	CPen* pOldPen = pDC->SelectObject(m_pBallPen);
	CBrush* pOldBrush = pDC->SelectObject(m_pBallBrush);

	pDC->Ellipse((CRect*)this);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

void CBall::SetOffset(int offX, int offY)	//ustaw offsety ruchy kulki
{
	m_offX = offX;
	m_offY = offY;
}

void CBall::BounceX(){
	m_offX = -m_offX;
}

void CBall::BounceY(){
	m_offY = -m_offY;
}

void CBall::SetBoundingRect(CRect& rect)
{
	*m_BoundingRect = rect;
}

void CBall::InitObjects(COLORREF ballColor)
{
	m_pBallPen = new CPen();
	m_pBallBrush = new CBrush();
	CreateObjects(ballColor);
}

CRect CBall::getRect(){
	return CRect(this->TopLeft(), this->BottomRight());
}