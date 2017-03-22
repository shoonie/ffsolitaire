
// FFSolitaireView.h : interface of the CFFSolitaireView class
//


#pragma once


class CFFSolitaireView : public CView
{
protected: // create from serialization only
	CFFSolitaireView();
	DECLARE_DYNCREATE(CFFSolitaireView)

// Attributes
public:
	CFFSolitaireDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CFFSolitaireView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in FFSolitaireView.cpp
inline CFFSolitaireDoc* CFFSolitaireView::GetDocument() const
   { return reinterpret_cast<CFFSolitaireDoc*>(m_pDocument); }
#endif

