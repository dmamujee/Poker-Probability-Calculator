#include <iostream>
#include "game.h"
#include "card.h"
#include "string.h"
using namespace std;

ostream& operator<<(ostream& os, Card* card);

int main(int argc, char *argv[]){

	Game* game = new Game();
	Hand* hand = new Hand();
	
	//Get Cards from input
	for (int i = 0; i < 7; i++){
		int value,suitInt;
		char suit;

		cin >> value >> suit;
		if (suit == 'S') suitInt = SPADE;
		else if (suit == 'H') suitInt = HEART;
		else if (suit == 'D') suitInt = DIAMOND;
		else if (suit == 'C') suitInt = CLUB;
		else{
			cout << "Error, Incorrect syntax";
			i--;
			continue;
		}

		if (value < 2 || value > 14){
			cout << "Error, Invalid Value";
			i--;
			continue;
		}

		Card* card = game->getCard(value, suitInt);
		if (i < 5){
			game->updateSingleCommunal(card,i);
		}
		else hand->setCard(i-4,card);
	}

	if ( strcmp(argv[1], "ranking") == 0 ){
		cout << "Hand Ranking: " << game->rankToString( game->handRanking(hand) ) << endl;
	}


}