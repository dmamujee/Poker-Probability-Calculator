#include "game.h"
#include <typeinfo>
using namespace std;

ostream& operator<<(ostream& os, Card* card)
	{
		string suitOutput = "";
		int suit = card->getSuit();
		if (suit == SPADE) suitOutput = "Spades";
		else if (suit == HEART) suitOutput = "Hearts";
		else if (suit == DIAMOND) suitOutput = "Diamonds";
		else if (suit == CLUB) suitOutput = "Clubs";


	    os << card->getValue() << " of " << suitOutput;
	    return os;
	}


Game::Game(){

	//Creating every Card in the Deck and placing it into array
	for (int suit = 0; suit < 4; suit++){
		for (int value = 2; value < 15; value++){
			deckOfCards[suit][value - 2] = new Card(value, suit);
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

void Game::updateCommunal(Card *newCommunalCards[5]){
	for (int i = 0; i < 5; i++){
		communalCards[i] = newCommunalCards[i];
	}
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

				return -1;
			}
		}
	}


	

	#ifdef DEBUG
		cout << "Priting all cards:" << endl;
		for (int i = 0; i < 7; i++){
			cout << allCards[i] << endl;
		}
	#endif

	//Sort allCards by value,
	// If value is the same, sort in order: Spade, Heart, Diamond, Club


	//Check if Cards are suited
	bool suited = false;
	int suit = 0;


	int Suits[4] = {SPADE, HEART, DIAMOND, CLUB};
	//Check if the 7 cards are suited for each suit
	for (int i = 0; i < 4; i++){
		int counter = 0;
		suit = Suits[i];
		for (int j = 0; j < 7; j++){
			
			if (allCards[j]->getSuit() == suit) counter++;

			//If this case is true, then it is impossible for the cards to be suited, so break loop
			if ( (j - counter) >= 2 ) break;
		}
		//If there are 5 cards of the same suit, then store what suit that is, and break loop
		if (counter >= 5) {
			suited = true;
			suit = i;
			break;
		}

	}

	if (suited) return FLUSH;
	





	//Check if Cards can create a straight flush


	//Check if Cards can create 4 of a Kind


	//Check if Cards can create a Full House

	//Check if Cards can create a Flush


	//Check if Cards can create a Straight


	//Check if cards can create 3 of a Kind


	// Check if Cards can create 2 Pairs


	//Checks if Cards cane create a Pair;


	//Only possible hand left that the Cards could create is a High Card


	else return -100;

	




}
