#include "card.h"

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

	// If all communal Cards have come out, then determines the ranking of the hand
	int handRanking(Card *card1, Card* card2);






};