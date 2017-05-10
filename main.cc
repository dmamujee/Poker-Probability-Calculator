#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
				handPoint = "preflop";
				break;
			} else if (handPoint == "Flop" || handPoint == "flop"){
				handPoint = "flop";
				break;
			} else if (handPoint == "Turn" || handPoint == "turn"){
				handPoint = "turn";
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
			hand[i-1]->setCard(0, card1);
			hand[i-1]->setCard(1, card2);
		}

	#ifdef TIMER
		int start = clock();
	#endif

		int hand1Wins = 0;
		int hand2Wins = 0;
		int ties = 0;
		int total = 0;
		if (handPoint == "turn"){
			cout << "Please enter 4 cards on the board: " << endl;
			while(true){
				int value, suitInt;
				char suit;
				for (int i = 0; i < 4; i++){
					cin >> value >> suit;

					if (value < 2 || value > 14){
						cout << "ERROR" << endl;
						return 0;
					}

					if (suit == 'S') suitInt = SPADE;
					else if (suit == 'H') suitInt = HEART;
					else if (suit == 'D') suitInt = DIAMOND;
					else if (suit == 'C') suitInt = CLUB;
					else{
						cout << "ERROR" << endl;
						return 0;
					}

					game->updateSingleCommunal(game->getCard(value, suitInt),i);

				}
				break;
			}

			for (int i = 0; i < 52; i++){
				game->updateSingleCommunal(game->getCard(i),4);
				int result = game->handComparison(hand[0],hand[1]);
				if (result == -2) continue;
				else if (result == 1) hand1Wins++;
				else if (result == 2) hand2Wins++;
				else if (result == 0) {
					ties++;
				}
				else {
					cout << "ERROR: main(): unpredictced response (turn)" << endl;
					return 0;
				}

			}
		}
		else if (handPoint == "flop"){
			cout << "Please enter 3 cards on the board: " << endl;
			int value, suitInt;
			char suit;
			for (int i = 0; i < 3; i++){
				cin >> value >> suit;

				if (value < 2 || value > 14){
					cout << "ERROR" << endl;
					return 0;
				}

				if (suit == 'S') suitInt = SPADE;
				else if (suit == 'H') suitInt = HEART;
				else if (suit == 'D') suitInt = DIAMOND;
				else if (suit == 'C') suitInt = CLUB;
				else{
					cout << "ERROR" << endl;
					return 0;
				}

				game->updateSingleCommunal(game->getCard(value, suitInt),i);

			}

			for (int i = 0; i < 52; i++){
				game->updateSingleCommunal(game->getCard(i),3);
				for (int j = 0; j < 52; j++){
					if (i == j) continue;
					game->updateSingleCommunal(game->getCard(j),4);
					int result = game->handComparison(hand[0],hand[1]);
					if (result == -2) continue;
					else if (result == 1) hand1Wins++;
					else if (result == 2) hand2Wins++;
					else if (result == 0) {
						ties++;
					}
					else {
						cout << "ERROR: main(): unpredictced response (flop)" << endl;
						return 0;
					}

				}
			}

		}
		else if (handPoint == "preflop"){
			cout << "Calculating..." << endl;

			srand(time(NULL));
			while(total < 100000){
				for (int i = 0; i < 5; i++) {
					game->updateSingleCommunal(game->getCard( rand()%52 ),i);
				}
				int result = game->handComparison(hand[0],hand[1]);
				if (result == -2) continue;
				else if (result == 1) hand1Wins++;
				else if (result == 2) hand2Wins++;
				else if (result == 0) {
					ties++;
				}
				else {
					cout << "ERROR: main(): unpredictced response (preflop)" << endl;
					return 0;
				}
				++total;

				
			}



		}

		if (total == 0) total = (hand1Wins + hand2Wins + ties);
		cout << "hand1Wins: " << hand1Wins << endl;
		cout << "hand2Wins: " << hand2Wins << endl;
		cout << "ties: " << ties << endl;
		cout << "Total: " << total << endl;
		float hand1percent = 100*(float)(hand1Wins + (float)(ties/2) ) /total;
		float hand2percent = 100*(float)(hand2Wins + (float)(ties/2) ) /total;

		cout << "Hand 1 wins " << hand1percent << "% of the time" << endl;
		cout << "Hand 2 wins " << hand2percent << "% of the time" << endl;

	#ifdef TIMER
		double duration = ( clock() - (double)start ) / (double) CLOCKS_PER_SEC;
		cout << "Calculation took: " << duration << " seconds" << endl;
	#endif


	} else if ( strcmp(argv[1], "ranking") == 0 ){
		cout << "Hand Ranking: " << game->rankToString( game->handRanking(hand[0]) ) << endl;
	} else if ( strcmp(argv[1], "comparison") == 0 ){
		cout << "Hand Winner: " << game->handComparison(hand[0],hand[1]) << endl;
	}




}