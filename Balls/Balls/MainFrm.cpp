
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Balls.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

UINT CMainFrame::m_buttonsIDs[] =
{
	ID_START,
	ID_ADD,
	ID_SUB
};
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||				// wykreowaæ
		!m_wndToolBar.LoadBitmap(ID_MYTOOLBAR) ||	// za³adowaæ bitmape
		!m_wndToolBar.SetButtons(m_buttonsIDs, sizeof(m_buttonsIDs) / sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	CToolBarCtrl& BarCtrl = m_wndToolBar.GetToolBarCtrl();
	BarCtrl.SetBitmapSize(CSize(31, 29));	// ustawiæ rozmiar obrazka
	BarCtrl.SetButtonSize(CSize(39, 36));	// cx+8, cy+7


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

void CMainFrame::ResetButton(BOOL b)
{
	int buttonIx = sizeof(m_buttonsIDs) / sizeof(UINT);
	if (b)
		m_wndToolBar.SetButtonInfo(0, ID_START, TBBS_BUTTON, buttonIx);
	else
		m_wndToolBar.SetButtonInfo(0, ID_START, TBBS_BUTTON, 0);
	m_wndToolBar.Invalidate();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

