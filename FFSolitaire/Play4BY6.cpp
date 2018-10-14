#include "StdAfx.h"
#include "Play4BY6.h"

CPlay4BY6::CPlay4BY6(CDeck* aDeck) :CPlayer(aDeck), m_bAnyCardSelected(false)
{
	m_MainColumns.resize(12);
}

CPlay4BY6::~CPlay4BY6(void)
{
}
bool CPlay4BY6::ShuffleAndInit()
{
	int i;
	for (auto column : m_MainColumns)
	{
		column.CleanCard();
	}
	m_HiddenColumn.CleanCard();
	m_pSetOfDeck->Shuffle();

	for (i = 0; i < 24; ++i)
		m_MainColumns[i % 12].PushCards(m_pSetOfDeck->GetCardAtIndex(i).get());

	for (i = 24; i < 48; ++i)
		m_HiddenColumn.PushCards(m_pSetOfDeck->GetCardAtIndex(i).get());
	return true;
}

bool CPlay4BY6::SetMouseRegion()
{
	bool	bRet = true;
	int i;

	//set main column rect
	for (i = 0; i < 6; ++i)
		m_MainColumns[i].SetLastRect(START_X_1_4BY12 + i * INTERVAL_COLUMNTOCOLUMN_4BY12,
			START_Y_1_4BY12 + INTERVAL_YTOY_4BY12 * (m_MainColumns[i].GetSize() - 1),
			CARD_CX,
			CARD_CY);
	for (i = 6; i < 12; ++i)
		m_MainColumns[i].SetLastRect(START_X_2_4BY12 + (i - 6)*INTERVAL_COLUMNTOCOLUMN_4BY12,
			START_Y_2_4BY12 + INTERVAL_YTOY_4BY12 * (m_MainColumns[i].GetSize() - 1),
			CARD_CX,
			CARD_CY);
	m_HiddenColumn.SetLastRect(HIDDEN_STARTX_4BY12, HIDDEN_STARTY_4BY12, CARD_CX, CARD_CY);
	return bRet;
}

bool	CPlay4BY6::CheckDbClick(CPoint pt)
{
	if (m_HiddenColumn.GetSize() > 1 && m_HiddenColumn.GetLastRect().PtInRect(pt))
	{
		for (int i = 0; i < 12; ++i)
		{
			m_MainColumns[i % 12].PushCards(m_HiddenColumn.PopLastCard());
		}
		m_bAnyCardSelected = false;
		return true;
	}
	else
	{
		m_bAnyCardSelected = false;
		return true;
	}
}

