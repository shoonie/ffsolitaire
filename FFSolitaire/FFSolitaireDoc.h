
// FFSolitaireDoc.h : interface of the CFFSolitaireDoc class
//


#pragma once
#include "playFortuneteller.h"
#include "play4By6.h"
#include "play8By6.h"

class CFFSolitaireDoc : public CDocument
{
	enum class WHAT_GAME_TO_PLAY
	{
		FORTUNE	=	1,
		GAME12,
		GAME8
	};
	CPlayer	* m_pPlay;
	WHAT_GAME_TO_PLAY m_WhichGame;
protected: // create from serialization only
	CFFSolitaireDoc();
	DECLARE_DYNCREATE(CFFSolitaireDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	void DrawPanel(CDC* pDC);
	int CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2);
	bool CheckDbClick(CPoint pt);
// Implementation
public:
	virtual ~CFFSolitaireDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileNew();
	afx_msg void OnGameChange();
	afx_msg void OnQuit();
};


