#include "StdAfx.h"
#include "PlayFortuneTeller.h"
#include "Resultdlg.h"
CPlayFortuneTeller::CPlayFortuneTeller(void)
{
	m_bAnyCardSelected		=	FALSE;
	m_nSelectedColumn		=	NULL_SELECTED;
	m_nCount				=	0;
	m_nMatchCount			=	0;
}

CPlayFortuneTeller::~CPlayFortuneTeller(void)
{
}


CCardColumn& CPlayFortuneTeller::GetColumn(COLUMN_NAME name)
{
	switch (name)
	{
	case NAME_MAIN_COLUMN1:
		return m_aMainColumn[0];
		break;
	case NAME_MAIN_COLUMN2:
		return m_aMainColumn[1];
		break;
	case NAME_MAIN_COLUMN3:
		return m_aMainColumn[2];
		break;
	case NAME_MAIN_COLUMN4:
		return m_aMainColumn[3];
		break;
	case NAME_SOLVED_COLUMN1:
		return m_aSolvedColumn[0];
		break;
	case NAME_SOLVED_COLUMN2:
		return m_aSolvedColumn[1];
		break;
	case NAME_SOLVED_COLUMN3:
		return m_aSolvedColumn[2];
		break;
	case NAME_SOLVED_COLUMN4:
		return m_aSolvedColumn[3];
		break;
	case NAME_HIDDEN_COLUMN:
		return m_aHiddenColumn;
		break;
	case NAME_BOARD_COLUMN:
	default:
		return m_aBoardColumn;
		break;
	}
}
BOOL CPlayFortuneTeller::ShuffleAndInit()
{
	int i;

	for(i=0;i<4;i++)
	{
		m_aMainColumn[i].CleanCard();
		m_aSolvedColumn[i].CleanCard();
	}
	m_aHiddenColumn.CleanCard();
	m_aBoardColumn.CleanCard();

	m_nMatchCount	=	0;
	m_aSetOfDeck.Shuffle();

	

	for(i=0;i<20;i++)
		m_aMainColumn[i%4].PushCards(m_aSetOfDeck.GetCardAtIndex(i));

	for(i=20;i<48;i++)
		m_aHiddenColumn.PushCards(m_aSetOfDeck.GetCardAtIndex(i));

	return TRUE;
}
BOOL CPlayFortuneTeller::PushSolveColumn(CFlowerCard	*SolveCard)
{
	switch(m_nCount % 8)
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

	return TRUE;
}
BOOL CPlayFortuneTeller::SetMouseRegion()
{
	BOOL	bRet	=	TRUE;
	for(int i = 0;i<4;i++)
		m_aMainColumn[i].SetLastRect(START_X_FORTUNE+i*INTERVAL_COLUMNTOCOLUMN_FORTUNE,
							INTERVAL_YTOY_FORTUNE*m_aMainColumn[i].GetSize(),
							CARD_CX,
							CARD_CY);

	if(m_aHiddenColumn.GetSize() > 0)
		m_aHiddenColumn.SetLastRect(HIDDEN_STARTX_FORTUNE  , HIDDEN_STARTY_FORTUNE ,	CARD_CX,	CARD_CY);

	if(m_aBoardColumn.GetSize() == 1)
		m_aBoardColumn.SetLastRect(BOARD_STARTX_FORTUNE  , BOARD_STARTY_FORTUNE ,	CARD_CX,	CARD_CY);

	if(m_aBoardColumn.GetSize() >	1)
	{
		m_aBoardColumn.SetFirstRect(BOARD_STARTX_FORTUNE  , BOARD_STARTY_FORTUNE ,	BOARD_INTERVAL_FORTUNE,	CARD_CY);
		m_aBoardColumn.SetLastRect(BOARD_STARTX_FORTUNE + BOARD_INTERVAL_FORTUNE* ( m_aBoardColumn.GetSize() -1), 
								BOARD_STARTY_FORTUNE ,	CARD_CX,	CARD_CY);

		if(	m_bAnyCardSelected && 
			m_aBoardColumn.GetSize() >=3 &&  
			(m_pSelectedCard	==	m_aBoardColumn.ShowLastCard()) 
			)
		{
			m_aBoardColumn.SetLastBeforeRect(	
					BOARD_STARTX_FORTUNE + BOARD_INTERVAL_FORTUNE* (m_aBoardColumn.GetSize()-2), 
					BOARD_STARTY_FORTUNE ,	
					BOARD_INTERVAL_FORTUNE,	
					CARD_CY);
		}
	}
	return bRet;
}

