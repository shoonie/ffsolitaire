#include "StdAfx.h"
#include "Play8By6.h"

CPlay8By6::CPlay8By6(void)
{
	m_bAnyCardSelected	=	FALSE;
	m_nSelectedColumn	=	0;
	m_pSelectedCard		=	NULL;
	m_nCount			=	0;
}

CPlay8By6::~CPlay8By6(void)
{
}
BOOL	CPlay8By6::ShuffleAndInit()
{
	
	int i;
	for(i=0;i<12;i++)
	{
		m_aMainColumn[i].CleanCard();
	}

	m_aSetOfDeck.Shuffle();

	for(i=0;i<48;i++)
		m_aMainColumn[i%8].PushCards(m_aSetOfDeck.GetCardAtIndex(i));

	m_bAnyCardSelected	=	FALSE;
	return TRUE;
}

BOOL CPlay8By6::SetMouseRegion()
{
	BOOL	bRet	=	TRUE;
	int i;

//set main column rect
	// m_aMainColumn[i].GetSize() == 0 일 때 고려....
	for( i = 0;i<4;i++)
	{
		if(m_aMainColumn[i].GetSize() == 0)
		{
			m_aMainColumn[i].SetLastRect(START_X_1_8BY6,
							START_Y_1_8BY6 + INTERVAL_YTOY_8BY6*i,
							CARD_CX,
							CARD_CY);
		}
		else
		{
			m_aMainColumn[i].SetLastRect(START_X_1_8BY6- (m_aMainColumn[i].GetSize()-1)*INTERVAL_XTOX_8BY6,
							START_Y_1_8BY6 + INTERVAL_YTOY_8BY6*i,
							CARD_CX,
							CARD_CY);
		}
	}
	for( i = 4;i<8;i++)
	{
		if(m_aMainColumn[i].GetSize() == 0)
		{
			m_aMainColumn[i].SetLastRect(START_X_2_8BY6,
							START_Y_2_8BY6 + INTERVAL_YTOY_8BY6*(i-4),
							CARD_CX,
							CARD_CY);
		}
		else
		{
			m_aMainColumn[i].SetLastRect(START_X_2_8BY6 +(m_aMainColumn[i].GetSize()-1)*INTERVAL_XTOX_8BY6,
							START_Y_2_8BY6 + INTERVAL_YTOY_8BY6*(i-4),
							CARD_CX,
							CARD_CY);
		}
	}
	for( i = 8;i<12;i++)
		m_aMainColumn[i].SetLastRect(START_SOLVE_X_8BY6,
							START_SOLVE_Y_8BY6 + INTERVAL_YTOY_8BY6*(i-8),
							CARD_CX,
							CARD_CY);
	return bRet;
}

