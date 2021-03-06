#pragma once
#include "player.h"

class CPlay4BY6 :
	public CPlayer
{
	const static int START_X_1_4BY12 = 10;
	const static int START_Y_1_4BY12 = 10;
	const static int START_X_2_4BY12 = 210;
	const static int START_Y_2_4BY12 = 350;
	const static int INTERVAL_COLUMNTOCOLUMN_4BY12 = 100;
	const static int INTERVAL_YTOY_4BY12 = 30;
	const static int HIDDEN_STARTX_4BY12 = 20;
	const static int HIDDEN_STARTY_4BY12 = 350;
	const static int CARD_CX = 64;
	const static int CARD_CY = 99;

	vector<CCardColumn>	m_MainColumns;
	CCardColumn	m_HiddenColumn;

	bool m_bAnyCardSelected;

	int	m_nCount;
	int	m_nSelectedColumn;
	shared_ptr<CFlowerCard> m_pSelectedCard;

public:
	bool SetMouseRegion() override;
	bool ShuffleAndInit() override;
	int CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2) override;
	bool CheckDbClick(CPoint pt) override;
	void DrawAll(CDC* pDC) override;

	CPlay4BY6(CDeck* aDeck);
	virtual ~CPlay4BY6(void);
};