void CPlayFortuneTeller::DrawAll(CDC* pDC)
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
		for ( i=0;i<GetColumn((COLUMN_NAME)j).GetSize();i++)
		{

			if(i==GetColumn((COLUMN_NAME)j).GetSize()-1)
				pBitmap	=	(CBitmap*) (GetColumn((COLUMN_NAME)j).GetBitmapOfCard(i));
			else
				pBitmap	=	(CBitmap*) (GetColumn((COLUMN_NAME)j).GetHiddenBitmap());
			MemDC.SelectObject(pBitmap);
//////////////////////////////
			pDC->BitBlt(	START_X_FORTUNE + j*INTERVAL_COLUMNTOCOLUMN_FORTUNE , 
							START_Y_FORTUNE + i *INTERVAL_YTOY_FORTUNE ,
							CARD_CX,
							CARD_CY,
							&MemDC,0,0,SRCCOPY);
//////////////////////////////////////////////////////////

		}
	}
///////////////////////////////////////////////////////////////////
//	Draw	Hidden Set.
	if(GetColumn(NAME_HIDDEN_COLUMN).GetSize())
	{
		pBitmap	=	(CBitmap*) (GetColumn(NAME_HIDDEN_COLUMN).GetHiddenBitmap());
		MemDC.SelectObject(pBitmap);
/////////////////////////////////////

		pDC->BitBlt(HIDDEN_STARTX_FORTUNE  , HIDDEN_STARTY_FORTUNE ,CARD_CX,CARD_CY,&MemDC,0,0,SRCCOPY);

	}
///////////////////////////////////////////////////////////////////
//	Draw	Board Set.
	for (i=0;i<GetColumn(NAME_BOARD_COLUMN).GetSize();i++)
	{
		pBitmap	=	(CBitmap*) (GetColumn(NAME_BOARD_COLUMN).GetBitmapOfCard(i));
		MemDC.SelectObject(pBitmap);

		pDC->BitBlt(BOARD_STARTX_FORTUNE +BOARD_INTERVAL_FORTUNE*i , 
					BOARD_STARTY_FORTUNE  ,
					CARD_CX,CARD_CY,&MemDC,0,0,SRCCOPY);

	}
///////////////////////////////////////////////////////////////
	if(m_bAnyCardSelected)
	{
//		SELECTED_COLUMN	n_SelectedColumn = GetSelectedColumn();
		pBitmap	=	(CBitmap*) (GetColumn(NAME_HIDDEN_COLUMN).GetSelectedBitmap());
		MemDC.SelectObject(pBitmap);
		if(m_nSelectedColumn < 4)
		{

			pDC->BitBlt(	START_X_FORTUNE +  INTERVAL_COLUMNTOCOLUMN_FORTUNE * (int)m_nSelectedColumn, 
						(GetColumn((COLUMN_NAME)m_nSelectedColumn).GetSize()) *INTERVAL_YTOY_FORTUNE ,
						CARD_CX,CARD_CY,
						&MemDC,0,0,SRCAND);
		}
		else if(m_nSelectedColumn ==4)
		{
			if(GetColumn(NAME_BOARD_COLUMN).GetSize() == 1)
			{

				pDC->BitBlt(	BOARD_STARTX_FORTUNE, 
					BOARD_STARTY_FORTUNE ,
					CARD_CX,CARD_CY,
					&MemDC,0,0,SRCAND);

			}
			else
			{
				pDC->BitBlt(	BOARD_STARTX_FORTUNE, 
					BOARD_STARTY_FORTUNE ,
					BOARD_INTERVAL_FORTUNE,CARD_CY,
					&MemDC,0,0,SRCAND);
			}
		}
		else if (m_nSelectedColumn ==5)
		{
			pDC->BitBlt(	BOARD_STARTX_FORTUNE+  BOARD_INTERVAL_FORTUNE * 
				(GetColumn(NAME_BOARD_COLUMN).GetSize() -1), 
				BOARD_STARTY_FORTUNE ,
					CARD_CX,CARD_CY,
					&MemDC,0,0,SRCAND);
		}

	}
	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
}

