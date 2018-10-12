#include <list>
#include <vector>

using namespace std;

#include "FlowerCard.h"

class CCardColumn
{
	CRect m_rtBoundaryRect;		// Do I still need thsi variable?
	CRect m_rtLastRect;
	CRect m_rtLastBeforeRect;
	CRect m_rtFirstRect;

	list<CFlowerCard*> m_CardList;

	int	m_nCurrentNumberOfCards;
	bool m_bHasHidden;
	unique_ptr<CBitmap> m_pBitmapForSelected{ new CBitmap };

public:
	CCardColumn(void);
	~CCardColumn(void);
	CCardColumn(const CCardColumn &);
	CCardColumn& operator=(const CCardColumn & AssignDeck);

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

	CFlowerCard * PopLastCard();
	CFlowerCard * ShowLastCard();
	CFlowerCard * ShowLastBeforeCard();
	CFlowerCard * ShowFirstCard();
	CFlowerCard * ShowSecondCard();
	CFlowerCard * ShowThirdCard();
	CFlowerCard * PopFirstCard();

	bool CleanCard();
	bool PushCards(CFlowerCard * pCard);

	vector<int> CheckFortuneResult();
};
