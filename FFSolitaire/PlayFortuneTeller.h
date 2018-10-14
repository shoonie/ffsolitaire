#pragma once


#include "player.h"

class CPlayFortuneTeller :public CPlayer
{

	static const int START_X_FORTUNE = 80;
	static const int START_Y_FORTUNE = 50;
	static const int INTERVAL_COLUMNTOCOLUMN_FORTUNE = 160;
	static const int INTERVAL_YTOY_FORTUNE = 50;
	static const int HIDDEN_STARTX_FORTUNE = 120;
	static const int HIDDEN_STARTY_FORTUNE = 400;
	static const int BOARD_STARTX_FORTUNE = 200;
	static const int BOARD_STARTY_FORTUNE = 400;
	static const int BOARD_INTERVAL_FORTUNE = 20;

	static const int CARD_CX = 64;
	static const int CARD_CY = 99;

public:

	enum class SELECTED_COLUMN
	{
		MAIN_COLUMN1,
		MAIN_COLUMN2,
		MAIN_COLUMN3,
		MAIN_COLUMN4,
		BOARD_COLUMN_LEFT,
		BOARD_COLUMN_RIGHT,
		NULL_SELECTED
	};
	enum class COLUMN_NAME
	{
		NAME_MAIN_COLUMN1,
		NAME_MAIN_COLUMN2,
		NAME_MAIN_COLUMN3,
		NAME_MAIN_COLUMN4,
		NAME_SOLVED_COLUMN1,
		NAME_SOLVED_COLUMN2,
		NAME_SOLVED_COLUMN3,
		NAME_SOLVED_COLUMN4,
		NAME_HIDDEN_COLUMN,
		NAME_BOARD_COLUMN
	};

private:

	vector<CCardColumn>	m_MainColumns;
	vector<CCardColumn> m_aSolvedColumn;
	CCardColumn		m_aHiddenColumn;
	CCardColumn		m_aBoardColumn;

	bool			m_bAnyCardSelected;

	SELECTED_COLUMN	m_nSelectedColumn;
	CFlowerCard	*	m_pSelectedCard;
	int				m_nCount;
	int				m_nMatchCount;

	bool PushSolveColumn(CFlowerCard	*SolveCard);
	CCardColumn& GetColumn(COLUMN_NAME name);
	bool FindNewSelectedCard(SELECTED_COLUMN nColumn, CFlowerCard *pCard);
	std::vector<int> GetResult();
public:
	bool	SetMouseRegion();
	bool	ShuffleAndInit();
	int		CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2);

	bool	CheckDbClick(CPoint pt);
	void DrawAll(CDC* pDC);

	CPlayFortuneTeller(CDeck* aDeck);
	virtual ~CPlayFortuneTeller(void);
};
