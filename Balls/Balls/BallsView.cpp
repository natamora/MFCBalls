
// BallsView.cpp : implementation of the CBallsView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Balls.h"
#endif

#include "CBall.h"
#include "BallsDoc.h"
#include "BallsView.h"
#include "MainFrm.h"
#include <cstdlib>
#include <atltypes.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBallsView

IMPLEMENT_DYNCREATE(CBallsView, CView)

BEGIN_MESSAGE_MAP(CBallsView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_START, &CBallsView::OnStart)
	ON_COMMAND(ID_ADD, &CBallsView::OnAdd)
	ON_COMMAND(ID_SUB, &CBallsView::OnSub)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_ADD, &CBallsView::OnUpdateAdd)
	ON_UPDATE_COMMAND_UI(ID_SUB, &CBallsView::OnUpdateSub)
END_MESSAGE_MAP()


void CALLBACK ZfxTimerProc(
	HWND hWnd,		// handle of CWnd that called SetTimer
	UINT nMsg,		// WM_TIMER
	UINT nIDEvent,	// timer id
	DWORD dwTime	// system time
	)
{
	::SendMessage(hWnd, WM_TIMER, 0, 0);
}

// CBallsView construction/destruction

CBallsView::CBallsView(){
	srand((unsigned int)time(NULL));
	
	//ustaw przyciski i przygotuj 3 kulki
	m_bStart = FALSE;
	m_bAdd = TRUE;
	m_bSub = FALSE;
	m_pClientRect = new CRect(0, 0, 0, 0);
	countBall = 0;
	m_pBall = (CBall**)malloc(10 * sizeof(CBall*));

	for (int i = 0; i < 3; i++){
		int ballSize = rand() % 91 + 20;
		int r = rand() % 255 + 30;
		int g = rand() % 255 + 30;
		int b = rand() % 255 + 30;		
		m_pBall[i] = new CBall(CPoint(100, 100), CSize(ballSize, ballSize), RGB(r, g, b), rand() % 11 - 5, rand() % 11 - 5);
		countBall++;
	}
}

CBallsView::~CBallsView()
{
	for (int i = 0; i < countBall; i++) 
	{
		delete m_pBall[i];
	}
	delete m_pBall;
	delete m_pClientRect;
	//m_pBall.clear();
	//delete m_pBall;
	//delete m_pClientRect;
}

BOOL CBallsView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// CBallsView drawing

void CBallsView::OnDraw(CDC* pDC)
{

	CDC memDC;
	BOOL b = memDC.CreateCompatibleDC(pDC);
	ASSERT(b);

	CBitmap bmp;
	b = bmp.CreateCompatibleBitmap(pDC, m_pClientRect->Width(), m_pClientRect->Height());
	ASSERT(b);
	CBitmap* pOldBitmap = memDC.SelectObject(&bmp);
	memDC.FillSolidRect(m_pClientRect, RGB(250, 250, 250));

	
	for (int i = 0; i < countBall; i++){
		m_pBall[i]->PaintBall(&memDC);
	}

	b = pDC->BitBlt(0, 0, m_pClientRect->Width(), m_pClientRect->Height(), &memDC, 0, 0, SRCCOPY);
	ASSERT(b);

	//delete
	memDC.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	memDC.DeleteDC();
}

// CBallsView diagnostics

#ifdef _DEBUG
void CBallsView::AssertValid() const
{
	CView::AssertValid();
}

void CBallsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBallsDoc* CBallsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBallsDoc)));
	return (CBallsDoc*)m_pDocument;
}
#endif //_DEBUG


// CBallsView message handlers

void CBallsView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//m_nTimerID = SetTimer(WM_USER + 1, 20, NULL); //milisekundy  WM_TIMER
	m_nTimerID = SetTimer(WM_USER + 1, 30, ZfxTimerProc);

	//GetClientRect(m_pClientRect);
}

void CBallsView::OnTimer(UINT_PTR nIDEvent)
{
	static int nTime = ::GetTickCount();

	int nCurrTime = ::GetTickCount();
	CString s;
	s.Format(L"DeltaT = %d", nCurrTime - nTime);

	nTime = nCurrTime;
	CFrameWnd* pFrame = GetParentFrame();
	pFrame->SetWindowText(s);

	//jesli kliknety start to kulki siê poruszaj¹ -> Bounce offsets
	if (m_bStart)
	{
		for (int i = 0; i < countBall; i++)
		{
			if (m_pBall[i]->right >= m_pClientRect->right)
			{
				m_pBall[i]->BounceX();
				m_pBall[i]->MoveToX(m_pClientRect->right - m_pBall[i]->Size().cx);
			}
			else if (m_pBall[i]->left <= m_pClientRect->left)
			{
				m_pBall[i]->BounceX();
				m_pBall[i]->MoveToX(0);
			}
			if (m_pBall[i]->bottom >= m_pClientRect->bottom)
			{
				m_pBall[i]->BounceY();
				m_pBall[i]->MoveToY(m_pClientRect->bottom - m_pBall[i]->Size().cy);
			}
			else if (m_pBall[i]->top <= m_pClientRect->top)
			{
				m_pBall[i]->BounceY();
				m_pBall[i]->MoveToY(0);
			}

			//przesuwam kulkê
			m_pBall[i]->OffsetRect(m_pBall[i]->m_offX, m_pBall[i]->m_offY);
		}

		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}

void CBallsView::OnStart()
{
	m_bStart = !m_bStart;
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	pFrame->ResetButton(m_bStart);
}

void CBallsView::OnAdd()
{
	if (m_bAdd)
	{
		int r = rand() % 225 + 30;
		int g = rand() % 225 + 30;
		int b = rand() % 225 + 30;
		int offx = 1 + (rand() % 5);
		int offy = 1 + (rand() % 5);
		int ballsize = 30 + (rand() % 91);
		m_pBall[countBall] = new CBall(CPoint(100, 100), CSize(ballsize, ballsize), RGB(r, g, b), offx, offy);
		countBall++;
	}

	if (countBall == 4)
	{
		m_bSub = TRUE;
	}

	if (countBall == 10)
	{
		m_bAdd = FALSE;
	}
}

void CBallsView::OnSub()
{
	if (m_bSub)
	{
		m_pBall[countBall-1] = NULL;
		countBall--;
	}

	if (countBall == 9)
	{
		m_bAdd = TRUE;
	}

	if (countBall == 3)
	{
		m_bSub = FALSE;
	}
}

void CBallsView::OnDestroy()
{
	KillTimer(m_nTimerID);
	CView::OnDestroy();
}

BOOL CBallsView::OnEraseBkgnd(CDC* pDC)
{
	return 1;
}

void CBallsView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	GetClientRect(m_pClientRect);
	CView::OnPrepareDC(pDC, pInfo);
}


void CBallsView::OnUpdateAdd(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bAdd);
}


void CBallsView::OnUpdateSub(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bSub);
}
