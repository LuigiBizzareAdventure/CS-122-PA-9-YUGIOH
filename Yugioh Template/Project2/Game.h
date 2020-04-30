#include "Header.h"
#include "Player.h"
#include "Object.h"
class Game {
private:
	int firstPlayer;
	int round;
	Player player[2];
public:
	Game(List preDeck0, List preDeck1) {
		firstPlayer = -1;
		int count = 0;
		Card temp;
		while (count != DECK_SIZE) {
			preDeck0.card(count, temp);
			player[0].insertCardtoDeck(temp);
			preDeck1.card(count, temp);
			player[1].insertCardtoDeck(temp);
			count++;
		}
		round = 1;
		player[0].setLife();
		player[1].setLife();
	}
	void Start();
	int winnerCheck();//returns a 0 if no winner, 1 if player 1 wins, 2 if player 2 wins, or 3 for draw.
	void swapTurn(int&);
	void compSetPhase();
	void playerSetPhase();

	void compBattlePhase();
	void playerBattlePhase();
	void setFirstPlayer(int aPlayer) {
		firstPlayer = aPlayer;
	}
	void damageCalculation();


	void display();
};