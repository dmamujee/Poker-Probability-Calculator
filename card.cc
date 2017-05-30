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


Hand::Hand(Card* card0, Card* card1): card0(card0), card1(card1){}

Hand::Hand(): card0(NULL), card1(NULL){}

Card* Hand::getCard(int i){
	if (i == 0) return this->card0;
	else if (i == 1) return this->card1;
	else {
		cout << "ERROR: card.cc: Hand::getCard()" << endl;
		return NULL;
	}
}

void Hand::setCard(int i, Card* card){
	if (i == 0) this->card0 = card;
	else if (i == 1) this->card1 = card;
	else cout << "ERROR: card.cc: Hand::setCard()" << endl;
}