int CPlayFortuneTeller::CheckPoint(const CPoint & pt, CRect& rt1, CRect& rt2)
{
	int		nRedraw		=	0;
	BOOL	bSelected	=	FALSE;
	BOOL	bFinish		=	FALSE;

	rt1.top		=	0;
	rt2.bottom	=	0;

	for(int i=0;i<6;i++)	//0~3 main column, 4 first card of board 5 last card of board
	{
		//if(GetColumn(NAME_BOARD_COLUMN).GetSize() == 1 && i== 5)
		//	break;

		if(	(i < 4 && GetColumn((COLUMN_NAME)i).GetLastRect().PtInRect(pt) ) 
			|| (i==4 &&  GetColumn(NAME_BOARD_COLUMN).GetFirstRect().PtInRect(pt))
			|| (i==5 &&  GetColumn(NAME_BOARD_COLUMN).GetLastRect().PtInRect(pt)))
		{
			if(!m_bAnyCardSelected)
			{
				if(i<4)
				{
					bSelected = FindNewSelectedCard((SELECTED_COLUMN)i,GetColumn((COLUMN_NAME)i).ShowLastCard());
					rt1.top		=	GetColumn((COLUMN_NAME)i).GetSize() * INTERVAL_YTOY_FORTUNE ;
					rt1.left		=	START_X_FORTUNE	+ i * INTERVAL_COLUMNTOCOLUMN_FORTUNE;
					rt1.bottom		=	rt1.top + CARD_CY;
					rt1.right		=	rt1.left + CARD_CX;
				}
				else if(i==4)
				{
					bSelected = FindNewSelectedCard((SELECTED_COLUMN)i,GetColumn(NAME_BOARD_COLUMN).ShowFirstCard());
					rt1.top			=	BOARD_STARTY_FORTUNE;
					rt1.left		=	BOARD_STARTX_FORTUNE;
					rt1.bottom		=	rt1.top + CARD_CY;
					rt1.right		=	rt1.left + CARD_CX;
				}
				else if(i==5)
				{
					bSelected = FindNewSelectedCard((SELECTED_COLUMN)i,GetColumn(NAME_BOARD_COLUMN).ShowLastCard());
					rt1.top			=	BOARD_STARTY_FORTUNE;
					rt1.left		=	BOARD_STARTX_FORTUNE + (GetColumn(NAME_BOARD_COLUMN).GetSize()-1)*BOARD_INTERVAL_FORTUNE;
					rt1.bottom		=	rt1.top + CARD_CY;
					rt1.right		=	rt1.left + CARD_CX;
				}

				nRedraw	=	1;

			}
			else
			{
				SELECTED_COLUMN nNewSelectedColumnNumber	=	(SELECTED_COLUMN)i;	
				if(nNewSelectedColumnNumber != m_nSelectedColumn)
				{
					//compare with it ...
					int nOldSelectedNumber	=	m_pSelectedCard->GetNumber();
					int nNewSelectedNumber	=	0;
					if(i<4 && GetColumn((COLUMN_NAME)i).ShowLastCard())
						nNewSelectedNumber	=	GetColumn((COLUMN_NAME)i).ShowLastCard()->GetNumber();
					else if (i==4 && GetColumn(NAME_BOARD_COLUMN).ShowFirstCard())
						nNewSelectedNumber	=	GetColumn(NAME_BOARD_COLUMN).ShowFirstCard()->GetNumber();
					else if (i==5 && GetColumn(NAME_BOARD_COLUMN).ShowLastCard())
						nNewSelectedNumber	=	GetColumn(NAME_BOARD_COLUMN).ShowLastCard()->GetNumber();

					if(nOldSelectedNumber == nNewSelectedNumber)
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
						if(i<4)
						{
							rt1.top		=	START_Y_FORTUNE;
							rt1.left		=	START_X_FORTUNE	+ i * INTERVAL_COLUMNTOCOLUMN_FORTUNE;
							rt1.bottom		=	START_Y_FORTUNE+ 5 * INTERVAL_YTOY_FORTUNE  + CARD_CY;
							rt1.right		=	rt1.left + CARD_CX;
							pTemp	= GetColumn((COLUMN_NAME)i).PopLastCard();
						}
						else if(i==4)
						{
							rt1.top		=	BOARD_STARTY_FORTUNE;
							rt1.left		=	BOARD_STARTX_FORTUNE;
							rt1.bottom		=	rt1.top + CARD_CY;
							rt1.right		=	BOARD_STARTX_FORTUNE + (GetColumn(NAME_BOARD_COLUMN).GetSize() + 1 )*BOARD_INTERVAL_FORTUNE + CARD_CY;

							pTemp	= GetColumn(NAME_BOARD_COLUMN).PopFirstCard();
						}
						else if(i==5)
						{
							rt1.top		=	BOARD_STARTY_FORTUNE;
							rt1.left		=	BOARD_STARTX_FORTUNE;
							rt1.bottom		=	rt1.top + CARD_CY;
							rt1.right		=	BOARD_STARTX_FORTUNE + (GetColumn(NAME_BOARD_COLUMN).GetSize() + 1 )*BOARD_INTERVAL_FORTUNE + CARD_CY;

							pTemp	= GetColumn(NAME_BOARD_COLUMN).PopLastCard();
						}
						
						PushSolveColumn(pTemp);
						//pop & push old

						if(m_nSelectedColumn<4)
						{
							rt2.top		=	START_Y_FORTUNE;
							rt2.bottom		=	START_Y_FORTUNE + 5 * INTERVAL_YTOY_FORTUNE  + CARD_CY;
							rt2.left		=	START_X_FORTUNE	+ m_nSelectedColumn * INTERVAL_COLUMNTOCOLUMN_FORTUNE;
							rt2.right		=	rt2.left + CARD_CX;

							pTemp	= GetColumn((COLUMN_NAME)m_nSelectedColumn).PopLastCard();//PopMainColumn(nOldSelectedColumnNumber);
						}
						else if(m_nSelectedColumn==4)
						{
							rt2.top		=	BOARD_STARTY_FORTUNE;
							rt2.left		=	BOARD_STARTX_FORTUNE;
							rt2.bottom		=	rt2.top + CARD_CY;
							rt2.right		=	BOARD_STARTX_FORTUNE + (GetColumn(NAME_BOARD_COLUMN).GetSize())*BOARD_INTERVAL_FORTUNE+CARD_CY;

							pTemp	= GetColumn(NAME_BOARD_COLUMN).PopFirstCard();
						}
						else if(m_nSelectedColumn==5)
						{
							rt2.top		=	BOARD_STARTY_FORTUNE;
							rt2.left		=	BOARD_STARTX_FORTUNE;
							rt2.bottom		=	rt2.top + CARD_CY;
							rt2.right		=	BOARD_STARTX_FORTUNE+ (GetColumn(NAME_BOARD_COLUMN).GetSize())*BOARD_INTERVAL_FORTUNE+CARD_CY;

							pTemp	= GetColumn(NAME_BOARD_COLUMN).PopLastCard();
						}
						PushSolveColumn(pTemp);

						nRedraw	=	2;
						m_nMatchCount++;
						if(m_nMatchCount == 24)
						{
							m_nMatchCount	=	0;;
							bFinish	=	TRUE;
						}
						m_bAnyCardSelected	=	FALSE;
					}
					else
					{
						CString	s;
						s.Format(_T("%d - %d Not pare!!!"),
							nOldSelectedNumber,
							nNewSelectedNumber);
						TRACE(s);
						nRedraw	=	1;
					}
				}
				else
				{
					nRedraw	=	1;
				}
			}
		}
	}
