#include "StdAfx.h"
#include "Play8By6.h"

CPlay8By6::CPlay8By6(CDeck* aDeck) :CPlayer(aDeck), m_bAnyCardSelected(false), m_nSelectedColumn(0), m_pSelectedCard(nullptr), m_nCount(0)
{
	m_MainColumns.resize(12);
}

CPlay8By6::~CPlay8By6(void)
{
}

bool	CPlay8By6::ShuffleAndInit()
{

	int i;
	for (auto column : m_MainColumns)
	{
		column.CleanCard();
	}

	m_pSetOfDeck->Shuffle();

	for (i = 0; i < 48; ++i)
		m_MainColumns[i % 8].PushCards(m_pSetOfDeck->GetCardAtIndex(i).get());

	m_bAnyCardSelected = false;
	return true;
}

bool CPlay8By6::SetMouseRegion()
{
	bool	bRet = true;
	int i;
	for (i = 0; i < 4; ++i)
	{
		if (m_MainColumns[i].GetSize() == 0)
		{
			m_MainColumns[i].SetLastRect(START_X_1_8BY6,
				START_Y_1_8BY6 + INTERVAL_YTOY_8BY6 * i,
				CARD_CX,
				CARD_CY);
		}
		else
		{
			m_MainColumns[i].SetLastRect(START_X_1_8BY6 - (m_MainColumns[i].GetSize() - 1)*INTERVAL_XTOX_8BY6,
				START_Y_1_8BY6 + INTERVAL_YTOY_8BY6 * i,
				CARD_CX,
				CARD_CY);
		}
	}
	for (i = 4; i < 8; ++i)
	{
		if (m_MainColumns[i].GetSize() == 0)
		{
			m_MainColumns[i].SetLastRect(START_X_2_8BY6,
				START_Y_2_8BY6 + INTERVAL_YTOY_8BY6 * (i - 4),
				CARD_CX,
				CARD_CY);
		}
		else
		{
			m_MainColumns[i].SetLastRect(START_X_2_8BY6 + (m_MainColumns[i].GetSize() - 1)*INTERVAL_XTOX_8BY6,
				START_Y_2_8BY6 + INTERVAL_YTOY_8BY6 * (i - 4),
				CARD_CX,
				CARD_CY);
		}
	}
	for (i = 8; i < 12; ++i)
		m_MainColumns[i].SetLastRect(START_SOLVE_X_8BY6,
			START_SOLVE_Y_8BY6 + INTERVAL_YTOY_8BY6 * (i - 8),
			CARD_CX,
			CARD_CY);
	return bRet;
}

