#include "StdAfx.h"
#include "FlowerCard.h"
#include "resource.h"		///for load bitmap...

CFlowerCard::CFlowerCard(int nID)
{
	m_nID	=	nID;
	if(!SetPositionAndNumber())
	{
		m_nNumber	=	0;
		m_nPosition	=	0;
	}
	m_pBitmap	=	NULL;
}

CFlowerCard::CFlowerCard(const CFlowerCard & CopyCard)
{
	m_nID		=	CopyCard.m_nID;
	SetPositionAndNumber();

	if(CopyCard.m_pBitmap)
	{
		m_pBitmap	=	new CBitmap();
		int nResource = 1000 + m_nNumber*10 +m_nPosition*1;
		m_pBitmap->LoadBitmap(nResource);
	}
	else 
		m_pBitmap	=	NULL;

}

CFlowerCard& CFlowerCard::operator =(const CFlowerCard & AssignCard)
{
	if(&AssignCard	==	this)
		return *this;
	m_nID		=	AssignCard.m_nID;
	SetPositionAndNumber();
	if(this->m_pBitmap)
		DeleteBitmap();
	if(AssignCard.m_pBitmap)
	{
		m_pBitmap	=	new CBitmap();
		int nResource = 1000 + m_nNumber*10 +m_nPosition*1;
		m_pBitmap->LoadBitmap(nResource);
	}
	else 
		m_pBitmap	=	NULL;

	return *this;
}

CFlowerCard::~CFlowerCard(void)
{
	DeleteBitmap();
}

const BOOL CFlowerCard::SetPositionAndNumber()
{
	if(m_nID >= 0 && m_nID <48)
	{
		m_nNumber	= m_nID/4 +1;
		m_nPosition	= m_nID%4 +1;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CFlowerCard::SetID(const int nNumber)
{
	m_nID	= nNumber;
	if(SetPositionAndNumber())
		return TRUE;
	else
	{
		m_nNumber	=	0;
		m_nPosition	=	0;
		return FALSE;
	}
}

const CBitmap* CFlowerCard::GetBitmap()
{
	if(m_nNumber > 0 && m_nNumber <13 && m_nPosition > 0 && m_nPosition <5) 
	{
		DeleteBitmap();
		m_pBitmap	=	new CBitmap();
		
		int nResource = 1000 + m_nNumber*10 +m_nPosition*1;

		m_pBitmap->LoadBitmap(nResource);
		
		return m_pBitmap;
	}
	else
		return NULL;
}

const CBitmap* CFlowerCard::GetHiddenBitmap()
{
	if(m_nNumber > 0 && m_nNumber <13 && m_nPosition > 0 && m_nPosition <5) 
	{
		DeleteBitmap();
		m_pBitmap	=	new CBitmap();
		
		m_pBitmap->LoadBitmap(IDB_BITMAP_HIDDEN);
		
		return m_pBitmap;
	}
	else
		return NULL;
}

void CFlowerCard::DeleteBitmap()
{
	if(m_pBitmap)
	{
		m_pBitmap->DeleteObject();
		delete	m_pBitmap;
		m_pBitmap	=	NULL;
	}
}