#pragma once


// CSelectDlg dialog

class CSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectDlg)

public:
	CSelectDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectDlg();
	int nSelect;
// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonfortune();
	afx_msg void OnBnClickedButton124();
	afx_msg void OnBnClickedButton86();
};
