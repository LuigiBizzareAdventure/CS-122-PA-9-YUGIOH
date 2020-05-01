#include "Header.h"
#include "List.h"
#include "Stack.h"
#include "Queue.h"

class Player {
private:
	int lifePoints;
	Stack deck;
	YCard temp;//card used to store, and check card values.
public:
	Player() {
		lifePoints = DEFAULT_LIFEPOINTS;
	}
	List hand;
	Stack graveyard;
	Queue attackQueue;
	Queue defenseQueue;

	int atkQueueActivation;
	int defQueueActivation;

	void addLife(unsigned int);//adds life to the player given an int
	bool subLife(unsigned int);//subs life from the player given an int. returns true, if a player hits 0 lifepoints.
	void setLife();//sets a players lifepoints to the default of 8000.
	int getLife();
	
	bool card(int, YCard&);
	void insertCardtoDeck(YCard);//pushes a card to the players deck
	bool drawCard();//draws a card from the deck and adds it to the hand, returns false if a card could not be drawn.
	int getDeckSize(void);
	void addCard(YCard);
	int size(void);
	bool removeCard(int, YCard&);
	bool removeCard(int);
};