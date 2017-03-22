// ResultDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FFSolitaire.h"
#include "ResultDlg.h"


// CResultDlg dialog

IMPLEMENT_DYNAMIC(CResultDlg, CDialog)

CResultDlg::CResultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResultDlg::IDD, pParent)
{
	m_nCount		=	0;
	m_nShowNumber	=	1;
	memset(m_nLuckNumber,0,12*4);
}

CResultDlg::~CResultDlg()
{
}

void CResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultDlg)
	DDX_Control(pDX, IDC_BUTTON_PREV, m_BtCtrlPrev);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_BtCtrlNext);
	DDX_Control(pDX, IDC_STORY, m_StCtlrExplain);
	DDX_Control(pDX, IDC_HOWMANY, m_StCtrlExplainHowManyLuck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResultDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTONOK, &CResultDlg::OnBnClickedButtonok)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CResultDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CResultDlg::OnBnClickedButtonPrev)
END_MESSAGE_MAP()


// CResultDlg message handlers

void CResultDlg::OnBnClickedButtonok()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CResultDlg::OnBnClickedButtonNext()
{
	// TODO: Add your control notification handler code here
	m_BtCtrlPrev.EnableWindow(TRUE);
	m_nShowNumber	++;
	if(m_nShowNumber	==	m_nCount)
		m_BtCtrlNext.EnableWindow(FALSE);
	ShowLuckCards(m_nLuckNumber[m_nShowNumber-1]);	
}

void CResultDlg::OnBnClickedButtonPrev()
{
	// TODO: Add your control notification handler code here
	m_BtCtrlNext.EnableWindow(TRUE);
	m_nShowNumber	--;
	if(m_nShowNumber	==	1)
		m_BtCtrlPrev.EnableWindow(FALSE);
	ShowLuckCards(m_nLuckNumber[m_nShowNumber-1]);
}
void CResultDlg::SetLuckCount(int nCount)
{
	m_nCount	=	nCount;
}

void CResultDlg::SetLuckNumber(int *pNumber)
{
	memcpy(m_nLuckNumber,pNumber,m_nCount*4);
}
BOOL CResultDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_StCtrlPicture.Create(NULL, _T(""), WS_VISIBLE, CRect(60,50,60+64,50+99), this, 1);

	if(m_nCount == 0)
	{
		m_StCtrlExplainHowManyLuck.SetWindowText(_T("You Don't Have Any Luck Cards. Sorry"));
		m_BtCtrlPrev.EnableWindow(FALSE);
		m_BtCtrlNext.EnableWindow(FALSE);
		return TRUE;
	}
	else if(m_nCount ==1)
	{
		m_StCtrlExplainHowManyLuck.SetWindowText(_T("You Have Only One Luck Card."));
		m_BtCtrlPrev.EnableWindow(FALSE);
		m_BtCtrlNext.EnableWindow(FALSE);
	}
	else if(m_nCount >1)
	{
		CString s;
		s.Format(_T("You Have %d Luck Cards."),m_nCount);
		m_StCtrlExplainHowManyLuck.SetWindowText(s);
		m_BtCtrlPrev.EnableWindow(FALSE);
		m_BtCtrlNext.EnableWindow(TRUE);
	}
	ShowLuckCards(m_nLuckNumber[0]);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CResultDlg::ShowLuckCards(int nLuckNumber)
{
	
	CString s;
	s.LoadString(IDS_LUCKNUMBER1+nLuckNumber-1);
	m_StCtlrExplain.SetWindowText(s);

	int nCard	= 1000;
	nCard		= nCard + nLuckNumber*10 +1;
	m_StCtrlPicture.SetBitmap(nCard);
	m_StCtrlPicture.Invalidate();
}
