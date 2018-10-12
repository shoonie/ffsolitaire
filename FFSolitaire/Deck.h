#pragma once
#include "FlowerCard.h"
#include <Vector>

class CDeck		//A set of cards //48 cards This is singleton class.
{
public:
	static CDeck* Instance();
	enum { NumberOfCardsInADeck = 48 };
	vector<shared_ptr<CFlowerCard>> Cards;
public:
	shared_ptr<CFlowerCard> GetCardAtIndex(const int nIndex)const;
	const unique_ptr<CBitmap>& GetBitmapOfCard(const int nIndex)const;
private:
	static CDeck* _instance;
	CDeck();
public:
	virtual ~CDeck();
	CDeck(const CDeck & CopyDeck) = delete;
	CDeck& operator=(const CDeck & AssignDeck) = delete;
	CDeck(CDeck && CopyDeck) = delete;
	CDeck& operator=(CDeck && AssignDeck) = delete;

	void Shuffle();
};
