#pragma once

class CFlowerCard
{
private:
	int		m_nID;				//	0~47
	int		m_nNumber;			//	1~12
	int		m_nPosition;		//	1~4
	CBitmap	* m_pBitmap;
	void	DeleteBitmap();
	const bool	SetPositionAndNumber();

public:
	const	CBitmap* GetHiddenBitmap();
	const	CBitmap* GetBitmap();

	bool	SetID(const int nNumber);

	int		GetID(){return m_nID;}
	int		GetNumber(){return m_nNumber;}
	int		GetPosition(){return m_nPosition;}
	
	CFlowerCard(int nID = -1);
	CFlowerCard(const CFlowerCard & CopyCard);
	CFlowerCard& operator=(const CFlowerCard & AssignCard);
	virtual ~CFlowerCard();
};