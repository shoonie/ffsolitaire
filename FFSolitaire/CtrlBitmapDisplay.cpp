// CtrlBitmapDisplay.cpp : implementation file
//

#include "stdafx.h"
#include "CtrlBitmapDisplay.h"

/////////////////////////////////////////////////////////////////////////////
// CCtrlBitmapDisplay

CCtrlBitmapDisplay::CCtrlBitmapDisplay()
{
}

CCtrlBitmapDisplay::~CCtrlBitmapDisplay()
{
}


BEGIN_MESSAGE_MAP(CCtrlBitmapDisplay, CWnd)
	//{{AFX_MSG_MAP(CCtrlBitmapDisplay)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCtrlBitmapDisplay message handlers


BOOL CCtrlBitmapDisplay::SetBitmap(UINT nIDResource)
{
	m_Bitmap.DeleteObject();
    return m_Bitmap.LoadBitmap(nIDResource);
}
void CCtrlBitmapDisplay::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting

    if (m_Bitmap.GetSafeHandle() != NULL)
    {
	    CPaintDC dc(this); // device context for painting

        // Create memory DC
        CDC MemDC;
        if (!MemDC.CreateCompatibleDC(&dc))
            return;

        CBitmap* pOldBitmap = (CBitmap*) MemDC.SelectObject(&m_Bitmap);
        dc.BitBlt(0, 0, 64, 99, 
                      &MemDC, 
                      0, 0, 
                      SRCCOPY);
        MemDC.SelectObject(pOldBitmap);      
    }


	// Do not call CStatic::OnPaint() for painting messages
}

BOOL CCtrlBitmapDisplay::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
   // If we have an image then don't perform any erasing, since the OnPaint
    // function will simply draw over the background
    if (m_Bitmap.GetSafeHandle() != NULL)
        return TRUE;
	
    // Obviously we don't have a bitmap - let the base class deal with it.
	return CWnd::OnEraseBkgnd(pDC);
	
}