// board card last & before last....	
	if(	m_bAnyCardSelected && 
		GetColumn(NAME_BOARD_COLUMN).GetLastBeforeRect().PtInRect(pt) &&
		m_nSelectedColumn	==	BOARD_COLUMN_RIGHT &&
		GetColumn(NAME_BOARD_COLUMN).GetSize() > 2
		)
	{
		int nOldSelectedNumber	=	GetColumn(NAME_BOARD_COLUMN).ShowLastCard()->GetNumber();
		int nNewSelectedNumber	=	GetColumn(NAME_BOARD_COLUMN).ShowLastBeforeCard()->GetNumber();
		if(nOldSelectedNumber == nNewSelectedNumber)
		{
				////////
			CString	s;
			s.Format(_T("%d - %d Good Job!!!\n"),
				nOldSelectedNumber,
				nNewSelectedNumber);
			TRACE(s);
			
			rt1.top		=	BOARD_STARTY_FORTUNE;
			rt1.left		=	HIDDEN_STARTX_FORTUNE;
			rt1.bottom		=	rt1.top + CARD_CY;
			rt1.right		=	BOARD_STARTX_FORTUNE + (GetColumn(NAME_BOARD_COLUMN).GetSize())*BOARD_INTERVAL_FORTUNE + CARD_CX;
	
			
			////////
			CFlowerCard* pTemp;
			//pop & push new 
			pTemp	= GetColumn(NAME_BOARD_COLUMN).PopLastCard();
			PushSolveColumn(pTemp);
			//pop & push old
			pTemp	= GetColumn(NAME_BOARD_COLUMN).PopLastCard();
			PushSolveColumn(pTemp);

			m_bAnyCardSelected	=	FALSE;
			nRedraw	=	1;
			m_nMatchCount++;
			if(m_nMatchCount == 24)
			{
				m_nMatchCount	=	0;
				bFinish	=	TRUE;
			}
		}
	}

