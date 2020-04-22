#include "Header.h"
#include "Game.h"
class MainMenu {
private:
	List trunk; //contains all monsters from Trunk.csv
	//place holder decks will be shuffled into the game decks.
	List deckPh[2];//place holder decks for players 1 and 2.
	void deckList(int);
public:

	MainMenu() {
	}
	~MainMenu() {

	}

	int display();//prints the main menu options to the console
	void createPlayers();
	void editDeck();//opens the edit deck menu.
	void tradeCards();
	void duel();//place holder decks are added into the stack first card first
	bool loadTrunk();//loads the trunk, returns a 0 if no trunk has been found or if 0 cards are loaded.
	void fillDeck(int);//fills a selected players deck with random cards until the deck is full.
	void displayTrunk();
	void displayDeck(int);
	void displayCardInfo(Card);

	//Edit Options
	void addCards();
	void removeCards();
	void randomlyFillDeck();
	void emptyDeck(int);
};