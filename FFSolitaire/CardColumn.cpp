#include "StdAfx.h"
#include "CardColumn.h"
#include "resource.h"

#define USINGVECTOR

#ifdef USINGVECTOR
#include <vector>
#include <algorithm>
using namespace std;
#endif

CCardColumn::CCardColumn(void)
{
	m_nCurrentNumberOfCards	=	0;
///////////////////////////////////////
//for 12*4 solitare games only;
	m_pBitmapForSelected	=	NULL;
///////////////////////////////////////
///////////////////////////////////////
//for 12*4 solitare games only;
	m_bHasHidden			=	TRUE;
///////////////////////////////////////
}

CCardColumn::~CCardColumn(void)
{
	if(m_pBitmapForSelected)
	{
		m_pBitmapForSelected->DeleteObject();
		delete m_pBitmapForSelected;
		m_pBitmapForSelected	=	NULL;
	}
}

BOOL CCardColumn::PushCards(CFlowerCard *pCard)
{
	m_CardList.push_back(pCard);
	m_nCurrentNumberOfCards	++;
	return TRUE;
}
CFlowerCard * CCardColumn::PopFirstCard()
{
	if (m_nCurrentNumberOfCards == 0)
		return NULL;

	CFlowerCard * pTemp;
	pTemp	=	m_CardList.front();
	m_CardList.pop_front();
	m_nCurrentNumberOfCards	--;
	return pTemp;
}

CFlowerCard * CCardColumn::PopLastCard()
{
	if (m_nCurrentNumberOfCards == 0)
		return NULL;

	CFlowerCard * pTemp;
	pTemp	=	m_CardList.back();
	m_CardList.pop_back();
	m_nCurrentNumberOfCards	--;
	return pTemp;
}

CFlowerCard * CCardColumn::ShowLastCard()
{
	if (m_nCurrentNumberOfCards == 0)
		return NULL;

	CFlowerCard * pTemp;
	pTemp	=	m_CardList.back();
	return pTemp;
}
CFlowerCard * CCardColumn::ShowFirstCard()
{
	if (m_nCurrentNumberOfCards == 0)
		return NULL;

	CFlowerCard * pTemp;
	pTemp	=	m_CardList.front();
	return pTemp;
}
CFlowerCard * CCardColumn::ShowSecondCard()
{
	if (m_nCurrentNumberOfCards < 2)
		return NULL;

	list <CFlowerCard*>::iterator pFCList_Iter;
	pFCList_Iter	=	m_CardList.begin();
	pFCList_Iter ++;
	CFlowerCard * pTemp	= *pFCList_Iter;
	return pTemp;
}
CFlowerCard * CCardColumn::ShowThirdCard()
{
	if (m_nCurrentNumberOfCards <3)
		return NULL;

	list <CFlowerCard*>::iterator pFCList_Iter;
	pFCList_Iter	=	m_CardList.begin();
	pFCList_Iter ++;
	pFCList_Iter ++;
	CFlowerCard * pTemp	= *pFCList_Iter;
	return pTemp;
}

CFlowerCard * CCardColumn::ShowLastBeforeCard()
{
	if (m_nCurrentNumberOfCards <	2)
		return NULL;
	list <CFlowerCard*>::iterator pFCList_Iter;
	pFCList_Iter	=	m_CardList.end();
	pFCList_Iter --;
	pFCList_Iter --;
	CFlowerCard * pTemp	= *pFCList_Iter;
	return pTemp;
}

const CBitmap* CCardColumn::GetSelectedBitmap()
{
	if(m_pBitmapForSelected)
	{
		m_pBitmapForSelected->DeleteObject();
		delete m_pBitmapForSelected;
		m_pBitmapForSelected	=	NULL;
	}
	m_pBitmapForSelected = new CBitmap();
	m_pBitmapForSelected->LoadBitmap(IDB_BITMAP_SELECTED);
	return m_pBitmapForSelected;
}
const CBitmap* CCardColumn::GetBitmapOfCard(int nIndex)
{
	if (m_nCurrentNumberOfCards == 0)
		return NULL;
	list <CFlowerCard*>::iterator pFCList_Iter;
	pFCList_Iter	=	m_CardList.begin();
	for(int i=0;i<nIndex;i++)
		pFCList_Iter++;
	CFlowerCard	* aCard	=	*pFCList_Iter;
	return aCard->GetBitmap();
}
const CBitmap* CCardColumn::GetHiddenBitmap()
{
	if (m_nCurrentNumberOfCards == 0)
		return NULL;
	return  m_CardList.back()->GetHiddenBitmap();
}

int	CCardColumn::CheckFortuneResult(int Solve[])
{
	vector<int> vtResult;
	int i;
	int nRetCount=	0;
	list <CFlowerCard*>::iterator pFCList_Iter	=	m_CardList.begin();
	for(i=0;i<12;i+=2)
	{
		pFCList_Iter++;
		CFlowerCard	* aCard	=	*pFCList_Iter;
		vtResult.push_back(aCard->GetNumber());
		pFCList_Iter++;
	}
	sort(vtResult.begin(),vtResult.end());
	auto Int_Iter	=	vtResult.begin();
	for(i=0;i<5;i++)
	{
		int first	=	*Int_Iter;
		Int_Iter++;
		int second	=	*Int_Iter;
		if(first	==	second)
		{
			Solve[nRetCount++] = first;
		}

	}
	return nRetCount;
}


BOOL	CCardColumn::SetBoundaryRect(int x,int y,int cx,int cy)
{
	m_rtBoundaryRect.top		=	y;
	m_rtBoundaryRect.left		=	x;
	m_rtBoundaryRect.right		=	x+cx;
	m_rtBoundaryRect.bottom		=	y+cy;
	return TRUE;
}
BOOL	CCardColumn::SetLastRect(int x,int y,int cx,int cy)
{
	m_rtLastRect.top		=	y;
	m_rtLastRect.left		=	x;
	m_rtLastRect.right		=	x+cx;
	m_rtLastRect.bottom		=	y+cy;
	return TRUE;
}

BOOL	CCardColumn::SetLastBeforeRect(int x,int y,int cx,int cy)
{
	m_rtLastBeforeRect.top			=	y;
	m_rtLastBeforeRect.left			=	x;
	m_rtLastBeforeRect.right		=	x+cx;
	m_rtLastBeforeRect.bottom		=	y+cy;
	return TRUE;
}

BOOL	CCardColumn::SetFirstRect(int x,int y,int cx,int cy)
{
	m_rtFirstRect.top			=	y;
	m_rtFirstRect.left			=	x;
	m_rtFirstRect.right			=	x+cx;
	m_rtFirstRect.bottom		=	y+cy;
	return TRUE;
}
BOOL CCardColumn::CleanCard()
{
	m_CardList.clear();
	m_nCurrentNumberOfCards	=	0;
	m_bHasHidden			=	TRUE;
	return TRUE;
}