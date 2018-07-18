#include "StdAfx.h"
#include "Deck.h"
#include <algorithm>
using namespace std;

CDeck::CDeck(void)
{
	for(int i=0;i<48;i++)
	{
		CFlowerCard *pCard = new CFlowerCard(i);
		Cards.push_back(pCard);
	}
}

CDeck::~CDeck(void)
{
	for (auto pIte:Cards)
    {
        delete pIte;
    }
	
}
CDeck::CDeck(const CDeck & CopyDeck)
{
	Cards.insert(Cards.begin(),CopyDeck.Cards.begin(),CopyDeck.Cards.end());
}
CDeck& CDeck::operator =(const CDeck & AssignDeck)
{
	if(&AssignDeck	==	this)
		return *this;
	Cards.insert(Cards.begin(),AssignDeck.Cards.begin(),AssignDeck.Cards.end());

	return *this;
}
CFlowerCard* CDeck::GetCardAtIndex(const int nIndex)const
{
	if(nIndex>=0 && nIndex <NumberOfCardsInADeck)
		return Cards[nIndex];
	else
		return NULL;
}

const CBitmap* CDeck::GetBitmapOfCard(const int nIndex) const
{
	if(nIndex>=0 && nIndex <NumberOfCardsInADeck)
		return Cards[nIndex]->GetBitmap();
	else
		return NULL;

}
void CDeck::Shuffle()
{
	srand(time(NULL));
	random_shuffle(Cards.begin(),Cards.end());
}