#pragma once
#include "FlowerCard.h"
#include <Vector>
//A set of cards //48 cards This is singleton class.

class CDeck		
{
public:
	enum { NumberOfCardsInADeck = 48 };
	static CDeck* Instance();
	vector<shared_ptr<CFlowerCard>> Cards;
	shared_ptr<CFlowerCard> GetCardAtIndex(const int nIndex)const;
	const unique_ptr<CBitmap>& GetBitmapOfCard(const int nIndex)const;

private:
	static CDeck* _instance;
	CDeck();

public:
	virtual ~CDeck();
	CDeck(const CDeck & CopyDeck) = delete;
	CDeck& operator=(const CDeck & AssignDeck) = delete;
	CDeck(CDeck && moveDeck) = delete;
	CDeck& operator=(CDeck && moveAssignDeck) = delete;
	void Shuffle();
};
