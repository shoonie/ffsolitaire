#pragma once
/////////////////////////////////////////////////////////////////////////////
// CCtrlBitmapDisplay window

class CCtrlBitmapDisplay : public CWnd
{
	CBitmap	m_Bitmap;
// Construction
public:
	CCtrlBitmapDisplay();

// Attributes
public:

// Operations
public:
	BOOL SetBitmap(UINT nIDResource);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCtrlBitmapDisplay)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCtrlBitmapDisplay();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCtrlBitmapDisplay)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

