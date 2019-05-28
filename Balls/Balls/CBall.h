#pragma once

#include <atltypes.h>

#define BLACK RGB(0,0,0)
#define WHITE RGB(255,255,255)

class CBall : public CRect
{
public:
	CBall(const CRect&, COLORREF ballColor = BLACK, int offX = 0, int offY = 0);
	CBall(const CPoint&, const CSize&, COLORREF ballColor = BLACK, int offX = 0, int offY = 0);
	CBall(int = 0, int = 0, int = 0, int = 0, COLORREF ballColor = BLACK, int offX = 0, int offY = 0);

	~CBall();

public:
	inline void SetColor(COLORREF ballColor);			//ustaw kolor kulki (Delete - kasowaæ obiekty graficzne, nie z pamiêci), potem create
	inline  void SetBallSize(const CRect& Rect);		//ustaw wielkosc kulki (ref do recta)
	void PaintBall(CDC *pDC);							//narysuj kulkê
	void SetOffset(int offX, int offY);					//ustaw offsety ruchu kulki
	void SetBoundingRect(CRect& rect);					//ustaw widoczny obszar

	CRect getRect();
	void BounceX();
	void BounceY();
private:
	inline void CreateObjects(COLORREF ballColor = BLACK);
	inline void DeleteObjects();
	void InitObjects(COLORREF ballColor = BLACK);

private:
	CPen* m_pBallPen;
	CBrush* m_pBallBrush;

public:
	int m_offX;
	int m_offY;
	CRect* m_BoundingRect;
};

inline void CBall::SetColor(COLORREF ballColor)
{
	DeleteObjects();
	CreateObjects(ballColor);
}

inline void CBall::SetBallSize(const CRect& rect)
{
	*(CRect*)this = rect;
}

inline void CBall::CreateObjects(COLORREF ballColor)
{
	m_pBallPen->CreatePen(PS_SOLID, 1, ballColor);
	m_pBallBrush->CreateSolidBrush(ballColor);
}

inline void CBall::DeleteObjects()
{
	m_pBallPen->DeleteObject();
	m_pBallBrush->DeleteObject();
}

