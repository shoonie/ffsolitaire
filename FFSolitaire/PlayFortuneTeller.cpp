#include "StdAfx.h"
#include "PlayFortuneTeller.h"
#include "Resultdlg.h"
CPlayFortuneTeller::CPlayFortuneTeller(CDeck* aDeck) :
	CPlayer(aDeck),
	m_bAnyCardSelected(false),
	m_nSelectedColumn(SELECTED_COLUMN::NULL_SELECTED),
	m_nCount(0),
	m_nMatchCount(0)
{
	m_MainColumns.resize(4);
	m_aSolvedColumn.resize(4);
}

CPlayFortuneTeller::~CPlayFortuneTeller(void)
{
}


CCardColumn& CPlayFortuneTeller::GetColumn(COLUMN_NAME name)
{
	if(static_cast<int>(name) < 4)
		return m_MainColumns[static_cast<int>(name)];
	else if (static_cast<int>(name) < 8)
		return m_MainColumns[static_cast<int>(name) -4];
	else if (name == COLUMN_NAME::NAME_HIDDEN_COLUMN)
		return m_aHiddenColumn;
	else
		return m_aBoardColumn;
}
bool CPlayFortuneTeller::ShuffleAndInit()
{
	int i;

	for (auto column : m_MainColumns)
	{
		column.CleanCard();
	}
	for (auto column : m_aSolvedColumn)
	{
		column.CleanCard();
	}
	m_aHiddenColumn.CleanCard();
	m_aBoardColumn.CleanCard();

	m_nMatchCount = 0;
	m_pSetOfDeck->Shuffle();

	for (i = 0; i < 20; ++i)
		m_MainColumns[i % 4].PushCards(m_pSetOfDeck->GetCardAtIndex(i).get());

	for (i = 20; i < 48; ++i)
		m_aHiddenColumn.PushCards(m_pSetOfDeck->GetCardAtIndex(i).get());

	return true;
}
bool CPlayFortuneTeller::PushSolveColumn(CFlowerCard	*SolveCard)
{
	switch (m_nCount % 8)
	{
	case	0:
	case	1:
		m_aSolvedColumn[0].PushCards(SolveCard);
		break;
	case	2:
	case	3:
		m_aSolvedColumn[1].PushCards(SolveCard);
		break;
	case	4:
	case	5:
		m_aSolvedColumn[2].PushCards(SolveCard);
		break;
	case	6:
	case	7:
		m_aSolvedColumn[3].PushCards(SolveCard);
		break;
	}

	m_nCount++;

	return true;
}
bool CPlayFortuneTeller::SetMouseRegion()
{
	bool	bRet = true;
	for (int i = 0; i < 4; ++i)
		m_MainColumns[i].SetLastRect(START_X_FORTUNE + i * INTERVAL_COLUMNTOCOLUMN_FORTUNE,
			INTERVAL_YTOY_FORTUNE*m_MainColumns[i].GetSize(),
			CARD_CX,
			CARD_CY);

	if (m_aHiddenColumn.GetSize() > 0)
		m_aHiddenColumn.SetLastRect(HIDDEN_STARTX_FORTUNE, HIDDEN_STARTY_FORTUNE, CARD_CX, CARD_CY);

	if (m_aBoardColumn.GetSize() == 1)
		m_aBoardColumn.SetLastRect(BOARD_STARTX_FORTUNE, BOARD_STARTY_FORTUNE, CARD_CX, CARD_CY);

	if (m_aBoardColumn.GetSize() > 1)
	{
		m_aBoardColumn.SetFirstRect(BOARD_STARTX_FORTUNE, BOARD_STARTY_FORTUNE, BOARD_INTERVAL_FORTUNE, CARD_CY);
		m_aBoardColumn.SetLastRect(BOARD_STARTX_FORTUNE + BOARD_INTERVAL_FORTUNE * (m_aBoardColumn.GetSize() - 1),
			BOARD_STARTY_FORTUNE, CARD_CX, CARD_CY);

		if (m_bAnyCardSelected &&
			m_aBoardColumn.GetSize() >= 3 &&
			(m_pSelectedCard == m_aBoardColumn.ShowLastCard())
			)
		{
			m_aBoardColumn.SetLastBeforeRect(
				BOARD_STARTX_FORTUNE + BOARD_INTERVAL_FORTUNE * (m_aBoardColumn.GetSize() - 2),
				BOARD_STARTY_FORTUNE,
				BOARD_INTERVAL_FORTUNE,
				CARD_CY);
		}
	}
	return bRet;
}

