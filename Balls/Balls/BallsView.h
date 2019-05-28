
// BallsView.h : interface of the CBallsView class
//

#pragma once

#include "CBall.h"
#include <vector>

class CBallsView : public CView
{
protected: // create from serialization only
	CBallsView();
	DECLARE_DYNCREATE(CBallsView)

// Attributes
public:
	CBallsDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CBallsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	UINT m_nTimerID;
	CRect* m_pClientRect;
	BOOL m_bStart;
	BOOL m_bAdd;
	BOOL m_bSub;
	CBall** m_pBall;
	int countBall;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnStart();
	afx_msg void OnAdd();
	afx_msg void OnSub();
	virtual void OnInitialUpdate();
	afx_msg void OnUpdateAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSub(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // debug version in BallsView.cpp
inline CBallsDoc* CBallsView::GetDocument() const
   { return reinterpret_cast<CBallsDoc*>(m_pDocument); }
#endif

