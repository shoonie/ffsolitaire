#pragma once


#include "FlowerCard.h"
#include "Deck.h"
#include "CardColumn.h"

class CPlayer
{

public:
	CDeck			m_aSetOfDeck;

	virtual void	DrawAll(CDC* pDC)=0;
	virtual BOOL	CheckDbClick(CPoint pt)=0;
	virtual BOOL	SetMouseRegion()=0;
	virtual BOOL	ShuffleAndInit()=0;
	virtual int		CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2)=0;

	CPlayer(void);
	virtual ~CPlayer(void);
};