void CPlayFortuneTeller::DrawAll(CDC* pDC)
{
	int i, j;
	CDC MemDC;
	CBitmap*	pOldBitmap;
	CBitmap*	pBitmap = NULL;
	MemDC.CreateCompatibleDC(pDC);
	pOldBitmap = (CBitmap*)MemDC.SelectObject(pBitmap);
	///////////////////////////////////////////////////////////////
	//draw main column....
	for (j = 0; j < 4; ++j)	//main column....
	{
		for (i = 0; i < GetColumn((COLUMN_NAME)j).GetSize(); i++)
		{

			if (i == GetColumn((COLUMN_NAME)j).GetSize() - 1)
				pBitmap = GetColumn((COLUMN_NAME)j).GetBitmapOfCard(i).get();
			else
				pBitmap = GetColumn((COLUMN_NAME)j).GetHiddenBitmap().get();
			MemDC.SelectObject(pBitmap);
			//////////////////////////////
			pDC->BitBlt(START_X_FORTUNE + j * INTERVAL_COLUMNTOCOLUMN_FORTUNE,
				START_Y_FORTUNE + i * INTERVAL_YTOY_FORTUNE,
				CARD_CX,
				CARD_CY,
				&MemDC, 0, 0, SRCCOPY);
			//////////////////////////////////////////////////////////

		}
	}
	///////////////////////////////////////////////////////////////////
	//	Draw	Hidden Set.
	if (GetColumn(COLUMN_NAME::NAME_HIDDEN_COLUMN).GetSize())
	{
		pBitmap = GetColumn(COLUMN_NAME::NAME_HIDDEN_COLUMN).GetHiddenBitmap().get();
		MemDC.SelectObject(pBitmap);
		/////////////////////////////////////

		pDC->BitBlt(HIDDEN_STARTX_FORTUNE, HIDDEN_STARTY_FORTUNE, CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);

	}
	///////////////////////////////////////////////////////////////////
	//	Draw	Board Set.
	for (i = 0; i < GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize(); i++)
	{
		pBitmap = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetBitmapOfCard(i).get();
		MemDC.SelectObject(pBitmap);

		pDC->BitBlt(BOARD_STARTX_FORTUNE + BOARD_INTERVAL_FORTUNE * i,
			BOARD_STARTY_FORTUNE,
			CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);

	}
	///////////////////////////////////////////////////////////////
	if (m_bAnyCardSelected)
	{
		pBitmap = GetColumn(COLUMN_NAME::NAME_HIDDEN_COLUMN).GetSelectedBitmap().get();
		MemDC.SelectObject(pBitmap);
		if (static_cast<int>(m_nSelectedColumn) < 4)
		{
			pDC->BitBlt(START_X_FORTUNE + INTERVAL_COLUMNTOCOLUMN_FORTUNE * (int)m_nSelectedColumn,
				(GetColumn((COLUMN_NAME)m_nSelectedColumn).GetSize()) *INTERVAL_YTOY_FORTUNE,
				CARD_CX, CARD_CY,
				&MemDC, 0, 0, SRCAND);
		}
		else if (static_cast<int>(m_nSelectedColumn) == 4)
		{
			if (GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize() == 1)
			{

				pDC->BitBlt(BOARD_STARTX_FORTUNE,
					BOARD_STARTY_FORTUNE,
					CARD_CX, CARD_CY,
					&MemDC, 0, 0, SRCAND);

			}
			else
			{
				pDC->BitBlt(BOARD_STARTX_FORTUNE,
					BOARD_STARTY_FORTUNE,
					BOARD_INTERVAL_FORTUNE, CARD_CY,
					&MemDC, 0, 0, SRCAND);
			}
		}
		else if (static_cast<int>(m_nSelectedColumn) == 5)
		{
			pDC->BitBlt(BOARD_STARTX_FORTUNE + BOARD_INTERVAL_FORTUNE *
				(GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize() - 1),
				BOARD_STARTY_FORTUNE,
				CARD_CX, CARD_CY,
				&MemDC, 0, 0, SRCAND);
		}

	}
	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
}

