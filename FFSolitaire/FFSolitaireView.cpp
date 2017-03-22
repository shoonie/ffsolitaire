
// FFSolitaireView.cpp : implementation of the CFFSolitaireView class
//

#include "stdafx.h"
#include "FFSolitaire.h"

#include "FFSolitaireDoc.h"
#include "FFSolitaireView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFFSolitaireView

IMPLEMENT_DYNCREATE(CFFSolitaireView, CView)

BEGIN_MESSAGE_MAP(CFFSolitaireView, CView)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CFFSolitaireView construction/destruction

CFFSolitaireView::CFFSolitaireView()
{
	// TODO: add construction code here

}

CFFSolitaireView::~CFFSolitaireView()
{
}

BOOL CFFSolitaireView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CFFSolitaireView drawing

void CFFSolitaireView::OnDraw(CDC* pDC)
{
	CFFSolitaireDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->DrawPanel(pDC);
	// TODO: add draw code for native data here
}


// CFFSolitaireView diagnostics

#ifdef _DEBUG
void CFFSolitaireView::AssertValid() const
{
	CView::AssertValid();
}

void CFFSolitaireView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFFSolitaireDoc* CFFSolitaireView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFFSolitaireDoc)));
	return (CFFSolitaireDoc*)m_pDocument;
}
#endif //_DEBUG


// CFFSolitaireView message handlers

void CFFSolitaireView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CFFSolitaireDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rtInvalidate1,rtInvalidate2;
	GetClientRect(&rtInvalidate1);
	GetClientRect(&rtInvalidate2);
	int result;
	result = pDoc->CheckPoint(point,rtInvalidate1,rtInvalidate2);
	if(result == 1)
	{	
		InvalidateRect(rtInvalidate1);
	}
	else if(result ==2)
	{
		InvalidateRect(rtInvalidate1);
		InvalidateRect(rtInvalidate2);
	}
	else if(result ==3)
	{
		InvalidateRect(rtInvalidate1);
		InvalidateRect(rtInvalidate2);
	}

	CView::OnLButtonUp(nFlags, point);
}

void CFFSolitaireView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CFFSolitaireDoc* pDoc = GetDocument();

	if(pDoc->CheckDbClick(point))	
		InvalidateRect(NULL);
	CView::OnLButtonDblClk(nFlags, point);
}
