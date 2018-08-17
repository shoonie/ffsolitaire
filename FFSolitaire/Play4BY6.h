#pragma once
#include "player.h"

class CPlay4BY6 :
	public CPlayer
{
	const static int	START_X_1_4BY12					=	10;
	const static int	START_Y_1_4BY12					=	10;
	const static int	START_X_2_4BY12					=	210;
	const static int	START_Y_2_4BY12					=	350;
	const static int	INTERVAL_COLUMNTOCOLUMN_4BY12	=	100;
	const static int	INTERVAL_YTOY_4BY12				=	30;
	const static int	HIDDEN_STARTX_4BY12				=	20;
	const static int	HIDDEN_STARTY_4BY12				=	350;
	const static int	CARD_CX							=	64;
	const static int	CARD_CY							=	99;

	CCardColumn		m_aMainColumn[12];
	CCardColumn		m_HiddenColumn;
	
	bool			m_bAnyCardSelected;

	int				m_nCount;
	int				m_nSelectedColumn;
	CFlowerCard	*	m_pSelectedCard;

public:

	bool	SetMouseRegion();
	bool	ShuffleAndInit();
	int		CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2);
	bool	CheckDbClick(CPoint pt);
	void	DrawAll(CDC* pDC);

	CPlay4BY6(void);
	virtual ~CPlay4BY6(void);
};