void	CPlay4BY6::DrawAll(CDC* pDC)
{

	int i, j;
	CDC MemDC;

	CBitmap*	pOldBitmap;
	CBitmap*	pBitmap = NULL;
	MemDC.CreateCompatibleDC(pDC);

	pOldBitmap = (CBitmap*)MemDC.SelectObject(pBitmap);
	///////////////////////////////////////////////////////////////
	//draw main column....
	for (j = 0; j < 6; ++j)	//main column....
	{
		if (m_MainColumns[j].GetSize() == 0)
		{
			pBitmap = m_MainColumns[j].GetSelectedBitmap().get();
			MemDC.SelectObject(pBitmap);
			pDC->BitBlt(START_X_1_4BY12 + j * INTERVAL_COLUMNTOCOLUMN_4BY12, START_Y_1_4BY12,
				CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);
		}
		else
		{
			for (i = 0; i < m_MainColumns[j].GetSize(); i++)
			{
				if (i == 0 && m_MainColumns[j].HasHidden())
				{
					pBitmap = m_MainColumns[j].GetHiddenBitmap().get();
				}
				else
					pBitmap = m_MainColumns[j].GetBitmapOfCard(i).get();

				MemDC.SelectObject(pBitmap);
				pDC->BitBlt(START_X_1_4BY12 + j * INTERVAL_COLUMNTOCOLUMN_4BY12, START_Y_1_4BY12 + INTERVAL_YTOY_4BY12 * i,
					CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);
			}
		}
	}
	for (j = 6; j < 12; ++j)	//main column....
	{
		if (m_MainColumns[j].GetSize() == 0)
		{
			pBitmap = m_MainColumns[j].GetSelectedBitmap().get();
			MemDC.SelectObject(pBitmap);
			pDC->BitBlt(START_X_2_4BY12 + (j - 6)*INTERVAL_COLUMNTOCOLUMN_4BY12, START_Y_2_4BY12,
				CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);
		}
		else
		{
			for (i = 0; i < m_MainColumns[j].GetSize(); i++)
			{
				if (i == 0 && m_MainColumns[j].HasHidden())
				{
					pBitmap = m_MainColumns[j].GetHiddenBitmap().get();
				}
				else
					pBitmap = m_MainColumns[j].GetBitmapOfCard(i).get();

				MemDC.SelectObject(pBitmap);
				pDC->BitBlt(START_X_2_4BY12 + (j - 6)*INTERVAL_COLUMNTOCOLUMN_4BY12, START_Y_2_4BY12 + INTERVAL_YTOY_4BY12 * i,
					CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);
			}
		}
	}
	///////////////////////////////////////////////////////////////////
	//	Draw	Hidden Set.
	if (m_HiddenColumn.GetSize())
	{
		pBitmap = m_HiddenColumn.GetHiddenBitmap().get();
		MemDC.SelectObject(pBitmap);
		pDC->BitBlt(HIDDEN_STARTX_4BY12, HIDDEN_STARTY_4BY12, CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);

	}
	//////////////////////////////////////////////////////////
	if (m_bAnyCardSelected)
	{
		//		int	nSelectedColumn = m_nSelectedColumn;
		pBitmap = m_MainColumns[m_nSelectedColumn].GetSelectedBitmap().get();
		MemDC.SelectObject(pBitmap);
		if (m_nSelectedColumn < 6)
		{

			pDC->BitBlt(START_X_1_4BY12 + INTERVAL_COLUMNTOCOLUMN_4BY12 * m_nSelectedColumn,
				START_Y_1_4BY12 + (m_MainColumns[m_nSelectedColumn].GetSize() - 1)*INTERVAL_YTOY_4BY12,
				CARD_CX, CARD_CY,
				&MemDC, 0, 0, SRCAND);
		}
		else
		{
			pDC->BitBlt(START_X_2_4BY12 + INTERVAL_COLUMNTOCOLUMN_4BY12 * (m_nSelectedColumn - 6),
				START_Y_2_4BY12 + (m_MainColumns[m_nSelectedColumn].GetSize() - 1) *INTERVAL_YTOY_4BY12,
				CARD_CX, CARD_CY,
				&MemDC, 0, 0, SRCAND);
		}
	}

	MemDC.SelectObject(pOldBitmap);

	MemDC.DeleteDC();
}
int CPlay4BY6::CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2)
{
	int		nRedraw = 0;
	int		i, j;
	bool	bFoundSomething = false;
	if (!m_bAnyCardSelected)
	{
		for (i = 0; i < 12; ++i)
		{
			if (m_MainColumns[i].GetLastRect().PtInRect(pt) && m_MainColumns[i].GetSize() > 0)
			{
				m_bAnyCardSelected = true;
				m_pSelectedCard = m_MainColumns[i].ShowLastCard();
				m_nSelectedColumn = i;
				SetMouseRegion();
				{
					rt1 = m_MainColumns[i].GetLastRect();
				}
				nRedraw = 1;
				break;
			}
		}
	}
	else	//has selected card.
	{
		for (i = 0; i < 12; ++i)
		{
			if (m_MainColumns[i].GetLastRect().PtInRect(pt))
			{
				bFoundSomething = true;
				if (i == m_nSelectedColumn)	//reselecte one column, unselect...
				{
					m_bAnyCardSelected = false;
					nRedraw = 1;
					break;
				}
				else
				{
					bFoundSomething = true;
					int nSizeCurColumn = m_MainColumns[i].GetSize();
					CFlowerCard * pCurCard;
					int nCurNumber = 0;
					int nCurPosition = 0;
					if (nSizeCurColumn)
					{
						pCurCard = m_MainColumns[i].ShowLastCard();
						nCurNumber = pCurCard->GetNumber();
						nCurPosition = pCurCard->GetPosition();
					}
					else
					{
						pCurCard = NULL;
						nCurNumber = 0;
						nCurPosition = 0;
					}

					if (nSizeCurColumn > 0 && m_pSelectedCard->GetNumber() != nCurNumber)
					{
						m_bAnyCardSelected = false;
						nRedraw = 1;
						break;
					}

					CFlowerCard * pTempCard[4];
					int		nDepthInColumn = 0;

					//check prev card top....
					{
						int		nColumnSize = m_MainColumns[m_nSelectedColumn].GetSize();
						bool	bHasHidden = m_MainColumns[m_nSelectedColumn].HasHidden();
						int		nPositionCur, nPositionLast;
						for (j = 0; j < nColumnSize; ++j)
						{
							if (bHasHidden && j == nColumnSize - 1)
								break;
							pTempCard[nDepthInColumn] = m_MainColumns[m_nSelectedColumn].PopLastCard();
							if (m_MainColumns[m_nSelectedColumn].GetSize())
							{
								if (m_MainColumns[m_nSelectedColumn].GetSize() == 1 && bHasHidden)
									break;
								if (pTempCard[nDepthInColumn]->GetNumber() == m_MainColumns[m_nSelectedColumn].ShowLastCard()->GetNumber())
								{
									nPositionCur = pTempCard[nDepthInColumn]->GetPosition();
									nPositionLast = m_MainColumns[m_nSelectedColumn].ShowLastCard()->GetPosition();
									if ((nPositionCur == nPositionLast + 1) ||
										(nPositionCur + nPositionLast == 7 && pTempCard[nDepthInColumn]->GetNumber() != 12) ||
										(nPositionCur == 4 && nPositionLast == 2 && pTempCard[nDepthInColumn]->GetNumber() != 12))
									{
										nDepthInColumn++;
										continue;
									}
									else
										break;
								}
								else
									break;
							}
							else
								break;
						}

					}


					if (nCurPosition + 1 == pTempCard[nDepthInColumn]->GetPosition())
					{
						for (j = nDepthInColumn; j >= 0; --j)
							m_MainColumns[i].PushCards(pTempCard[j]);//m_PlayingCard01.GetColumn(m_PlayingCard01.GetSelectedColumn())->PopCard());
						SetMouseRegion();
						if (m_MainColumns[m_nSelectedColumn].GetSize() == 1)
						{
							m_MainColumns[m_nSelectedColumn].SetHiddenOrShow(false);
						}
						m_bAnyCardSelected = false;
						if (m_nSelectedColumn < 6)
						{
							rt1.top = START_Y_1_4BY12;
							rt1.bottom = START_Y_1_4BY12 + (m_MainColumns[m_nSelectedColumn].GetSize() + 4) * INTERVAL_YTOY_4BY12 + CARD_CY;
							rt1.left = START_X_1_4BY12 + m_nSelectedColumn * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt1.right = rt1.left + CARD_CX;
						}
						else
						{
							rt1.top = START_Y_2_4BY12;
							rt1.bottom = START_Y_2_4BY12 + (m_MainColumns[m_nSelectedColumn].GetSize() + 4) * INTERVAL_YTOY_4BY12 + CARD_CY;
							rt1.left = START_X_2_4BY12 + (m_nSelectedColumn - 6) * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt1.right = rt1.left + CARD_CX;
						}
						if (i < 6)
						{
							rt2.top = START_Y_1_4BY12;
							rt2.bottom = START_Y_1_4BY12 + (m_MainColumns[i].GetSize() + 1)* INTERVAL_YTOY_4BY12 + CARD_CY;
							rt2.left = START_X_1_4BY12 + i * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt2.right = rt2.left + CARD_CX;
						}
						else
						{
							rt2.top = START_Y_2_4BY12;
							rt2.bottom = START_Y_2_4BY12 + (m_MainColumns[i].GetSize() + 1) * INTERVAL_YTOY_4BY12 + CARD_CY;
							rt2.left = START_X_2_4BY12 + (i - 6) * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt2.right = rt2.left + CARD_CX;
						}


						nRedraw = 2;
					}
					else if (nCurPosition + pTempCard[nDepthInColumn]->GetPosition() == 7 && m_pSelectedCard->GetNumber() != 12)
					{
						for (j = nDepthInColumn; j >= 0; --j)
							m_MainColumns[i].PushCards(pTempCard[j]);//m_PlayingCard01.GetColumn(m_PlayingCard01.GetSelectedColumn())->PopCard());
						SetMouseRegion();
						if (m_MainColumns[m_nSelectedColumn].GetSize() == 1)
						{
							m_MainColumns[m_nSelectedColumn].SetHiddenOrShow(false);
						}
						m_bAnyCardSelected = false;
						if (m_nSelectedColumn < 6)
						{
							rt1.top = START_Y_1_4BY12;
							rt1.bottom = START_Y_1_4BY12 + (m_MainColumns[m_nSelectedColumn].GetSize() + 4) * INTERVAL_YTOY_4BY12 + CARD_CY;
							rt1.left = START_X_1_4BY12 + m_nSelectedColumn * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt1.right = rt1.left + CARD_CX;
						}
						else
						{
							rt1.top = START_Y_2_4BY12;
							rt1.bottom = START_Y_2_4BY12 + (m_MainColumns[m_nSelectedColumn].GetSize() + 4) * INTERVAL_YTOY_4BY12 + CARD_CY;
							rt1.left = START_X_2_4BY12 + (m_nSelectedColumn - 6) * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt1.right = rt1.left + CARD_CX;
						}
						if (i < 6)
						{
							rt2.top = START_Y_1_4BY12;
							rt2.bottom = START_Y_1_4BY12 + (m_MainColumns[i].GetSize() + 1)* INTERVAL_YTOY_4BY12 + CARD_CY;
							rt2.left = START_X_1_4BY12 + i * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt2.right = rt2.left + CARD_CX;
						}
						else
						{
							rt2.top = START_Y_2_4BY12;
							rt2.bottom = START_Y_2_4BY12 + (m_MainColumns[i].GetSize() + 1) * INTERVAL_YTOY_4BY12 + CARD_CY;
							rt2.left = START_X_2_4BY12 + (i - 6) * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt2.right = rt2.left + CARD_CX;
						}


						nRedraw = 2;
					}
					else if (nCurPosition == 2 && pTempCard[nDepthInColumn]->GetPosition() == 4 && m_pSelectedCard->GetNumber() != 12)
					{
						for (j = nDepthInColumn; j >= 0; --j)
							m_MainColumns[i].PushCards(pTempCard[j]);//m_PlayingCard01.GetColumn(m_PlayingCard01.GetSelectedColumn())->PopCard());
						SetMouseRegion();
						if (m_MainColumns[m_nSelectedColumn].GetSize() == 1)
						{
							m_MainColumns[m_nSelectedColumn].SetHiddenOrShow(false);
						}
						m_bAnyCardSelected = false;
						if (m_nSelectedColumn < 6)
						{
							rt1.top = START_Y_1_4BY12;
							rt1.bottom = START_Y_1_4BY12 + (m_MainColumns[m_nSelectedColumn].GetSize() + 4) * INTERVAL_YTOY_4BY12 + CARD_CY;
							rt1.left = START_X_1_4BY12 + m_nSelectedColumn * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt1.right = rt1.left + CARD_CX;
						}
						else
						{
							rt1.top = START_Y_2_4BY12;
							rt1.bottom = START_Y_2_4BY12 + (m_MainColumns[m_nSelectedColumn].GetSize() + 4) * INTERVAL_YTOY_4BY12 + CARD_CY;
							rt1.left = START_X_2_4BY12 + (m_nSelectedColumn - 6) * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt1.right = rt1.left + CARD_CX;
						}
						if (i < 6)
						{
							rt2.top = START_Y_1_4BY12;
							rt2.bottom = START_Y_1_4BY12 + (m_MainColumns[i].GetSize() + 1)* INTERVAL_YTOY_4BY12 + CARD_CY;
							rt2.left = START_X_1_4BY12 + i * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt2.right = rt2.left + CARD_CX;
						}
						else
						{
							rt2.top = START_Y_2_4BY12;
							rt2.bottom = START_Y_2_4BY12 + (m_MainColumns[i].GetSize() + 1) * INTERVAL_YTOY_4BY12 + CARD_CY;
							rt2.left = START_X_2_4BY12 + (i - 6) * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt2.right = rt2.left + CARD_CX;
						}


						nRedraw = 2;
					}
					else if (pTempCard[nDepthInColumn]->GetPosition() == 1 && m_MainColumns[i].GetSize() == 0)
					{
						for (j = nDepthInColumn; j >= 0; --j)
							m_MainColumns[i].PushCards(pTempCard[j]);//m_PlayingCard01.GetColumn(m_PlayingCard01.GetSelectedColumn())->PopCard());
						SetMouseRegion();
						if (m_MainColumns[m_nSelectedColumn].GetSize() == 1)
						{
							m_MainColumns[m_nSelectedColumn].SetHiddenOrShow(false);
						}
						m_bAnyCardSelected = false;
						if (m_nSelectedColumn < 6)
						{
							rt1.top = START_Y_1_4BY12;
							rt1.bottom = START_Y_1_4BY12 + (m_MainColumns[m_nSelectedColumn].GetSize() + 4) * INTERVAL_YTOY_4BY12 + CARD_CY;
							rt1.left = START_X_1_4BY12 + m_nSelectedColumn * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt1.right = rt1.left + CARD_CX;
						}
						else
						{
							rt1.top = START_Y_2_4BY12;
							rt1.bottom = START_Y_2_4BY12 + (m_MainColumns[m_nSelectedColumn].GetSize() + 4) * INTERVAL_YTOY_4BY12 + CARD_CY;
							rt1.left = START_X_2_4BY12 + (m_nSelectedColumn - 6) * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt1.right = rt1.left + CARD_CX;
						}
						if (i < 6)
						{
							rt2.top = START_Y_1_4BY12;
							rt2.bottom = START_Y_1_4BY12 + (m_MainColumns[i].GetSize() + 1)* INTERVAL_YTOY_4BY12 + CARD_CY;
							rt2.left = START_X_1_4BY12 + i * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt2.right = rt2.left + CARD_CX;
						}
						else
						{
							rt2.top = START_Y_2_4BY12;
							rt2.bottom = START_Y_2_4BY12 + (m_MainColumns[i].GetSize() + 1) * INTERVAL_YTOY_4BY12 + CARD_CY;
							rt2.left = START_X_2_4BY12 + (i - 6) * INTERVAL_COLUMNTOCOLUMN_4BY12;
							rt2.right = rt2.left + CARD_CX;
						}


						nRedraw = 2;
					}
					else
					{
						for (j = nDepthInColumn; j >= 0; --j)
							m_MainColumns[m_nSelectedColumn].PushCards(pTempCard[j]);
						rt1 = m_MainColumns[m_nSelectedColumn].GetLastRect();
						m_bAnyCardSelected = false;
						nRedraw = 1;

					}

				}

				break;
			}//if
		}//for
		if (bFoundSomething == false)
		{
			rt1 = m_MainColumns[m_nSelectedColumn].GetLastRect();
			m_bAnyCardSelected = false;
			nRedraw = 1;
		}
	}//if
	//check Finish...
	int	nFinish = 1;
	for (i = 0; i < 12; ++i)
	{
		if (m_MainColumns[i].GetSize() != 4)
		{
			nFinish = 0;
			break;
		}
		if (m_MainColumns[i].HasHidden() == true)
		{
			nFinish = 0;
			break;
		}
	}

	if (nFinish)
	{
		for (i = 0; i < 12; ++i)
		{
			CFlowerCard	* pCard;
			pCard = m_MainColumns[i].ShowFirstCard();
			if (pCard->GetPosition() != 1)
			{
				nFinish = -1;
				break;
			}
			pCard = m_MainColumns[i].ShowSecondCard();
			if (pCard->GetPosition() != 2)
			{
				nFinish = -1;
				break;
			}
			if (pCard->GetNumber() == 12)
			{
				pCard = m_MainColumns[i].ShowThirdCard();
				if (pCard->GetPosition() != 3)
					nFinish = -1;
				break;
			}
		}
	}

	if (nFinish != 0)
	{
		if (nFinish == 1)
			AfxMessageBox(_T(" You Win the Game!!!"));
		else if (nFinish == -1)
			AfxMessageBox(_T(" Game Finish But You canNOT win. It's rare case....!!!"));
		nRedraw = 3;
	}
	SetMouseRegion();
	return nRedraw;
}