#pragma once
#include <memory>
using namespace std;
class CFlowerCard
{
private:
	int	m_nID;				//	0~47
	int	m_nNumber;			//	1~12
	int	m_nPosition;		//	1~4
	unique_ptr<CBitmap> m_pBitmap{ new CBitmap };
	const bool	SetPositionAndNumber();
public:
	const unique_ptr<CBitmap>& GetHiddenBitmap();
	const unique_ptr<CBitmap>& GetBitmap();
	bool SetID(const int nNumber);
	int GetID() { return m_nID; }
	int	GetNumber() { return m_nNumber; }
	int	GetPosition() { return m_nPosition; }

	CFlowerCard(int nID = -1);
	CFlowerCard(const CFlowerCard & CopyCard);
	CFlowerCard& operator=(const CFlowerCard & AssignCard);
	CFlowerCard(CFlowerCard && CopyCard) = delete;
	CFlowerCard& operator=(CFlowerCard && AssignCard) = delete;
	virtual ~CFlowerCard();
};