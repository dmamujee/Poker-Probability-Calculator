#ifndef GAME_H
#define GAME_H
#include "card.h"
#include <iostream>
using namespace std;

#endif

class Game{

	//Array of all the cards in the deck;
	Card* deckOfCards[4][13];
	Card* hand1[2];
	Card* hand2[2];

	//Array holding the 5 communal cards "on the board"
	Card* communalCards[5];

public:

	Game();
	~Game();
	
	void clearGame();
	void updateCommunal(Card *newCommunalCards[5]);
	void updateSingleCommunal(Card* newCard, int location);
	void printCommunal();
	bool isFlush(Card *allCards[7]);
	bool isQuads(Card *allCards[7]);
	bool isStraight(Card *allCards[7]);
	bool isTriple(Card *allCards[7]);
	bool isOnePair(Card *allCards[7]);
	bool isStraightFlush(Card *allCards[7]);
	bool isTwoPair(Card *allCards[7]);
	bool isFullHouse(Card *allCards[7]);
	bool isHighCard(Card *allCards[7]);
	string rankToString(int rank);
	Card* getCard(int value, int suit);
	Card* getCard(int value);

	// If all communal Cards have come out, then determines the ranking of the hand
	int handRanking(Hand* hand);

	int handComparison(Hand* hand1, Hand* hand2);




};
ostream& operator<<(ostream& os, const Card& card);
