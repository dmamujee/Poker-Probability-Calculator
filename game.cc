#include "game.h"
#include <typeinfo>
#include <sstream>
using namespace std;

ostream& operator<<(ostream& os, Card* card)
	{
		string suitOutput = "";
		int suit = card->getSuit();
		if (suit == SPADE) suitOutput = "Spades";
		else if (suit == HEART) suitOutput = "Hearts";
		else if (suit == DIAMOND) suitOutput = "Diamonds";
		else if (suit == CLUB) suitOutput = "Clubs";

		string valueOutput = "";
		int value = card->getValue();

		if ( value > 10 ){
			if (value == 11) os << "Jack";
			else if (value == 12) os << "Queen";
			else if (value == 13) os << "King";
			else if (value == 14) os << "Ace";

		} else {
			os << value;
		}

	    os << " of " << suitOutput;
	    return os;
	}


Game::Game(){

	//Creating every Card in the Deck and placing it into array
	for (int suit = 0; suit < 4; suit++){
		for (int value = 2; value < 15; value++){
			deckOfCards[suit][value - 2] = new Card(value, suit + CLUB);
		}
	}

	//Sets all the hands and communal Cards to NULL
	for (int i = 0; i < 5; i++){
		if (i < 2){
			hand1[i] = NULL;
			hand2[i] = NULL;
		}
		communalCards[i] = NULL;
	}
}

Game::~Game(){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 13; j++){
			delete deckOfCards[i][j];
		}
	}	
}


void Game::clearGame(){
	//Sets all the hands and communal Cards to NULL
	for (int i = 0; i < 5; i++){
		if (i < 2){
			hand1[i] = NULL;
			hand2[i] = NULL;
		}
		communalCards[i] = NULL;
	}

}

Card* Game::getCard(int value, int suit){
	return deckOfCards[suit-CLUB][value-2];
}

void Game::updateCommunal(Card *newCommunalCards[5]){
	for (int i = 0; i < 5; i++){
		communalCards[i] = newCommunalCards[i];
	}
}

void Game::updateSingleCommunal(Card* newCard, int location){
	if (location < 0 || location > 4) return;
	communalCards[location] = newCard;
	}

bool Game::isFlush(Card *allCards[7]){
	int Suits[4] = {SPADE, HEART, DIAMOND, CLUB};
	//Check if the 7 cards are suited for each suit
	for (int i = 0; i < 4; i++){
		int counter = 0;
		for (int j = 0; j < 7; j++){
			if (allCards[j]->getSuit() == Suits[i]) counter++;

			//If this case is true, then it is impossible for the cards to be suited, so break loop
			if ( (j - counter) >= 2 ) break;
		}
		//If there are 5 cards of the same suit, then store what suit that is, and break loop
		if (counter >= 5) {
			return true;
		}

	}

	return false;

}

bool Game::isQuads(Card *allCards[7]){
	//Since we know that the Cards will be sorted, we just need to go 4 cards
	//after each card to check if there are 4 of the same kind
	for (int i = 0; i < 4; i++){
		for (int j = i+1; j < i+4; j++){
			//If 2 cards match, don't match then break
			if ( allCards[i]->getValue() != allCards[j]->getValue() ) break;
			else if (j == i+3) return true;
		}
	}

	return false;
}

bool Game::isStraight(Card *allCards[7]){
	int cardsInStraight = 0;
	for(int location = 0; location < 6; location++){	
		//If we have more than a difference of 3 between cards found and cards left, then
		//impossible to have a straight, so we return false
		if( (location - cardsInStraight) > 3 ) return false;

		//If current card and next card have the same value, then continue 
		if (allCards[location]->getValue() == allCards[location+1]->getValue()) continue;

		//Finds wheel straights, by check if for an ace when finding a 2
		if (allCards[location]->getValue() == 2 && allCards[6]->getValue() == 14 ){
			cardsInStraight++;
		}

		if ( (allCards[location]->getValue() + 1) == allCards[location+1]->getValue()){
			cardsInStraight++;
		}
		else cardsInStraight = 0;
		if (cardsInStraight == 4) return true;
	}
	return false;
}

bool Game::isTriple(Card *allCards[7]){
	for (int i = 0; i < 5; i++){
			if (allCards[i]->getValue() == allCards[i+1]->getValue()
				&& allCards[i]->getValue() == allCards[i+2]->getValue()){
				return true;
			}
	}

	return false;
}

bool Game::isOnePair(Card *allCards[7]){
	bool foundPair = false;
	for (int i = 0; i < 6; i++){
			if (allCards[i]->getValue() == allCards[i+1]->getValue()){
				if (!foundPair) foundPair = true;
				else return false;
			}
	}

	if (foundPair) return true;
	else return false;
}

