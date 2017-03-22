// SelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FFSolitaire.h"
#include "SelectDlg.h"


// CSelectDlg dialog

IMPLEMENT_DYNAMIC(CSelectDlg, CDialog)

CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDlg::IDD, pParent)
{

}

CSelectDlg::~CSelectDlg()
{
}

void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTONFORTUNE, &CSelectDlg::OnBnClickedButtonfortune)
	ON_BN_CLICKED(IDC_BUTTON124, &CSelectDlg::OnBnClickedButton124)
	ON_BN_CLICKED(IDC_BUTTON86, &CSelectDlg::OnBnClickedButton86)
END_MESSAGE_MAP()


// CSelectDlg message handlers

void CSelectDlg::OnBnClickedButtonfortune()
{
	nSelect	=1;
	OnOK();
}

void CSelectDlg::OnBnClickedButton124()
{
	nSelect =2;
	OnOK();
}

void CSelectDlg::OnBnClickedButton86()
{
	nSelect	=3;
	OnOK();
}
