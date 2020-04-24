#include "Header.h"
#include "MainMenu.h"

int main(void) {


	//fasdasdasdasd

	srand(time(NULL));//generates a seed for random numbers
	MainMenu menu;
	menu.loadTrunk();//loads cards from the csv file
	int selection = 0;
	do {
		selection = menu.display();
		clrscr();
		switch (selection) {
		case CREATE_PLAYERS:menu.createPlayers(); break;
		case EDIT_DECK:menu.editDeck(); break;
		case TRADE_CARDS: menu.tradeCards(); break;
		case DUEL: menu.duel(); break;
		case LOAD_TRUNK: menu.loadTrunk(); break;
		case EXIT:break;
		default: selection = 0;  cout << "Please select a valid option.\n"; EnterKey(); break;
		}
	} while (selection != EXIT);

	cout << "Thanks for playing!\n";

	return 0;
}
