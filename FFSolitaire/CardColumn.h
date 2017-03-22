#pragma once
#include <list>
using namespace std;

#include "FlowerCard.h"

class CCardColumn
{
	CRect	m_rtBoundaryRect;		// Do I still need thsi variable?
	CRect	m_rtLastRect;
	CRect	m_rtLastBeforeRect;
	CRect	m_rtFirstRect;

	list<CFlowerCard*> m_CardList;

	int		m_nCurrentNumberOfCards;
///////////////////////////////////////
//for 12*4 solitare games only;
	CBitmap* m_pBitmapForSelected;	// think it over. if I use this, I have to make something....
///////////////////////////////////////
///////////////////////////////////////
//for 12*4 solitare games only;
	BOOL	m_bHasHidden;
///////////////////////////////////////

public:
	CCardColumn(void);
	~CCardColumn(void);

	BOOL	HasHidden(){return m_bHasHidden;}
	void	SetHiddenOrShow(const BOOL bShow){m_bHasHidden	=	bShow;}

	const CBitmap* GetSelectedBitmap();
	const CBitmap* GetBitmapOfCard(int nIndex);
	const CBitmap* GetHiddenBitmap();
	
	int		GetSize(){return m_nCurrentNumberOfCards;}

	const	CRect& GetBoundaryRect(){return m_rtBoundaryRect;}
	const	CRect& GetLastRect(){return m_rtLastRect;}
	const	CRect& GetLastBeforeRect(){return m_rtLastBeforeRect;}
	const	CRect& GetFirstRect(){return m_rtFirstRect;}

	BOOL	SetBoundaryRect(int x,int y,int cx,int cy);
	BOOL	SetLastRect(int x,int y,int cx,int cy);
	BOOL	SetLastBeforeRect(int x,int y,int cx,int cy);
	BOOL	SetFirstRect(int x,int y,int cx,int cy);

	CFlowerCard * PopLastCard();
	CFlowerCard * ShowLastCard();
	CFlowerCard * ShowLastBeforeCard();
	CFlowerCard * ShowFirstCard();
	CFlowerCard * ShowSecondCard();
	CFlowerCard * ShowThirdCard();
	CFlowerCard * PopFirstCard();

	BOOL	CleanCard();
	BOOL PushCards(CFlowerCard * pCard);

	int	CheckFortuneResult(int Solve[]);
};
