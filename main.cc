#include <iostream>
#include "game.h"
#include "card.h"
#include "string.h"
using namespace std;

ostream& operator<<(ostream& os, Card* card);

//TODO: in main(), have main keep intaking input until EOF

int main(int argc, char *argv[]){
	cout << "hi";
	Game* game = new Game();
	Hand* hand[10];

	for (int i = 0; i < 10; i++){
		hand[i] = new Hand();
	}
	
	//TODO Change this!!!!!
	int cards;
	if (argc == 1) cards = 0;
	else if (strcmp(argv[1], "ranking") == 0) cards = 7;
	else if (strcmp(argv[1], "comparison") == 0) cards = 9;
	else cards = 0;
	
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

	
	if (argc == 1){
		cout << "Welcome to the No Limit Holdem Poker Calculator!" << endl;
		cout << "Please enter which point of the hand you would like to calculate [Preflop, Flop, Turn]:" << endl;
		string handPoint;
		while (true){
			cin >> handPoint;
			if (handPoint == "Preflop" || handPoint == "preflop"){
				break;
			} else if (handPoint == "flop" || handPoint == "flop"){
				cout << "hi2" << endl;
				break;
			} else if (handPoint == "turn" || handPoint == "turn"){
				cout << "hi2" << endl;
				break;
			} else {
				cout << "Invalid input. Please enter one of the following 3 options: [Preflop, Flop, Turn]" << endl;
				continue;
			}
		}

		for (int i = 1; i < 3; i++){
			cout << "Please enter hand " << i << ", in the Format [5 H 7 D], which would represent the 5 of hearts and the 7 of diamonds (Note: 14 represents Ace): " << endl;
			int card1value, card2value, suitInt1, suitInt2;
			char card1suit, card2suit;
			bool flag = true;
			while(true){
				cin >> card1value >> card1suit >> card2value >> card2suit;
				if (card1value < 2 || card1value > 14 || card2value < 2 || card2value > 14){
					cout << "Please enter a value between 2 and 14: " << endl;
					continue;
				} else if (card1suit == 'S'){
					suitInt1 = SPADE;
					flag = false;
				} else if (card1suit == 'H') {
					suitInt1 = HEART;
					flag = false;
				} else if (card1suit == 'D'){
				 	suitInt1 = DIAMOND;
				 	flag = false;
				} else if (card1suit == 'C') {
					suitInt1 = CLUB;
					flag = false;
				} if (flag) {
					cout << "Please enter a valid suit [S,H,D,C]:" << endl;
					continue;
				}

				if (card2suit == 'S'){
					suitInt2 = SPADE;
					break;
				} else if (card2suit == 'H'){
					suitInt2 = HEART;
					break;
				} else if (card2suit == 'D') {
					suitInt2 = DIAMOND;
					break;
				} else if (card2suit == 'C') {
					suitInt2 = CLUB;
					break;
				} else {
					cout << "Please enter a valid suit [S,H,D,C]:" << endl;
					continue;
				}

			}

			Card* card1 = game->getCard(card1value, suitInt1);
			Card* card2 = game->getCard(card2value, suitInt2);
			hand[i]->setCard(0, card1);
			hand[i]->setCard(1, card2);


		}








	} else if ( strcmp(argv[1], "ranking") == 0 ){
		cout << "Hand Ranking: " << game->rankToString( game->handRanking(hand[0]) ) << endl;
	} else if ( strcmp(argv[1], "comparison") == 0 ){
		cout << "Hand Winner: " << game->handComparison(hand[0],hand[1]) << endl;
	}




}