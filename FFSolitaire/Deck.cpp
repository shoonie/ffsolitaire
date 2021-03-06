#include "StdAfx.h"
#include "Deck.h"
#include <algorithm>
using namespace std;

CDeck* CDeck::_instance = nullptr;

CDeck* CDeck::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new CDeck();
		return _instance;
	}
	else
		return  _instance;
}

CDeck::CDeck(void)
{
	for (int i = 0; i < NumberOfCardsInADeck; ++i)
	{
		shared_ptr<CFlowerCard> tmp(new CFlowerCard(i));
		Cards.push_back(tmp);
	}
}

CDeck::~CDeck(void)
{
	delete _instance;
}

shared_ptr<CFlowerCard> CDeck::GetCardAtIndex(const int nIndex)const
{
	return Cards[nIndex];
}

const unique_ptr<CBitmap>& CDeck::GetBitmapOfCard(const int nIndex) const
{
	return Cards[nIndex]->GetBitmap();
}

void CDeck::Shuffle()
{
	srand(unsigned int(time(0)));
	random_shuffle(Cards.begin(), Cards.end());
}