int CPlayFortuneTeller::CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2)
{
	int		nRedraw = 0;
	bool	bSelected = false;
	bool	bFinish = false;

	rt1.top = 0;
	rt2.bottom = 0;

	for (int i = 0; i < 6; ++i)	//0~3 main column, 4 first card of board 5 last card of board
	{
		if ((i < 4 && GetColumn((COLUMN_NAME)i).GetLastRect().PtInRect(pt))
			|| (i == 4 && GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetFirstRect().PtInRect(pt))
			|| (i == 5 && GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetLastRect().PtInRect(pt)))
		{
			if (!m_bAnyCardSelected)
			{
				if (i < 4)
				{
					bSelected = FindNewSelectedCard((SELECTED_COLUMN)i, GetColumn((COLUMN_NAME)i).ShowLastCard());
					rt1.top = GetColumn((COLUMN_NAME)i).GetSize() * INTERVAL_YTOY_FORTUNE;
					rt1.left = START_X_FORTUNE + i * INTERVAL_COLUMNTOCOLUMN_FORTUNE;
					rt1.bottom = rt1.top + CARD_CY;
					rt1.right = rt1.left + CARD_CX;
				}
				else if (i == 4)
				{
					bSelected = FindNewSelectedCard((SELECTED_COLUMN)i, GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).ShowFirstCard());
					rt1.top = BOARD_STARTY_FORTUNE;
					rt1.left = BOARD_STARTX_FORTUNE;
					rt1.bottom = rt1.top + CARD_CY;
					rt1.right = rt1.left + CARD_CX;
				}
				else if (i == 5)
				{
					bSelected = FindNewSelectedCard((SELECTED_COLUMN)i, GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).ShowLastCard());
					rt1.top = BOARD_STARTY_FORTUNE;
					rt1.left = BOARD_STARTX_FORTUNE + (GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize() - 1)*BOARD_INTERVAL_FORTUNE;
					rt1.bottom = rt1.top + CARD_CY;
					rt1.right = rt1.left + CARD_CX;
				}

				nRedraw = 1;

			}
			else
			{
				SELECTED_COLUMN nNewSelectedColumnNumber = (SELECTED_COLUMN)i;
				if (nNewSelectedColumnNumber != m_nSelectedColumn)
				{
					//compare with it ...
					int nOldSelectedNumber = m_pSelectedCard->GetNumber();
					int nNewSelectedNumber = 0;
					if (i < 4 && GetColumn((COLUMN_NAME)i).ShowLastCard())
						nNewSelectedNumber = GetColumn((COLUMN_NAME)i).ShowLastCard()->GetNumber();
					else if (i == 4 && GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).ShowFirstCard())
						nNewSelectedNumber = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).ShowFirstCard()->GetNumber();
					else if (i == 5 && GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).ShowLastCard())
						nNewSelectedNumber = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).ShowLastCard()->GetNumber();

					if (nOldSelectedNumber == nNewSelectedNumber)
					{
						////////
						CString	s;
						s.Format(_T("%d - %d Good Job!!!\n"),
							nOldSelectedNumber,
							nNewSelectedNumber);
						TRACE(s);
						////////
						CFlowerCard* pTemp;
						//pop & push new 
						if (i < 4)
						{
							rt1.top = START_Y_FORTUNE;
							rt1.left = START_X_FORTUNE + i * INTERVAL_COLUMNTOCOLUMN_FORTUNE;
							rt1.bottom = START_Y_FORTUNE + 5 * INTERVAL_YTOY_FORTUNE + CARD_CY;
							rt1.right = rt1.left + CARD_CX;
							pTemp = GetColumn((COLUMN_NAME)i).PopLastCard();
						}
						else if (i == 4)
						{
							rt1.top = BOARD_STARTY_FORTUNE;
							rt1.left = BOARD_STARTX_FORTUNE;
							rt1.bottom = rt1.top + CARD_CY;
							rt1.right = BOARD_STARTX_FORTUNE + (GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize() + 1)*BOARD_INTERVAL_FORTUNE + CARD_CY;

							pTemp = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).PopFirstCard();
						}
						else if (i == 5)
						{
							rt1.top = BOARD_STARTY_FORTUNE;
							rt1.left = BOARD_STARTX_FORTUNE;
							rt1.bottom = rt1.top + CARD_CY;
							rt1.right = BOARD_STARTX_FORTUNE + (GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize() + 1)*BOARD_INTERVAL_FORTUNE + CARD_CY;

							pTemp = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).PopLastCard();
						}

						PushSolveColumn(pTemp);
						//pop & push old

						if (static_cast<int>(m_nSelectedColumn) < 4)
						{
							rt2.top = START_Y_FORTUNE;
							rt2.bottom = START_Y_FORTUNE + 5 * INTERVAL_YTOY_FORTUNE + CARD_CY;
							rt2.left = START_X_FORTUNE + static_cast<int>(m_nSelectedColumn) * INTERVAL_COLUMNTOCOLUMN_FORTUNE;
							rt2.right = rt2.left + CARD_CX;

							pTemp = GetColumn((COLUMN_NAME)m_nSelectedColumn).PopLastCard();//PopMainColumn(nOldSelectedColumnNumber);
						}
						else if (static_cast<int>(m_nSelectedColumn) == 4)
						{
							rt2.top = BOARD_STARTY_FORTUNE;
							rt2.left = BOARD_STARTX_FORTUNE;
							rt2.bottom = rt2.top + CARD_CY;
							rt2.right = BOARD_STARTX_FORTUNE + (GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize())*BOARD_INTERVAL_FORTUNE + CARD_CY;

							pTemp = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).PopFirstCard();
						}
						else if (static_cast<int>(m_nSelectedColumn) == 5)
						{
							rt2.top = BOARD_STARTY_FORTUNE;
							rt2.left = BOARD_STARTX_FORTUNE;
							rt2.bottom = rt2.top + CARD_CY;
							rt2.right = BOARD_STARTX_FORTUNE + (GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize())*BOARD_INTERVAL_FORTUNE + CARD_CY;

							pTemp = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).PopLastCard();
						}
						PushSolveColumn(pTemp);

						nRedraw = 2;
						m_nMatchCount++;
						if (m_nMatchCount == 24)
						{
							m_nMatchCount = 0;;
							bFinish = true;
						}
						m_bAnyCardSelected = false;
					}
					else
					{
						CString	s;
						s.Format(_T("%d - %d Not pare!!!"),
							nOldSelectedNumber,
							nNewSelectedNumber);
						TRACE(s);
						nRedraw = 1;
					}
				}
				else
				{
					nRedraw = 1;
				}
			}
		}
	}
	// board card last & before last....	
	if (m_bAnyCardSelected &&
		GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetLastBeforeRect().PtInRect(pt) &&
		m_nSelectedColumn == SELECTED_COLUMN::BOARD_COLUMN_RIGHT &&
		GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize() > 2
		)
	{
		int nOldSelectedNumber = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).ShowLastCard()->GetNumber();
		int nNewSelectedNumber = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).ShowLastBeforeCard()->GetNumber();
		if (nOldSelectedNumber == nNewSelectedNumber)
		{
			////////
			CString	s;
			s.Format(_T("%d - %d Good Job!!!\n"),
				nOldSelectedNumber,
				nNewSelectedNumber);
			TRACE(s);

			rt1.top = BOARD_STARTY_FORTUNE;
			rt1.left = HIDDEN_STARTX_FORTUNE;
			rt1.bottom = rt1.top + CARD_CY;
			rt1.right = BOARD_STARTX_FORTUNE + (GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize())*BOARD_INTERVAL_FORTUNE + CARD_CX;


			////////
			CFlowerCard* pTemp;
			//pop & push new 
			pTemp = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).PopLastCard();
			PushSolveColumn(pTemp);
			//pop & push old
			pTemp = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).PopLastCard();
			PushSolveColumn(pTemp);

			m_bAnyCardSelected = false;
			nRedraw = 1;
			m_nMatchCount++;
			if (m_nMatchCount == 24)
			{
				m_nMatchCount = 0;
				bFinish = true;
			}
		}
	}

	///////////////////
	if (m_bAnyCardSelected)
	{
		nRedraw = 1;

		//		SELECTED_COLUMN SelectedColumn	=	GetSelectedColumn();
		if ( static_cast<int>(m_nSelectedColumn) < 4)
		{
			rt1.top = START_Y_FORTUNE + (GetColumn((COLUMN_NAME)m_nSelectedColumn).GetSize() - 1) * INTERVAL_YTOY_FORTUNE;
			rt1.left = START_X_FORTUNE + (int)m_nSelectedColumn * INTERVAL_COLUMNTOCOLUMN_FORTUNE;
			rt1.bottom = rt1.top + CARD_CY;
			rt1.right = rt1.left + CARD_CX;
		}
		else if (static_cast<int>(m_nSelectedColumn) == 4)
		{
			rt1.top = BOARD_STARTY_FORTUNE;
			rt1.left = BOARD_STARTX_FORTUNE;
			rt1.bottom = rt1.top + CARD_CY;
			rt1.right = rt1.left + CARD_CX;
		}
		else if (static_cast<int>(m_nSelectedColumn) == 5)
		{
			rt1.top = BOARD_STARTY_FORTUNE;
			rt1.left = BOARD_STARTX_FORTUNE + (GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize() - 1)* BOARD_INTERVAL_FORTUNE;
			rt1.bottom = rt1.top + CARD_CY;
			rt1.right = rt1.left + CARD_CX;
		}
		m_bAnyCardSelected = bSelected;
		//		SetHavingSelectedCard(bSelected);
	}
	if (GetColumn(COLUMN_NAME::NAME_HIDDEN_COLUMN).GetLastRect().PtInRect(pt))
	{
		CFlowerCard* pTemp;
		pTemp = GetColumn(COLUMN_NAME::NAME_HIDDEN_COLUMN).PopLastCard();//PopHiddenColumn();
		if (pTemp)
			GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).PushCards(pTemp);//PushBoardColumn(pTemp);
		rt1.top = BOARD_STARTY_FORTUNE;
		rt1.left = HIDDEN_STARTX_FORTUNE;
		rt1.bottom = rt1.top + CARD_CY;
		rt1.right = BOARD_STARTX_FORTUNE + (GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize() + 1)*BOARD_INTERVAL_FORTUNE + CARD_CY;

		nRedraw = 1;
	}
	if (nRedraw == 1 || nRedraw == 2)
		SetMouseRegion();
	if (bFinish)
	{
		nRedraw = 3;

		CResultDlg Dlg;
		auto ResultVector = GetResult();
		Dlg.SetLuckCount(ResultVector.size());
		Dlg.SetLuckNumber(ResultVector);
		Dlg.DoModal();

	}
	return nRedraw;
}
std::vector<int> CPlayFortuneTeller::GetResult()
{
	std::vector<int> resultVector;
	for (int i = 4; i < 8; ++i)
	{
		auto partVector = GetColumn((COLUMN_NAME)i).CheckFortuneResult();
		resultVector.insert(resultVector.end(), partVector.begin(), partVector.end());
	}
	return resultVector;

}
bool CPlayFortuneTeller::FindNewSelectedCard(SELECTED_COLUMN nColumn, CFlowerCard *pCard)
{
	if (pCard == nullptr)
		return false;
	m_bAnyCardSelected = true;
	m_nSelectedColumn = nColumn;
	m_pSelectedCard = pCard;
	return true;
}

bool CPlayFortuneTeller::CheckDbClick(CPoint pt)
{
	bool bRedraw = false;
	CRect	rtBoardColumn;
	memcpy(&rtBoardColumn, GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetFirstRect(), sizeof(CRect));
	rtBoardColumn.right = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetLastRect().right;
	int nCount = GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).GetSize();
	if (nCount > 2 &&
		GetColumn(COLUMN_NAME::NAME_HIDDEN_COLUMN).GetSize() == 0 &&
		rtBoardColumn.PtInRect(pt))
	{
		for (int i = 0; i < nCount; ++i)
		{
			GetColumn(COLUMN_NAME::NAME_HIDDEN_COLUMN).PushCards(GetColumn(COLUMN_NAME::NAME_BOARD_COLUMN).PopLastCard());
		}
		bRedraw = true;
	}
	if (bRedraw)
		SetMouseRegion();
	return bRedraw;
}
