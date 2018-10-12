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

CFlowerCard& CFlowerCard::operator =(const CFlowerCard & AssignCard)
{
	if (&AssignCard == this)
		return *this;
	m_nID = AssignCard.m_nID;
	SetPositionAndNumber();
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
	if (m_nNumber > 0 && m_nNumber < 13 && m_nPosition > 0 && m_nPosition < 5)
	{
		m_pBitmap->DeleteObject();
		int nResource = 1000 + m_nNumber * 10 + m_nPosition * 1;
		if (m_pBitmap->LoadBitmap(nResource))
			return m_pBitmap;
		else
			return nullptr;
	}
	else
		return nullptr;
}

const unique_ptr<CBitmap>& CFlowerCard::GetHiddenBitmap()
{
	if (m_nNumber > 0 && m_nNumber < 13 && m_nPosition > 0 && m_nPosition < 5)
	{
		m_pBitmap->DeleteObject();
		if (m_pBitmap->LoadBitmap(IDB_BITMAP_HIDDEN))
			return m_pBitmap;
		else
			return nullptr;
	}
	else
		return nullptr;
}
