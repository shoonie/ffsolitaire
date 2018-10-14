#include "StdAfx.h"
#include "CardColumn.h"
#include "resource.h"
#include <vector>
#include <algorithm>
using namespace std;

CCardColumn::CCardColumn(void) :
	m_nCurrentNumberOfCards(0),
	m_bHasHidden(true)
{
}

CCardColumn::~CCardColumn(void)
{
	m_pBitmapForSelected->DeleteObject();
}

CCardColumn::CCardColumn(const CCardColumn & CopyCard)
{
	m_nCurrentNumberOfCards = CopyCard.m_nCurrentNumberOfCards;
	m_bHasHidden = CopyCard.m_bHasHidden;
}

CCardColumn& CCardColumn::operator =(const CCardColumn & AssignCard)
{
	if (&AssignCard == this)
		return *this;
	m_nCurrentNumberOfCards = AssignCard.m_nCurrentNumberOfCards;
	m_bHasHidden = AssignCard.m_bHasHidden;
	return *this;
}

bool CCardColumn::PushCards(shared_ptr<CFlowerCard>pCard)
{
	m_CardList.push_back(pCard);
	m_nCurrentNumberOfCards++;
	return true;
}

shared_ptr<CFlowerCard> CCardColumn::PopFirstCard()
{
	if (m_nCurrentNumberOfCards == 0)
		return nullptr;

	auto pTemp = m_CardList.front();
	m_CardList.pop_front();
	m_nCurrentNumberOfCards--;
	return pTemp;
}

shared_ptr<CFlowerCard> CCardColumn::PopLastCard()
{
	auto pTemp = m_CardList.back();
	m_CardList.pop_back();
	m_nCurrentNumberOfCards--;
	return pTemp;
}

shared_ptr<CFlowerCard> CCardColumn::ShowFirstCard()
{
	if (m_nCurrentNumberOfCards == 0)
		return nullptr;
	return m_CardList.front();
}

shared_ptr<CFlowerCard> CCardColumn::ShowSecondCard()
{
	if (m_nCurrentNumberOfCards < 2)
		return nullptr;

	auto pFCList_Iter = m_CardList.cbegin();
	pFCList_Iter++;
	return *pFCList_Iter;
}

shared_ptr<CFlowerCard> CCardColumn::ShowThirdCard()
{
	if (m_nCurrentNumberOfCards < 3)
		return nullptr;

	auto pFCList_Iter = m_CardList.cbegin();
	pFCList_Iter++;
	pFCList_Iter++;
	return *pFCList_Iter;
}

shared_ptr<CFlowerCard> CCardColumn::ShowLastBeforeCard()
{
	if (m_nCurrentNumberOfCards < 2)
		return nullptr;
	auto pFCList_Iter = m_CardList.cend();
	pFCList_Iter--;
	pFCList_Iter--;
	return *pFCList_Iter;
}

const unique_ptr<CBitmap>& CCardColumn::GetSelectedBitmap()
{
	m_pBitmapForSelected->DeleteObject();
	m_pBitmapForSelected->LoadBitmap(IDB_BITMAP_SELECTED);
	return m_pBitmapForSelected;
}
const unique_ptr<CBitmap>& CCardColumn::GetBitmapOfCard(int nIndex)
{
	auto pFCList_Iter = m_CardList.cbegin();
	for (int i = 0; i < nIndex; ++i)
		pFCList_Iter++;
	auto aCard = *pFCList_Iter;
	return aCard->GetBitmap();
}

const unique_ptr<CBitmap>& CCardColumn::GetHiddenBitmap()
{
	return  m_CardList.back()->GetHiddenBitmap();
}

std::vector<int> CCardColumn::CheckFortuneResult()
{
	vector<int> vtAllResult;
	vector<int> vtResult;
	std::for_each(m_CardList.begin(), m_CardList.end(), [&vtAllResult](auto aCard) { vtAllResult.push_back(aCard->GetNumber()); });

	for (int i = 1; i <= 12; ++i) {
		if (4 == (int)count(vtAllResult.begin(), vtAllResult.end(), i))
			vtResult.push_back(i);
	}
	return vtResult;
}


bool	CCardColumn::SetBoundaryRect(int x, int y, int cx, int cy)
{
	m_rtBoundaryRect.top = y;
	m_rtBoundaryRect.left = x;
	m_rtBoundaryRect.right = x + cx;
	m_rtBoundaryRect.bottom = y + cy;
	return true;
}
bool	CCardColumn::SetLastRect(int x, int y, int cx, int cy)
{
	m_rtLastRect.top = y;
	m_rtLastRect.left = x;
	m_rtLastRect.right = x + cx;
	m_rtLastRect.bottom = y + cy;
	return true;
}

bool	CCardColumn::SetLastBeforeRect(int x, int y, int cx, int cy)
{
	m_rtLastBeforeRect.top = y;
	m_rtLastBeforeRect.left = x;
	m_rtLastBeforeRect.right = x + cx;
	m_rtLastBeforeRect.bottom = y + cy;
	return true;
}

bool	CCardColumn::SetFirstRect(int x, int y, int cx, int cy)
{
	m_rtFirstRect.top = y;
	m_rtFirstRect.left = x;
	m_rtFirstRect.right = x + cx;
	m_rtFirstRect.bottom = y + cy;
	return true;
}
bool CCardColumn::CleanCard()
{
	m_CardList.clear();
	m_nCurrentNumberOfCards = 0;
	m_bHasHidden = true;
	return true;
}