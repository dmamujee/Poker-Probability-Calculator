#include <iostream>
#include "game.h"
#include "card.h"
#include "string.h"
using namespace std;

ostream& operator<<(ostream& os, Card* card);

//TODO: in main(), have main keep intaking input until EOF

int main(int argc, char *argv[]){

	Game* game = new Game();
	Hand* hand[10];

	for (int i = 0; i < 10; i++){
		hand[i] = new Hand();
	}
	
	//TODO Change this!!!!!
	int cards = 7;
	if (strcmp(argv[1], "comparison") == 0) cards = 9;
	
	//Get Cards from input
	for (int i = 0; i < cards; i++){
		int value,suitInt;
		char suit;

		cin >> value >> suit;
		if (suit == 'S') suitInt = SPADE;
		else if (suit == 'H') suitInt = HEART;
		else if (suit == 'D') suitInt = DIAMOND;
		else if (suit == 'C') suitInt = CLUB;
		else{
			cout << endl << "ERROR: main.cc: main(): Incorrect syntax";
			i--;
			continue;
		}

		if (value < 2 || value > 14){
			cout << endl << "ERROR: main.cc: main(): Invalid Value";
			i--;
			continue;
		}

		Card* card = game->getCard(value, suitInt);
		if (i < 5){
			game->updateSingleCommunal(card,i);
		} else hand[(i-5)/2]->setCard( (i-1)%2 ,card);
	}

	if ( strcmp(argv[1], "ranking") == 0 ){
		cout << "Hand Ranking: " << game->rankToString( game->handRanking(hand[0]) ) << endl;
	} else if ( strcmp(argv[1], "comparison") == 0 ){
		cout << "Hand Winner: " << game->handComparison(hand[0],hand[1]) << endl;
	}




}