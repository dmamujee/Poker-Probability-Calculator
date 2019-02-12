#ifndef CARD_H
#define CARD_H

const int SPADE = 1004;
const int HEART = 1003;
const int DIAMOND = 1002;
const int CLUB = 1001;

// Card values go from 2 to 10


const int STRAIGHT_FLUSH = 101;
const int FOUR_OF_KIND = 102;
const int FULL_HOUSE = 103;
const int FLUSH = 104;
const int STRAIGHT = 105;
const int THREE_OF_A_KIND = 106;
const int TWO_PAIR = 107;
const int ONE_PAIR = 108;
const int HIGH_CARD = 109;
const int INVALID = 110;


class Card {
	int value;
	int suit;

public:
	Card(int value, int suit);
	int getSuit();
	int getValue();
	bool operator==(Card &other);
	bool operator!=(Card &other);


};

class Hand {
	Card* card0;
	Card* card1;

public:
	Hand(Card* card0, Card* card1);
	Hand();
	//Input only can be 0 or 1
	Card* getCard(int i);
	void setCard(int i, Card* card);

};

#endif