int CPlay8By6::CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2)
{
	int		nRedraw = 0;
	int		i;
	bool	bFoundSomething = false;
	if (!m_bAnyCardSelected)  //first select...
	{
		for (i = 0; i < 8; i++)
		{
			if (m_MainColumns[i].GetLastRect().PtInRect(pt) && m_MainColumns[i].GetSize() > 0)
			{
				m_bAnyCardSelected = true;
				m_pSelectedCard = m_MainColumns[i].ShowLastCard();
				m_nSelectedColumn = i;
				SetMouseRegion();
				rt1 = m_MainColumns[i].GetLastRect();
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
					rt1 = m_MainColumns[i].GetFirstRect();
					nRedraw = 1;
					break;
				}
				else if (i < 8)
				{		/////////think over and over,,,,very important part////
					int	nSelectedColumn = m_nSelectedColumn;
					CFlowerCard * pPrevCard = m_pSelectedCard;
					int nSizeCurColumn = m_MainColumns[i].GetSize();
					if (nSizeCurColumn > 0)
					{
						CFlowerCard * pCurCard = m_MainColumns[i].ShowLastCard();
						if (pPrevCard->GetNumber() + 1 == pCurCard->GetNumber())
						{
							m_MainColumns[i].PushCards(m_MainColumns[nSelectedColumn].PopLastCard());
							if (nSelectedColumn < 4)
							{
								rt1.top = START_Y_1_8BY6 + nSelectedColumn * INTERVAL_YTOY_8BY6;
								rt1.bottom = rt1.top + CARD_CY;
								rt1.left = START_X_1_8BY6 - m_MainColumns[nSelectedColumn].GetSize() * INTERVAL_XTOX_8BY6;
								rt1.right = START_X_1_8BY6 + CARD_CX;
							}
							else
							{
								rt1.top = START_Y_2_8BY6 + (nSelectedColumn - 4) * INTERVAL_YTOY_8BY6;
								rt1.bottom = rt1.top + CARD_CY;
								rt1.left = START_X_2_8BY6;
								rt1.right = START_X_2_8BY6 + m_MainColumns[nSelectedColumn].GetSize() * INTERVAL_XTOX_8BY6 + CARD_CX;
							}
							if (i < 4)
							{
								rt2.top = START_Y_1_8BY6 + i * INTERVAL_YTOY_8BY6;
								rt2.bottom = rt2.top + CARD_CY;
								rt2.left = START_X_1_8BY6 - (m_MainColumns[i].GetSize() + 1) * INTERVAL_XTOX_8BY6;
								rt2.right = START_X_1_8BY6 + CARD_CX;
							}
							else
							{
								rt2.top = START_Y_2_8BY6 + (i - 4) * INTERVAL_YTOY_8BY6;
								rt2.bottom = rt2.top + CARD_CY;
								rt2.left = START_X_2_8BY6;
								rt2.right = START_X_2_8BY6 + (m_MainColumns[i].GetSize() + 1) * INTERVAL_XTOX_8BY6 + CARD_CX;
							}
							//	Move
							nRedraw = 2;
							break;
						}
						else
						{
							//Nothing To do here///
							nRedraw = 1;
							rt1 = m_MainColumns[nSelectedColumn].GetLastRect();
							//memcpy(rtInvalidateRect	,&(	m_MainColumns[nSelectedColumn].GetMainRect()) ,sizeof(CRect));
						}
					}
					else
					{
						// Move to New Column
						m_MainColumns[i].PushCards(m_MainColumns[nSelectedColumn].PopLastCard());
						if (nSelectedColumn < 4)
						{
							rt1.top = START_Y_1_8BY6 + nSelectedColumn * INTERVAL_YTOY_8BY6;
							rt1.bottom = rt1.top + CARD_CY;
							rt1.left = START_X_1_8BY6 - m_MainColumns[nSelectedColumn].GetSize() * INTERVAL_XTOX_8BY6;
							rt1.right = START_X_1_8BY6 + CARD_CX;
						}
						else
						{
							rt1.top = START_Y_2_8BY6 + (nSelectedColumn - 4) * INTERVAL_YTOY_8BY6;
							rt1.bottom = rt1.top + CARD_CY;
							rt1.left = START_X_2_8BY6;
							rt1.right = START_X_2_8BY6 + m_MainColumns[nSelectedColumn].GetSize() * INTERVAL_XTOX_8BY6 + CARD_CX;
						}
						if (i < 4)
						{
							rt2.top = START_Y_1_8BY6 + i * INTERVAL_YTOY_8BY6;
							rt2.bottom = rt2.top + CARD_CY;
							rt2.left = START_X_1_8BY6 - (m_MainColumns[i].GetSize() + 1) * INTERVAL_XTOX_8BY6;
							rt2.right = START_X_1_8BY6 + CARD_CX;
						}
						else
						{
							rt2.top = START_Y_2_8BY6 + (i - 4) * INTERVAL_YTOY_8BY6;
							rt2.bottom = rt2.top + CARD_CY;
							rt2.left = START_X_2_8BY6;
							rt2.right = START_X_2_8BY6 + (m_MainColumns[i].GetSize() + 1) * INTERVAL_XTOX_8BY6 + CARD_CX;
						}
						nRedraw = 2;
						break;

					}
				}
				else //8 <= i < 12
				{
					int nColumnSize = m_MainColumns[i].GetSize();
					int	nSelectedColumn = m_nSelectedColumn;
					int nCurNumber = 0;
					if (nColumnSize == 0)
						nCurNumber = 0;
					else
						nCurNumber = m_MainColumns[i].ShowLastCard()->GetNumber();
					if (nCurNumber + 1 == m_pSelectedCard->GetNumber())
					{// check position....
						int nCurPosition = (i % 4) + 1;
						if (nCurPosition == m_pSelectedCard->GetPosition() ||
							((nCurPosition + m_pSelectedCard->GetPosition() == 7) && m_pSelectedCard->GetNumber() != 12))
						{
							m_MainColumns[i].PushCards(m_MainColumns[nSelectedColumn].PopLastCard());
							if (nSelectedColumn < 4)
							{
								rt1.top = START_Y_1_8BY6 + nSelectedColumn * INTERVAL_YTOY_8BY6;
								rt1.bottom = rt1.top + CARD_CY;
								rt1.left = START_X_1_8BY6 - m_MainColumns[nSelectedColumn].GetSize() * INTERVAL_XTOX_8BY6;
								rt1.right = START_X_1_8BY6 + CARD_CX;
							}
							else
							{
								rt1.top = START_Y_2_8BY6 + (nSelectedColumn - 4) * INTERVAL_YTOY_8BY6;
								rt1.bottom = rt1.top + CARD_CY;
								rt1.left = START_X_2_8BY6;
								rt1.right = START_X_2_8BY6 + m_MainColumns[nSelectedColumn].GetSize() * INTERVAL_XTOX_8BY6 + CARD_CX;
							}

							rt2.top = START_Y_1_8BY6 + (i - 8) * INTERVAL_YTOY_8BY6;
							rt2.bottom = rt2.top + CARD_CY;
							rt2.left = START_SOLVE_X_8BY6;
							rt2.right = START_SOLVE_X_8BY6 + CARD_CX;
							nRedraw = 2;
							break;
						}
						else
						{
							bFoundSomething = false;
							break;
						}

					}
					else
					{
						bFoundSomething = false;
						break;
					}

				}
			} //if
		} //for
		m_bAnyCardSelected = false;
		if (!bFoundSomething)
		{
			int	nSelectedColumn = m_nSelectedColumn;
			rt1 = m_MainColumns[nSelectedColumn].GetLastRect();
			nRedraw = 1;
		}
	} //else - has seleced card...
	//check Finish...
	int nFinish = 0;
	for (i = 8; i < 12; ++i)
	{
		if (m_MainColumns[i].GetSize() == 12)
		{
			nFinish++;
		}
	}
	if (nFinish == 4)
	{
		AfxMessageBox(_T(" You Win the Game!!!"));
		nRedraw = 3;
	}
	SetMouseRegion();
	return nRedraw;
}
void CPlay8By6::DrawAll(CDC *pDC)
{
	int i, j;
	CDC MemDC;

	CBitmap*	pOldBitmap;
	CBitmap*	pBitmap = nullptr;
	MemDC.CreateCompatibleDC(pDC);

	pOldBitmap = (CBitmap*)MemDC.SelectObject(pBitmap);
	///////////////////////////////////////////////////////////////
	//draw main column....
	for (j = 0; j < 4; ++j)	//main column....
	{
		if (m_MainColumns[j].GetSize() == 0)
		{
			pBitmap = m_MainColumns[j].GetSelectedBitmap().get();
			MemDC.SelectObject(pBitmap);
			pDC->BitBlt(START_X_1_8BY6, START_Y_1_8BY6 + j * INTERVAL_YTOY_8BY6, CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);
		}
		else
		{
			for (i = 0; i < m_MainColumns[j].GetSize(); i++)
			{
				pBitmap = m_MainColumns[j].GetBitmapOfCard(i).get();
				MemDC.SelectObject(pBitmap);
				pDC->BitBlt(START_X_1_8BY6 - i * INTERVAL_XTOX_8BY6, START_Y_1_8BY6 + INTERVAL_YTOY_8BY6 * j, CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);
			}
		}
	}

	for (j = 4; j < 8; ++j)	//main column....
	{
		if (m_MainColumns[j].GetSize() == 0)
		{
			pBitmap = m_MainColumns[j].GetSelectedBitmap().get();
			MemDC.SelectObject(pBitmap);
			pDC->BitBlt(START_X_2_8BY6, START_Y_2_8BY6 + (j - 4)* INTERVAL_YTOY_8BY6, CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);
		}
		else
		{
			for (i = 0; i < m_MainColumns[j].GetSize(); i++)
			{
				pBitmap = m_MainColumns[j].GetBitmapOfCard(i).get();
				MemDC.SelectObject(pBitmap);
				pDC->BitBlt(START_X_2_8BY6 + i * INTERVAL_XTOX_8BY6, START_Y_2_8BY6 + INTERVAL_YTOY_8BY6 * (j - 4), CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);
			}
		}
	}
	for (j = 8; j < 12; ++j)	//main column....
	{
		if (m_MainColumns[j].GetSize() == 0)
		{
			pBitmap = m_MainColumns[j].GetSelectedBitmap().get();
			MemDC.SelectObject(pBitmap);
			pDC->BitBlt(START_SOLVE_X_8BY6, START_Y_2_8BY6 + (j - 8) * INTERVAL_YTOY_8BY6, CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);
		}
		else
		{
			for (i = 0; i < m_MainColumns[j].GetSize(); i++)
			{
				pBitmap = m_MainColumns[j].GetBitmapOfCard(i).get();

				MemDC.SelectObject(pBitmap);
				pDC->BitBlt(START_SOLVE_X_8BY6, START_Y_2_8BY6 + (j - 8) * INTERVAL_YTOY_8BY6, CARD_CX, CARD_CY, &MemDC, 0, 0, SRCCOPY);
			}
		}
	}
	if (m_bAnyCardSelected)
	{
		int	nSelectedColumn = m_nSelectedColumn;
		pBitmap = m_MainColumns[nSelectedColumn].GetSelectedBitmap().get();
		MemDC.SelectObject(pBitmap);
		if (nSelectedColumn < 4)
		{

			pDC->BitBlt(START_X_1_8BY6 - INTERVAL_XTOX_8BY6 * (m_MainColumns[nSelectedColumn].GetSize() - 1),
				START_Y_1_8BY6 + nSelectedColumn * INTERVAL_YTOY_8BY6,
				CARD_CX, CARD_CY,
				&MemDC, 0, 0, SRCAND);
		}
		else
		{
			pDC->BitBlt(START_X_2_8BY6 + INTERVAL_XTOX_8BY6 * (m_MainColumns[nSelectedColumn].GetSize() - 1),
				START_Y_2_8BY6 + (nSelectedColumn - 4) *INTERVAL_YTOY_8BY6,
				CARD_CX, CARD_CY,
				&MemDC, 0, 0, SRCAND);
		}
	}

	MemDC.SelectObject(pOldBitmap);

	MemDC.DeleteDC();
}