bool Game::isStraightFlush(Card *allCards[7]){
	int cardsInStraight = 0;
	for(int location = 0; location < 6; location++){		
		if( (location - cardsInStraight) > 4 ) return false;

		//If the next card is the same value, or if the next card is one value higher but different suit
		if (allCards[location]->getValue() == allCards[location+1]->getValue()
		|| (allCards[location]->getValue()+1 == allCards[location+1]->getValue() 
				&& allCards[location]->getSuit() != allCards[location+1]->getSuit() ) ) {

			if (location == 5) return false;

			else if (allCards[location]->getValue() == (allCards[location+2]->getValue() - 1)
				&& allCards[location]->getSuit() == allCards[location+2]->getSuit() ){

				location++;
				cardsInStraight++;
			}

			else if (location == 4) return false;

			else if (allCards[location]->getValue() == (allCards[location+3]->getValue() - 1)
				&& allCards[location]->getSuit() == allCards[location+3]->getSuit() ){
				location = location + 2;
				cardsInStraight++;
			}

			else {
				cardsInStraight = 0;
			}


		}

		else if ( (allCards[location]->getValue() + 1) == allCards[location+1]->getValue() 
			&& (allCards[location]->getSuit() == allCards[location+1]->getSuit() ) )  {
			cardsInStraight++;
		}

		else {
			cardsInStraight = 0;				
		} 

		if (cardsInStraight == 4) return true;
	}

	return false;
}

bool Game::isTwoPair(Card *allCards[7]){
	bool foundPair = false;
	for (int i = 0; i < 6; i++){
			if (allCards[i]->getValue() == allCards[i+1]->getValue()){
				if (!foundPair) foundPair = true;
				else return true;
			}
	}

	return false;
}

bool Game::isFullHouse(Card *allCards[7]){
	bool foundPair = false;
	bool foundTriple = false;
	for (int i = 0; i < 6; i++){
			if (allCards[i]->getValue() == allCards[i+1]->getValue()){
				if (i < 5 && !foundTriple){
					if (allCards[i]->getValue() == allCards[i+2]->getValue()){
						foundTriple = true;
						i++;
					}
					else foundPair = true;

				}
				else foundPair = true;
			}
			if (foundPair && foundTriple) return true;
	}

	return false;

}

string Game::rankToString(int rank){
	const char* cardRanks[] = {"Straight Flush", "Four of a Kind", "Full House",
	 "Flush", "Straight", "Three of a Kind", "Two Pair", "One Pair", "High Card", "Invalid"};
	return cardRanks[rank-STRAIGHT_FLUSH];

}

// If all Communal Cards have come out, then determines the ranking of the hand
int Game::handRanking(Card *card1, Card* card2){


	Card* allCards[7];
	
	// Checks that all Communal Cards have come out
	for (int i = 0; i < 5; i++){
		if (communalCards[i] == NULL) {
			#ifdef DEBUG
				cout << "Communal Card is NULL" << endl;
			#endif

			return -1;
		}
		else allCards[i] = communalCards[i];
	}
 	
 	allCards[5] = card1;
	allCards[6] = card2;

 	//Checks that none of the communal cards, or the given hand, are the same
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
			if ( (i != j) && (allCards[i] == allCards[j]) ) {
				#ifdef DEBUG
					cout << "Given hand is same card as communal card" << endl;
					cout << "Card" << i << ": " << allCards[i] << endl;
					cout << "Card" << j << ": " << allCards[j] << endl;
				#endif

				return INVALID;
			}
		}
	}

	//Sort allCards by value, using Bubble sort
	// If value is the same, sort in order: Spade, Heart, Diamond, Club
	for (int i = 1; i < 7; i++){

		if ( allCards[i-1]->getValue() >= allCards[i]->getValue() ){
			if ( (allCards[i-1]->getValue() == allCards[i]->getValue() ) && 
			( allCards[i-1]->getSuit() < allCards[i]->getSuit() ) ){
				continue;
			}
			//Swap the 2 elements
			Card* temp = allCards[i];
			allCards[i] = allCards[i-1];
			allCards[i-1] = temp;
			i = 0;
		}

	}


	#ifdef DEBUG
		cout << "Priting all cards:" << endl;
		for (int i = 0; i < 7; i++){
			cout << allCards[i] << endl;
		}
	#endif



	/*TODO:
		In future, if order of this check is reversed will reverse overall runtime.
		The Straight Flush is the least likely hand, but it takes the most time to check,
		so it doesn't really make sense to be checking it everytime.

		To do this the individual functions for each hand ranking will need to be changed

	*/

	//Check if Cards can create a straight flush
	if (isStraightFlush(allCards)) return STRAIGHT_FLUSH;


	//Check if Cards can create 4 of a Kind
	if (isQuads(allCards)) return FOUR_OF_KIND;


	//Check if Cards can create a Full House
	if (isFullHouse(allCards)) return FULL_HOUSE;

	//Check if Cards can create a Flush
	if (isFlush(allCards)) return FLUSH;


	//Check if Cards can create a Straight
	if (isStraight(allCards)) return STRAIGHT;


	//Check if cards can create 3 of a Kind
	if (isTriple(allCards)) return THREE_OF_A_KIND;


	// Check if Cards can create 2 Pairs
	if (isTwoPair(allCards)) return TWO_PAIR;


	//Checks if Cards cane create a Pair;
	if (isOnePair(allCards)) return ONE_PAIR;


	//Only possible hand left that the Cards could create is a High Card
	else return HIGH_CARD;


}