///////////////////
	if(m_bAnyCardSelected)
	{
		nRedraw = 1;
		
//		SELECTED_COLUMN SelectedColumn	=	GetSelectedColumn();
		if(m_nSelectedColumn < 4)
		{
			rt1.top		=	START_Y_FORTUNE + (GetColumn((COLUMN_NAME)m_nSelectedColumn).GetSize() -1) * INTERVAL_YTOY_FORTUNE;
			rt1.left		=	START_X_FORTUNE	+ (int)m_nSelectedColumn * INTERVAL_COLUMNTOCOLUMN_FORTUNE;
			rt1.bottom		=	rt1.top + CARD_CY;
			rt1.right		=	rt1.left + CARD_CX;
		}
		else if(m_nSelectedColumn == 4)
		{
			rt1.top		=	BOARD_STARTY_FORTUNE;
			rt1.left		=	BOARD_STARTX_FORTUNE;
			rt1.bottom		=	rt1.top + CARD_CY;
			rt1.right		=	rt1.left + CARD_CX;
		}
		else if(m_nSelectedColumn == 5)
		{
			rt1.top		=	BOARD_STARTY_FORTUNE;
			rt1.left		=	BOARD_STARTX_FORTUNE + (GetColumn(NAME_BOARD_COLUMN).GetSize() -1)* BOARD_INTERVAL_FORTUNE;
			rt1.bottom		=	rt1.top + CARD_CY;
			rt1.right		=	rt1.left + CARD_CX;
		}
		m_bAnyCardSelected	=	bSelected;
//		SetHavingSelectedCard(bSelected);
	}
	if(	GetColumn(NAME_HIDDEN_COLUMN).GetLastRect().PtInRect(pt) ) 
	{
		CFlowerCard* pTemp;
		pTemp	=	GetColumn(NAME_HIDDEN_COLUMN).PopLastCard();//PopHiddenColumn();
		if(pTemp)
			GetColumn(NAME_BOARD_COLUMN).PushCards(pTemp);//PushBoardColumn(pTemp);
			rt1.top		=	BOARD_STARTY_FORTUNE;
			rt1.left	=	HIDDEN_STARTX_FORTUNE;
			rt1.bottom	=	rt1.top + CARD_CY;
			rt1.right	=	BOARD_STARTX_FORTUNE + (GetColumn(NAME_BOARD_COLUMN).GetSize() + 1 )*BOARD_INTERVAL_FORTUNE + CARD_CY;

		nRedraw	=	1;
	}
	if(nRedraw == 1 || nRedraw ==2 )
		SetMouseRegion();
	if(bFinish)
	{
		nRedraw =3;

		int	nResultCards[12]	=	{0,};
		int nResultNumber;

		CResultDlg Dlg;
		nResultNumber	=	GetResult(nResultCards);
		Dlg.SetLuckCount(nResultNumber);
		Dlg.SetLuckNumber(nResultCards);
		Dlg.DoModal();

	}
	return nRedraw;
}
int CPlayFortuneTeller::GetResult(int pResult[])	// find solve column same card....using STL ....
{
	int nResultCount=0;
	int i,j=0;
	int SolveNo[3]	=	{0,};
	int SolveCount	=	0;
	
	for(i=4;i<8;i++)
	{
		SolveCount		=	GetColumn((COLUMN_NAME)i).CheckFortuneResult(SolveNo);

		for(j=0;j<SolveCount;j++)
			pResult[nResultCount+j]	=	SolveNo[j];
		nResultCount	+= SolveCount;

	}
	return nResultCount;

}
BOOL CPlayFortuneTeller::FindNewSelectedCard(SELECTED_COLUMN nColumn, CFlowerCard *pCard)
{
	if(pCard	==	NULL)
		return FALSE;
	m_bAnyCardSelected	=	TRUE;
	m_nSelectedColumn	=	nColumn;
	m_pSelectedCard		=	pCard;
	return TRUE;
}

BOOL CPlayFortuneTeller::CheckDbClick(CPoint pt)
{
	BOOL bRedraw	=	FALSE;
	CRect	rtBoardColumn;
	memcpy(&rtBoardColumn,	GetColumn(NAME_BOARD_COLUMN).GetFirstRect(),sizeof(CRect));
	rtBoardColumn.right	=	GetColumn(NAME_BOARD_COLUMN).GetLastRect().right;
	int nCount	=GetColumn(NAME_BOARD_COLUMN).GetSize();	
	if( nCount> 2 && 
			GetColumn(NAME_HIDDEN_COLUMN).GetSize() == 0 &&
			rtBoardColumn.PtInRect(pt) )
	{
		for(int i=0;i<nCount;i++)
		{
			GetColumn(NAME_HIDDEN_COLUMN).PushCards(GetColumn(NAME_BOARD_COLUMN).PopLastCard());
		}
		bRedraw	=	TRUE;
	}	
	if(bRedraw)
		SetMouseRegion();
	return bRedraw;
}
