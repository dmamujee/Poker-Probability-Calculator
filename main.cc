#include <iostream>
#include "game.h"
#include "card.h"
using namespace std;

int main(){
	Card* card1 = new Card(2,CLUB);
	Card* card2 = new Card(3,CLUB);
	Card* card3 = new Card(4,HEART);
	Card* card4 = new Card(5,HEART);
	Card* card5 = new Card(6,HEART);
	Card* card6 = new Card(10,SPADE);
	Card* card7 = new Card(JACK,DIAMOND);
	Card* card8 = new Card(QUEEN,HEART);
	Card* card9 = new Card(KING,HEART);
	Card* card10 = new Card(ACE,SPADE);
	Card* card11 = new Card(ACE,DIAMOND);
	Card* card12 = new Card(ACE,CLUB);
	Card* card13 = new Card(KING,SPADE);
	Card* card14 = new Card(10,DIAMOND);

	Game* game = new Game();
	Card* communalCards[5] = {card5, card8, card9, card1, card2};
	Card* Hand[2] = {card3, card4};
	game->updateCommunal(communalCards);

	//Should be a flush
	cout << "Hand Ranking: " << game->handRanking(card3, card4) << endl;	


}