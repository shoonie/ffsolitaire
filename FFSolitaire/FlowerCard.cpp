#include "StdAfx.h"
#include "FlowerCard.h"
#include "resource.h"		///for load bitmap...

CFlowerCard::CFlowerCard(int nID) :m_nID(nID)
{
	if (!SetPositionAndNumber())
	{
		m_nNumber = 0;
		m_nPosition = 0;
	}
}

CFlowerCard::~CFlowerCard(void)
{
	m_pBitmap->DeleteObject();
}

CFlowerCard::CFlowerCard(const CFlowerCard & CopyCard)
{
	m_nID = CopyCard.m_nID;
	SetPositionAndNumber();
}

CFlowerCard::CFlowerCard(CFlowerCard && moveCard)
{
	m_pBitmap = move(moveCard.m_pBitmap);
	m_nID = moveCard.m_nID;
	SetPositionAndNumber();
}

CFlowerCard& CFlowerCard::operator =(const CFlowerCard & AssignCard)
{
	if (&AssignCard == this)
		return *this;
	m_nID = AssignCard.m_nID;
	SetPositionAndNumber();
	return *this;
}

CFlowerCard& CFlowerCard::operator=(CFlowerCard && moveCard)
{
	if (this != &moveCard)
	{
		m_pBitmap->DeleteObject();
		m_pBitmap = move(moveCard.m_pBitmap);
		m_nID = moveCard.m_nID;
		SetPositionAndNumber();
	}
	return *this;
}

const bool CFlowerCard::SetPositionAndNumber()
{
	if (m_nID >= 0 && m_nID < 48)
	{
		m_nNumber = m_nID / 4 + 1;
		m_nPosition = m_nID % 4 + 1;
		return true;
	}
	else
		return false;
}

bool CFlowerCard::SetID(const int nNumber)
{
	m_nID = nNumber;
	if (SetPositionAndNumber())
		return true;
	else
	{
		m_nNumber = 0;
		m_nPosition = 0;
		return false;
	}
}

const unique_ptr<CBitmap>& CFlowerCard::GetBitmap()
{
	m_pBitmap->DeleteObject();
	int nResource = 1000 + m_nNumber * 10 + m_nPosition * 1;
	m_pBitmap->LoadBitmap(nResource);
	return m_pBitmap;
}

const unique_ptr<CBitmap>& CFlowerCard::GetHiddenBitmap()
{
	m_pBitmap->DeleteObject();
	m_pBitmap->LoadBitmap(IDB_BITMAP_HIDDEN);
	return m_pBitmap;
}
//doing some job here
