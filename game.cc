#include "game.h"


Game::Game(){

	//Creating everyy Card in the Deck and placing it into array
	for (int suit = 0; suit < 4; suit++){
		for (int value = 2; value < 15; value++){
			deckOfCards[suit][value - 2] = new Card(value, suit);
		}
	}

	//Sets all the hands and communal Cards to NULL
	for int (i = 0; i < 5; i++){
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
			delete deckOfCards[i][j]
		}
	}	
}

void Game::clearGame(){
	//Sets all the hands and communal Cards to NULL
	for int (i = 0; i < 5; i++){
		if (i < 2){
			hand1[i] = NULL;
			hand2[i] = NULL;
		}
		communalCards[i] = NULL;
	}

}


// If all Communal Cards have come out, then determines the ranking of the hand
int Gmae::handRanking(Card *card1, Card* card2){

	Card* allCards[7];

	// Checks that all Communal Cards have come out
	for (int i = 0; i < 5; i++){
		if (communalCards[i] == NULL) return -1;
		else allCards[i] = communalCards[i];
	}
 	

 	//Checks that none of the communal cards, or the given hand, are the same
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
			if ( (i != j) && (allCards[i] == allCards[j]) ) return -1;
		}
	}


	allCards[5] = card1;
	allCards[6] = card2;

	//Sort allCards




	//Check if Cards can create a straight flush


	//Check if Cards can create 4 of a Kind


	//Check if Cards can create a Full House

	//Check if Cards can create a Flush


	//Check if Cards can create a Straight


	//Check if cards can create 3 of a Kind


	// Check if Cards can create 2 Pairs


	//Checks if Cards cane create a Pair;


	//Only possible hand left that the Cards could create is a High Card

	




}
