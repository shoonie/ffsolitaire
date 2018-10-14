#include <list>
#include <vector>
#include "FlowerCard.h"

class CCardColumn
{
	CRect m_rtBoundaryRect;
	CRect m_rtLastRect;
	CRect m_rtLastBeforeRect;
	CRect m_rtFirstRect;

	list<shared_ptr<CFlowerCard>> m_CardList;

	int	m_nCurrentNumberOfCards;
	bool m_bHasHidden;
	unique_ptr<CBitmap> m_pBitmapForSelected{ new CBitmap };

public:
	CCardColumn(void);
	~CCardColumn(void);
	CCardColumn(const CCardColumn &);
	CCardColumn& operator=(const CCardColumn & AssignDeck);

	CCardColumn(CCardColumn &&) = delete;
	CCardColumn& operator=(CCardColumn && ) = delete;

	bool HasHidden() { return m_bHasHidden; }
	void SetHiddenOrShow(const bool bShow) { m_bHasHidden = bShow; }

	const unique_ptr<CBitmap>& GetSelectedBitmap();
	const unique_ptr<CBitmap>& GetBitmapOfCard(int nIndex);
	const unique_ptr<CBitmap>& GetHiddenBitmap();

	int	GetSize() { return m_nCurrentNumberOfCards; }

	const CRect& GetBoundaryRect() { return m_rtBoundaryRect; }
	const CRect& GetLastRect() { return m_rtLastRect; }
	const CRect& GetLastBeforeRect() { return m_rtLastBeforeRect; }
	const CRect& GetFirstRect() { return m_rtFirstRect; }

	bool SetBoundaryRect(int x, int y, int cx, int cy);
	bool SetLastRect(int x, int y, int cx, int cy);
	bool SetLastBeforeRect(int x, int y, int cx, int cy);
	bool SetFirstRect(int x, int y, int cx, int cy);

	shared_ptr<CFlowerCard> PopLastCard();
	shared_ptr<CFlowerCard> ShowLastBeforeCard();
	shared_ptr<CFlowerCard> ShowFirstCard();
	shared_ptr<CFlowerCard> ShowSecondCard();
	shared_ptr<CFlowerCard> ShowThirdCard();
	shared_ptr<CFlowerCard> PopFirstCard();
	decltype(auto) ShowLastCard()
	{
		return m_CardList.back();
	}

	bool CleanCard();
	bool PushCards(shared_ptr<CFlowerCard> pCard);

	vector<int> CheckFortuneResult();
};
