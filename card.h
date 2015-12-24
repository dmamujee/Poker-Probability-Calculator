#ifndef CARD_H

const int ACE = 14;
const int JACK = 11;
const int Queen = 12;
const int KING = 13;
const int SPADE = 0;
const int HEART = 1;
const int DIAMOND = 2;
const int CLUB = 3;

const int STRAIGHT_FLUSH = 101;
const int FOUR_OF_KIND = 102;
const int FULL_HOUSE = 103;
const int FLUSH = 104;
const int STRAIGHT = 105;
const int THREE_OF_A_KIND = 106;
const int TWO_PAIR = 107;
const int PAIR = 108;
const int HIGH_CARD = 109;

class Card {
	int value;
	int suit;

public:
	Card(int value; int suit);
	int getSuit();
	int getValue();


};

#endif
