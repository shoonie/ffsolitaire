
// FFSolitaireDoc.cpp : implementation of the CFFSolitaireDoc class
//

#include "stdafx.h"
#include "FFSolitaire.h"

#include "FFSolitaireDoc.h"
#include "selectdlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFFSolitaireDoc

IMPLEMENT_DYNCREATE(CFFSolitaireDoc, CDocument)

BEGIN_MESSAGE_MAP(CFFSolitaireDoc, CDocument)
	ON_COMMAND(ID_FILE_NEW, &CFFSolitaireDoc::OnFileNew)
	ON_COMMAND(ID_CHANGE, &CFFSolitaireDoc::OnGameChange)
	ON_COMMAND(ID_QUIT, &CFFSolitaireDoc::OnQuit)
END_MESSAGE_MAP()


// CFFSolitaireDoc construction/destruction

CFFSolitaireDoc::CFFSolitaireDoc()
{
	// TODO: add one-time construction code here
	m_WhichGame	=	FORTUNE;
	m_pPlay	=	NULL;
}

CFFSolitaireDoc::~CFFSolitaireDoc()
{
	if (m_pPlay)
		delete m_pPlay;
}

BOOL CFFSolitaireDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	if(m_pPlay)
	{
		delete m_pPlay;
		m_pPlay	=	NULL;
	}

	switch(m_WhichGame)
	{
	case FORTUNE:
		m_pPlay	=	new CPlayFortuneTeller();
		AfxGetMainWnd()->SetWindowPos(NULL,10,10,800,700,0);
		break;
	case GAME12:
		m_pPlay	=	new CPlay4BY6();
		AfxGetMainWnd()->SetWindowPos(NULL,10,10,800,700,0);
		break;
	case GAME8:
		m_pPlay	=	new CPlay8By6();
		AfxGetMainWnd()->SetWindowPos(NULL,10,10,1000,700,0);
		break;
	}
	if(m_pPlay)
	{
		m_pPlay->ShuffleAndInit();
		m_pPlay->SetMouseRegion();
	}
	AfxGetMainWnd()->GetActiveWindow()->Invalidate(NULL);
	return TRUE;
}




// CFFSolitaireDoc serialization

void CFFSolitaireDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CFFSolitaireDoc diagnostics

#ifdef _DEBUG
void CFFSolitaireDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFFSolitaireDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFFSolitaireDoc commands
void CFFSolitaireDoc::DrawPanel(CDC* pDC)
{
	if(m_pPlay)
		m_pPlay->DrawAll( pDC);
}

int CFFSolitaireDoc::CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2)
{
	if(m_pPlay)
		return m_pPlay->CheckPoint( pt,rt1,rt2);
	else
		return 0;
}
BOOL CFFSolitaireDoc::CheckDbClick(CPoint pt)
{
	if(m_pPlay)
		return m_pPlay->CheckDbClick( pt);
	else
		return 0;
}
void CFFSolitaireDoc::OnFileNew()
{
	if(m_pPlay)
	{
		m_pPlay->ShuffleAndInit();
		m_pPlay->SetMouseRegion();
	}
	AfxGetMainWnd()->GetActiveWindow()->Invalidate(NULL);
}
void CFFSolitaireDoc::OnGameChange()
{
	CSelectDlg	dlg;
	dlg.DoModal();
	m_WhichGame	=	(WHAT_GAME_TO_PLAY)dlg.nSelect;
	OnNewDocument();
}
void CFFSolitaireDoc::OnQuit()
{
	PostQuitMessage(0);
}