int CPlay8By6::CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2)
{
	int		nRedraw		=	0;
	int		i;
	BOOL	bFoundSomething	=	FALSE;
	if(!m_bAnyCardSelected)  //first select...
	{
		for(i=0;i<8;i++)
		{
			if(m_aMainColumn[i].GetLastRect().PtInRect(pt) && m_aMainColumn[i].GetSize() > 0)
			{
				m_bAnyCardSelected	=	TRUE;
				m_pSelectedCard		=	m_aMainColumn[i].ShowLastCard();
				m_nSelectedColumn	=	i;
				SetMouseRegion();
				rt1	=	m_aMainColumn[i].GetLastRect();
				nRedraw	=	1;
				break;
			}
		}
	}
	else	//has selected card.
	{
		for( i=0;i<12;i++)
		{
			if(m_aMainColumn[i].GetLastRect().PtInRect(pt) )
			{
				bFoundSomething	=	TRUE;
				if(i == m_nSelectedColumn)	//reselecte one column, unselect...
				{
					rt1	=	m_aMainColumn[i].GetFirstRect();
					nRedraw	=	1;
					break;
				}
				else if( i < 8)
				{		/////////think over and over,,,,very important part////
					int	nSelectedColumn		=	m_nSelectedColumn;
					CFlowerCard * pPrevCard	=	m_pSelectedCard;
					int nSizeCurColumn		=	m_aMainColumn[i].GetSize();
					if(nSizeCurColumn > 0)
					{
						CFlowerCard * pCurCard	=	m_aMainColumn[i].ShowLastCard();
						if(pPrevCard->GetNumber()+1 == pCurCard->GetNumber())
						{
							m_aMainColumn[i].PushCards(m_aMainColumn[nSelectedColumn].PopLastCard());
							if(nSelectedColumn < 4)
							{
								rt1.top		=	START_Y_1_8BY6 + nSelectedColumn * INTERVAL_YTOY_8BY6;
								rt1.bottom	=	rt1.top + CARD_CY;
								rt1.left	=	START_X_1_8BY6 - m_aMainColumn[nSelectedColumn].GetSize() * INTERVAL_XTOX_8BY6;
								rt1.right	=	START_X_1_8BY6 + CARD_CX;
							}
							else
							{
								rt1.top		=	START_Y_2_8BY6 + (nSelectedColumn-4) * INTERVAL_YTOY_8BY6;
								rt1.bottom	=	rt1.top + CARD_CY;
								rt1.left		=	START_X_2_8BY6 ;
								rt1.right		=	START_X_2_8BY6 + m_aMainColumn[nSelectedColumn].GetSize() * INTERVAL_XTOX_8BY6 + CARD_CX;
							}
							if(i < 4)
							{
								rt2.top		=	START_Y_1_8BY6 + i * INTERVAL_YTOY_8BY6;
								rt2.bottom	=	rt2.top + CARD_CY;
								rt2.left		=	START_X_1_8BY6 - (m_aMainColumn[i].GetSize() +1) * INTERVAL_XTOX_8BY6;
								rt2.right	=	START_X_1_8BY6 + CARD_CX;
							}
							else
							{
								rt2.top		=	START_Y_2_8BY6 + (i-4) * INTERVAL_YTOY_8BY6;
								rt2.bottom	=	rt2.top + CARD_CY;
								rt2.left		=	START_X_2_8BY6 ;
								rt2.right	=	START_X_2_8BY6 + (m_aMainColumn[i].GetSize() + 1) * INTERVAL_XTOX_8BY6 + CARD_CX;
							}
						//	Move
							nRedraw = 2;
							break;
						}
						else
						{
							//Nothing To do here///
							nRedraw = 1;
							rt1	=	m_aMainColumn[nSelectedColumn].GetLastRect();
							//memcpy(rtInvalidateRect	,&(	m_aMainColumn[nSelectedColumn].GetMainRect()) ,sizeof(CRect));
						}
					}
					else
					{
						// Move to New Column
						m_aMainColumn[i].PushCards(m_aMainColumn[nSelectedColumn].PopLastCard());
						if(nSelectedColumn < 4)
						{
							rt1.top		=	START_Y_1_8BY6 + nSelectedColumn * INTERVAL_YTOY_8BY6;
							rt1.bottom	=	rt1.top + CARD_CY;
							rt1.left		=	START_X_1_8BY6 - m_aMainColumn[nSelectedColumn].GetSize() * INTERVAL_XTOX_8BY6;
							rt1.right		=	START_X_1_8BY6 + CARD_CX;
						}
						else
						{
							rt1.top		=	START_Y_2_8BY6 + (nSelectedColumn-4) * INTERVAL_YTOY_8BY6;
							rt1.bottom	=	rt1.top + CARD_CY;
							rt1.left		=	START_X_2_8BY6 ;
							rt1.right		=	START_X_2_8BY6 + m_aMainColumn[nSelectedColumn].GetSize() * INTERVAL_XTOX_8BY6 + CARD_CX;
						}
						if(i < 4)
						{
							rt2.top		=	START_Y_1_8BY6 + i * INTERVAL_YTOY_8BY6;
							rt2.bottom	=	rt2.top + CARD_CY;
							rt2.left		=	START_X_1_8BY6 - (m_aMainColumn[i].GetSize() +1) * INTERVAL_XTOX_8BY6;
							rt2.right	=	START_X_1_8BY6 + CARD_CX;
						}
						else
						{
							rt2.top		=	START_Y_2_8BY6 + (i-4) * INTERVAL_YTOY_8BY6;
							rt2.bottom	=	rt2.top + CARD_CY;
							rt2.left		=	START_X_2_8BY6 ;
							rt2.right	=	START_X_2_8BY6 + (m_aMainColumn[i].GetSize() + 1) * INTERVAL_XTOX_8BY6 + CARD_CX;
						}
						nRedraw = 2;
						break;

					}
				}
				else //8 <= i < 12
				{
					int nColumnSize			=	m_aMainColumn[i].GetSize();
					int	nSelectedColumn		=	m_nSelectedColumn;
					int nCurNumber = 0;
					if(nColumnSize == 0 )
						nCurNumber = 0;
					else
						nCurNumber	=	m_aMainColumn[i].ShowLastCard()->GetNumber();
					if(nCurNumber + 1 == m_pSelectedCard->GetNumber() )
					{// check position....
						int nCurPosition = (i%4)+1 ;
						if( nCurPosition ==  m_pSelectedCard->GetPosition() ||
							((nCurPosition + m_pSelectedCard->GetPosition()==7) && m_pSelectedCard->GetNumber() != 12))
						{
							m_aMainColumn[i].PushCards(m_aMainColumn[nSelectedColumn].PopLastCard());
							if(nSelectedColumn < 4)
							{
								rt1.top		=	START_Y_1_8BY6 + nSelectedColumn * INTERVAL_YTOY_8BY6;
								rt1.bottom	=	rt1.top + CARD_CY;
								rt1.left		=	START_X_1_8BY6 - m_aMainColumn[nSelectedColumn].GetSize() * INTERVAL_XTOX_8BY6;
								rt1.right		=	START_X_1_8BY6 + CARD_CX;
							}
							else
							{
								rt1.top		=	START_Y_2_8BY6 + (nSelectedColumn-4) * INTERVAL_YTOY_8BY6;
								rt1.bottom	=	rt1.top + CARD_CY;
								rt1.left		=	START_X_2_8BY6 ;
								rt1.right		=	START_X_2_8BY6 + m_aMainColumn[nSelectedColumn].GetSize() * INTERVAL_XTOX_8BY6 + CARD_CX;
							}

							rt2.top		=	START_Y_1_8BY6 + (i - 8) * INTERVAL_YTOY_8BY6;
							rt2.bottom	=	rt2.top + CARD_CY;
							rt2.left		=	START_SOLVE_X_8BY6 ;
							rt2.right	=	START_SOLVE_X_8BY6 + CARD_CX;
							nRedraw	=	2;
							break;
						}
						else
						{
							bFoundSomething = FALSE;
							break;
						}

					}
					else
					{
						bFoundSomething = FALSE;
						break;
					}
					
				}
			} //if
		} //for
		m_bAnyCardSelected	=	FALSE;
		if(!bFoundSomething)
		{
			int	nSelectedColumn		=	m_nSelectedColumn;
			rt1	=	m_aMainColumn[nSelectedColumn].GetLastRect();
			nRedraw = 1;
		}
	} //else - has seleced card...
	//check Finish...
	int nFinish = 0;
	for(i=8;i<12;i++)
	{
		if(m_aMainColumn[i].GetSize() == 12)
		{
			nFinish ++;
		}
	}
	if(nFinish == 4)
	{
		AfxMessageBox(_T(" You Win the Game!!!"));
		nRedraw = 3;
	}
	SetMouseRegion();
	return nRedraw;
}
void CPlay8By6::DrawAll(CDC *pDC)
{
	int i,j;
	CDC MemDC;

	CBitmap*	pOldBitmap;
	CBitmap*	pBitmap	=	NULL;	
	MemDC.CreateCompatibleDC(pDC);

	pOldBitmap	=	(CBitmap*)MemDC.SelectObject(pBitmap);
///////////////////////////////////////////////////////////////
//draw main column....
	for( j=0;j<4;j++)	//main column....
	{
		if(m_aMainColumn[j].GetSize() == 0)
		{
			pBitmap	=	(CBitmap*)m_aMainColumn[j].GetSelectedBitmap();
			MemDC.SelectObject(pBitmap);
			pDC->BitBlt( START_X_1_8BY6 ,START_Y_1_8BY6 + j* INTERVAL_YTOY_8BY6 ,CARD_CX,CARD_CY,&MemDC,0,0,SRCCOPY);
		}
		else
		{
			for ( i=0;i<m_aMainColumn[j].GetSize();i++)
			{
				pBitmap	=	(CBitmap*)m_aMainColumn[j].GetBitmapOfCard(i);
				MemDC.SelectObject(pBitmap);
				pDC->BitBlt( START_X_1_8BY6 - i*INTERVAL_XTOX_8BY6 ,START_Y_1_8BY6 + INTERVAL_YTOY_8BY6 *j,CARD_CX,CARD_CY,&MemDC,0,0,SRCCOPY);
			}
		}
	}

	for( j=4;j<8;j++)	//main column....
	{
		if(m_aMainColumn[j].GetSize() == 0)
		{
			pBitmap	=	(CBitmap*)m_aMainColumn[j].GetSelectedBitmap();
			MemDC.SelectObject(pBitmap);
			pDC->BitBlt( START_X_2_8BY6 ,START_Y_2_8BY6+ (j-4)* INTERVAL_YTOY_8BY6,CARD_CX,CARD_CY,&MemDC,0,0,SRCCOPY);
		}
		else
		{
			for ( i=0;i<m_aMainColumn[j].GetSize();i++)
			{
				pBitmap	=	(CBitmap*)m_aMainColumn[j].GetBitmapOfCard(i);
				MemDC.SelectObject(pBitmap);
				pDC->BitBlt( START_X_2_8BY6 + i*INTERVAL_XTOX_8BY6 ,START_Y_2_8BY6 + INTERVAL_YTOY_8BY6 *(j-4),CARD_CX,CARD_CY,&MemDC,0,0,SRCCOPY);
			}
		}
	}
	for( j=8;j<12;j++)	//main column....
	{
		if(m_aMainColumn[j].GetSize() == 0)
		{
			pBitmap	=	(CBitmap*)m_aMainColumn[j].GetSelectedBitmap();
			MemDC.SelectObject(pBitmap);
			pDC->BitBlt( START_SOLVE_X_8BY6 ,START_Y_2_8BY6 + (j-8) * INTERVAL_YTOY_8BY6,CARD_CX,CARD_CY,&MemDC,0,0,SRCCOPY);
		}
		else
		{
			for ( i=0;i<m_aMainColumn[j].GetSize();i++)
			{
				pBitmap	=	(CBitmap*)m_aMainColumn[j].GetBitmapOfCard(i);

				MemDC.SelectObject(pBitmap);
				pDC->BitBlt( START_SOLVE_X_8BY6,START_Y_2_8BY6 + (j-8) * INTERVAL_YTOY_8BY6 ,CARD_CX,CARD_CY,&MemDC,0,0,SRCCOPY);
			}
		}
	}
	if(m_bAnyCardSelected)
	{
		int	nSelectedColumn = m_nSelectedColumn;
		pBitmap	=	(CBitmap*)m_aMainColumn[nSelectedColumn].GetSelectedBitmap();
		MemDC.SelectObject(pBitmap);
		if(nSelectedColumn < 4)
		{

			pDC->BitBlt(	START_X_1_8BY6 -  INTERVAL_XTOX_8BY6 * (m_aMainColumn[nSelectedColumn].GetSize() -1) , 
							START_Y_1_8BY6 + nSelectedColumn*INTERVAL_YTOY_8BY6 ,
							CARD_CX,CARD_CY,
							&MemDC,0,0,SRCAND);
		}
		else 
		{
			pDC->BitBlt(	START_X_2_8BY6 +  INTERVAL_XTOX_8BY6 * (m_aMainColumn[nSelectedColumn].GetSize() -1), 
							START_Y_2_8BY6 + (nSelectedColumn -4) *INTERVAL_YTOY_8BY6 ,
							CARD_CX,CARD_CY,
							&MemDC,0,0,SRCAND);
		}
	}

	MemDC.SelectObject(pOldBitmap);
	
	MemDC.DeleteDC();
}