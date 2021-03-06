#pragma once
#include <list>
using namespace std;
#include "resource.h"
// CResultDlg dialog
#include "CtrlBitmapDisplay.h"
#include <vector>
class CResultDlg : public CDialog
{
	DECLARE_DYNAMIC(CResultDlg)
	std::vector<int> m_nLuckNumbers;
	int m_nCount;
	int	m_nShowNumber;
	CCtrlBitmapDisplay	m_StCtrlPicture;
public:
	CResultDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CResultDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_RESULT };
	CButton	m_CtrlPic;
	CButton	m_BtCtrlPrev;
	CButton	m_BtCtrlNext;
	CStatic	m_StCtlrExplain;
	CStatic	m_StCtrlExplainHowManyLuck;

	void ShowLuckCards(int nLuckNumber);
	void SetLuckNumber(std::vector<int> Numbers);
	void SetLuckCount(int nCount);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonok();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonPrev();
	virtual BOOL OnInitDialog();
};
