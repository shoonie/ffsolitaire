#pragma once
#include "FlowerCard.h"
#include <Vector>
using namespace std;

class CDeck		//A set of cards //48 cards...
{
	enum { NumberOfCardsInADeck = 48 };
	vector<CFlowerCard*> Cards;
public:
	CFlowerCard* GetCardAtIndex(const int nIndex)const;
	const CBitmap* GetBitmapOfCard(const int nIndex)const;

	CDeck();
	virtual ~CDeck();
	CDeck(const CDeck & CopyDeck);
	CDeck& operator=(const CDeck & AssignDeck);

	void Shuffle();
};
