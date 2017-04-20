#include "card.h"
#include "game.h"

Card::Card(int value, int suit): value(value), suit(suit){}

int Card::getSuit() {
	return suit;
}

int Card::getValue() {
	return value;
}

bool Card::operator==(Card &other) {
	return ( ( other.getValue() && this->getValue() )
		&& ( other.getSuit() && this->getSuit() ) );
}

bool Card::operator!=(Card &other) {
return !(*this == other);
}


Hand::Hand(Card* card1, Card* card2): card1(card1), card2(card2){}

Hand::Hand(): card1(NULL), card2(NULL){}

Card* Hand::getCard(int i){
	if (i == 1) return this->card1;
	else if (i == 2) return this->card2;
	else {
		cout << "ERROR: card.cc: Hand::getCard()" << endl;
		return NULL;
	}
}

void Hand::setCard(int i, Card* card){
	if (i == 1) this->card1 = card;
	else if (i == 2) this->card2 = card;
	else cout << "ERROR: card.cc: Hand::setCard()" << endl;
}