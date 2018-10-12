#pragma once


#include "FlowerCard.h"
#include "Deck.h"
#include "CardColumn.h"

class CPlayer
{

public:
	CDeck*			m_pSetOfDeck;

	virtual void	DrawAll(CDC* pDC) = 0;
	virtual bool	CheckDbClick(CPoint pt) = 0;
	virtual bool	SetMouseRegion() = 0;
	virtual bool	ShuffleAndInit() = 0;
	virtual int		CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2) = 0;

	CPlayer(CDeck* aDeck);
	virtual ~CPlayer(void);
};
