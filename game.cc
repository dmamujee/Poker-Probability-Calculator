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
int Game::handRanking(Hand* hand){


	Card* allCards[7];
	
	// Checks that all Communal Cards have come out
	for (int i = 0; i < 5; i++){
		if (communalCards[i] == NULL) {
			#ifdef DEBUG
				cout << endl << "ERROR: game.cc: Game::handRanking(): Communal Card is NULL" << endl;
			#endif

			return -1;
		}
		else allCards[i] = communalCards[i];
	}
 	
 	allCards[5] = hand->getCard(0);
	allCards[6] = hand->getCard(1);

 	//Checks that none of the communal cards, or the given hand, are the same
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
			if ( (i != j) && (allCards[i] == allCards[j]) ) {
				#ifdef DEBUG
					cout << endl << "ERROR: game.cc: Given hand is same card as communal card" << endl;
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


/*
int handComparison(Hand* hand1, Hand* hand2):
Ouput:
1 = Hand 1 wins
2 = Hand 2 wins
0 = tie
-1 = ERROR

*/

int Game::handComparison(Hand* hand1, Hand* hand2){
	
	//Check that niether of the hands have the same cards
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			if (hand1->getCard(i) == hand2->getCard(j)){
			#ifdef DEBUG
				cout << endl << "ERROR, 2 hands share cards: game.cc: Game::handComparison()" << endl;
			#endif
				return -1;
			}
		}
	}


	int hand1Ranking = handRanking(hand1);
	int hand2Ranking = handRanking(hand2);

	if (hand1Ranking < hand2Ranking) return 1;
	else if (hand1Ranking > hand2Ranking) return 2;

	/*
	If we get to this point, then the 2 hands have the same value.
	This means that we must find the values and kickers involved
	*/

	Card* hand1AllCards[7];
	Card* hand2AllCards[7];

	for (int i = 0; i < 5; i++){
		//Place hole cards in the allCards array
		if (i < 2){
			hand1AllCards[5+i] = hand1->getCard(i);
			hand2AllCards[5+i] = hand2->getCard(i);
		}
		hand1AllCards[i] = communalCards[i];
		hand2AllCards[i] = communalCards[i];
	}

	//Sort hand1AllCards by value, using Bubble sort
	// If value is the same, sort in order: Spade, Heart, Diamond, Club
	for (int i = 1; i < 7; i++){

		if ( hand1AllCards[i-1]->getValue() >= hand1AllCards[i]->getValue() ){
			if ( (hand1AllCards[i-1]->getValue() == hand1AllCards[i]->getValue() ) && 
			( hand1AllCards[i-1]->getSuit() < hand1AllCards[i]->getSuit() ) ){
				continue;
			}
			//Swap the 2 elements
			Card* temp = hand1AllCards[i];
			hand1AllCards[i] = hand1AllCards[i-1];
			hand1AllCards[i-1] = temp;
			i = 0;
		}

	}

	//Sort hand2AllCards by value, using Bubble sort
	// If value is the same, sort in order: Spade, Heart, Diamond, Club
	for (int i = 1; i < 7; i++){

		if ( hand2AllCards[i-1]->getValue() >= hand2AllCards[i]->getValue() ){
			if ( (hand2AllCards[i-1]->getValue() == hand2AllCards[i]->getValue() ) && 
			( hand2AllCards[i-1]->getSuit() < hand2AllCards[i]->getSuit() ) ){
				continue;
			}
			//Swap the 2 elements
			Card* temp = hand2AllCards[i];
			hand2AllCards[i] = hand2AllCards[i-1];
			hand2AllCards[i-1] = temp;
			i = 0;
		}

	}


	if (hand1Ranking == HIGH_CARD){

		for (int i = 6; i > 1; i--){
			if (hand1AllCards[i]->getValue() > hand2AllCards[i]->getValue()) return 1;
			else if (hand1AllCards[i]->getValue() < hand2AllCards[i]->getValue()) return 2;

		}
		return 0;
	}

	if (hand1Ranking == ONE_PAIR){
		int hand1Pair = 0;
		int hand2Pair = 0;

		for (int i = 0; i < 6; i++){
			if (hand1AllCards[i]->getValue() == hand1AllCards[i+1]->getValue() ){
				hand1Pair = hand1AllCards[i]->getValue();
			}
			if (hand2AllCards[i]->getValue() == hand2AllCards[i+1]->getValue() ){
				hand2Pair = hand2AllCards[i]->getValue();
			}
		}
		if (hand1Pair == 0 || hand2Pair == 0) cout << endl << "ERROR: game.cc: handComparison()" << endl;

		if (hand1Pair > hand2Pair) return 1;
		else if (hand1Pair < hand2Pair) return 2;

		int count = 0;

		for (int i = 6; i >= 0; i--){
			if (hand1AllCards[i]->getValue() == hand1Pair) continue;
			if (hand1AllCards[i]->getValue() > hand2AllCards[i]->getValue()) return 1;
			if (hand1AllCards[i]->getValue() < hand2AllCards[i]->getValue()) return 2;
			count++;
			if (count >= 3) return 0;
		}

		return -2;
	}

	if (hand1Ranking == FLUSH){
		Card* hand1Flush[5];
		Card* hand2Flush[5];


		int Suits[4] = {SPADE, HEART, DIAMOND, CLUB};
		//Check if the 7 cards are suited for each suit
		for (int i = 0; i < 4; i++){
			int counter = 0;
			for (int j = 6; j >= 0; j--){
				if (hand1AllCards[j]->getSuit() == Suits[i]){
					hand1Flush[counter] = hand1AllCards[j];
					counter++;
				}

				//If this case is true, then it is impossible for the cards to be suited, so break loop
				if ( (j + counter) < 4 ) break;
			}
			if (counter >= 5) {
				break;
			}
		}
		for (int i = 0; i < 4; i++){
			int counter = 0;
			for (int j = 6; j >= 0; j--){
				if (hand2AllCards[j]->getSuit() == Suits[i]){
					hand2Flush[counter] = hand2AllCards[j];
					counter++;
				}

				//If this case is true, then it is impossible for the cards to be suited, so break loop
				if ( (j + counter) < 4 ) break;
			}
			if (counter >= 5) {
				break;
			}
		}
		//At this point we can assume that in each of the hand*Flush arrays, they hold the 5
		//Cards of one suit. So we can just compare them to who has the highest card
		for (int i = 4; i >= 0; i--){
			if (hand1Flush[i]->getValue() > hand2Flush[i]->getValue()) return 1;
			else if (hand1Flush[i]->getValue() < hand2Flush[i]->getValue()) return 2;

		}
		return 0;

	}

	return -1;
}



