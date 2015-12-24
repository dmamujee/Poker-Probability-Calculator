#include "card.h"

Card::Card(int value, int suit): value(value),suit(suit){}

Card::getSuit(){
	return suit;
}

Card::getValue(){
	return value;
}