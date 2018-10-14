#pragma once
#include "player.h"

class CPlay8By6 :
	public CPlayer
{
	static const int START_X_1_4BY12 = 10;
	static const int START_Y_1_4BY12 = 10;
	static const int START_X_2_4BY12 = 210;
	static const int START_Y_2_4BY12 = 350;
	static const int INTERVAL_COLUMNTOCOLUMN_4BY12 = 100;
	static const int INTERVAL_YTOY_4BY12 = 30;
	static const int HIDDEN_STARTX_4BY12 = 20;
	static const int HIDDEN_STARTY_4BY12 = 350;

	static const int START_X_1_8BY6 = 390;
	static const int START_Y_1_8BY6 = 20;
	static const int START_X_2_8BY6 = 540;
	static const int START_Y_2_8BY6 = 20;

	static const int INTERVAL_XTOX_8BY6 = 25;
	static const int INTERVAL_YTOY_8BY6 = 120;

	static const int START_SOLVE_X_8BY6 = 465;
	static const int START_SOLVE_Y_8BY6 = 20;
	
	static const int CARD_CX = 64;
	static const int CARD_CY = 99;

	vector<CCardColumn> m_MainColumns;

	bool m_bAnyCardSelected;

	int m_nSelectedColumn;
	CFlowerCard* m_pSelectedCard;
	int	m_nCount;

public:
	bool SetMouseRegion() override;
	bool ShuffleAndInit() override;
	int	CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2) override;
	bool CheckDbClick(CPoint pt) override { return false; }
	void DrawAll(CDC* pDC) override;

	CPlay8By6(CDeck* aDeck);
	virtual ~CPlay8By6(void);
};
