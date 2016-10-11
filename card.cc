#include "card.h"

Card::Card(int value, int suit): value(value), suit(suit){}

int Card::getSuit() {
	return suit;
}

int Card::getValue() {
	return value;
}

// bool Card::operator==(Card &other) {
// 	return ( ( other.getValue() && this->getValue() )
// 		&& ( other.getSuit() && this->getSuit() ) );
// }

// bool Card::operator!=(Card &other) {
// return !(*this == other);
// }