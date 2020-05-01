#include "MainMenu.h"


int MainMenu::display(void) {
	int selection = 0;
	cout << "Yugioh Main Menu:\n\n";
	cout << "   Options:\n";
	cout << "      1. Create Players(randomly generates decks)\n";
	cout << "      2. Edit Deck\n";
	cout << "      3. Trade Cards With Opponent\n";
	cout << "      4. Duel\n";
	cout << "      5. Load Trunk\n";
	cout << "      6. Exit\n";
	cout << "\nPlease select an option:";
	cin >> selection;
	flushCin();
	return selection;
}
void MainMenu::displayTrunk(void) {
	int count = 1;
	YCard temp;
	cout << "Trunk Card List" << endl;
	cout.ios_base::setf(ios_base::left, ios_base::adjustfield);
	cout << "Player 1's Deck" << endl;
	cout << " #  " << setw(38) << "Monster Name";
	cout << setw(4) << "ATK";
	cout << " " << setw(4) << "DEF";
	cout << " " << "Type" << endl;
	while (count != trunk.size() + 1) {
		trunk.card(count - 1, temp);//makes a copy of the selected card to temp
		cout.ios_base::setf(ios_base::right, ios_base::adjustfield);
		cout << setw(2) << count << ". ";//acceses the custom << operator from Card.h
		cout.ios_base::setf(ios_base::left, ios_base::adjustfield);
		cout << temp << endl;//////////////////////
		count++;
	}
}
void MainMenu::displayDeck(int player) {
	int count = 1;
	YCard temp;
	cout.ios_base::setf(ios_base::left, ios_base::adjustfield);
	cout << "Player" << player + 1 <<"'s Deck" << endl;
	cout << " #  " << setw(38) << "Monster Name";
	cout << setw(4) << "ATK";
	cout << " " << setw(4) << "DEF";
	cout << " " << "Type" << endl;

	while (count != deckPh[0].size() + 1) {
		deckPh[0].card(count - 1, temp);//makes a copy of the selected card to temp
		cout.ios_base::setf(ios_base::right, ios_base::adjustfield);
		cout << setw(2) << count << ". ";//acceses the custom << operator from Card.h
		cout.ios_base::setf(ios_base::left, ios_base::adjustfield);
		cout << temp << endl;////////////////////////////////
		count++;
	}
}
bool MainMenu::loadTrunk(void) {
	fstream trunkFile;
	char record[200];//buffer to get one line of information from the trunk.
	int recordLength;
	string data;//used to split data from the record up.
	YCard temp;//a temporary card to store data into.
	trunkFile.open("Trunk.csv");
	if (!trunkFile.is_open()) {
		cout << "Trunk.csv could not be found or opened.\n";
		EnterKey();
		return false;
	}
	trunkFile.getline(record, 200);//trunk called a first time to clear the first line of information.
	while (!trunkFile.eof()) {
		
		trunkFile.getline(record, 200);
		recordLength = strlen(record);
		if (record[recordLength - 1] == '\n') {//gets rid of the newline character if found in the record.
			record[recordLength - 1] = '\0';
		}
		data = strtok(record, ",");//the monster name is read from record and stored in data.
		temp.setName(data);//temp name is set to data
		
		data = strtok(NULL, ",");//the attack points are read from record and stored in data.
		temp.setAtk(std::stoi(data));//temp attack set to data
		
		data = strtok(NULL, ",");//the defense points are read from record and stored in data.
		temp.setDef(std::stoi(data));//temp def set to data
		
		data = strtok(NULL, ",");//the moster type is read from record and stored in data.
		temp.setType(data);//temp type is set to data.
		temp.setFrontTexture("cardTextures/" + temp.getName() + ".png");
		trunk.addCard(temp);//temp is stored.
		temp.reset();//resets the temps default settings.

	}
	trunkFile.getline(record, 200);
	recordLength = strlen(record);
	if (trunk.size() == 0) {
		cout << "Trunk.csv has loaded, but no cards were found.\n";
		EnterKey();
		return false;
	}
	else {
		//cout << "Trunk.csv has been succesfully loaded\n";
		//EnterKey();
		return true;
	}
	trunkFile.close();
}
void MainMenu::createPlayers(void) {
	if (trunk.size() == 0) {
		cout << "There must be cards in the trunk to use this feature.\n";
		return;
	}
	emptyDeck(0);
	//cout << "Emptied deck 0\n";
	emptyDeck(1);
	//cout << "Emptied deck 1\n";
	fillDeck(0);//fills player 1's deck with random cards
	//cout << "Filled deck 0\n";
	fillDeck(1);//fills player 2's deck with random cards
	//cout << "Filled deck 1\n";
	//cout << "The deck of each player has been randomly generated.\n";
	//EnterKey();
	return;
}

void MainMenu::fillDeck(int player) {
	
	int count = deckPh[player].size();
	
	while (count != DECK_SIZE) {//loop keeps going until the deck is full
		int randPick = 0;
		randPick = rand() % trunk.size();
		YCard randCard;
		trunk.card(randPick, randCard);//picks a random card from the trunk
		deckPh[player].addCard(randCard);//adds the card to the place holder deck.
		count++;
	}

}
void MainMenu::editDeck(void) {
	if (deckPh[0].size() != DECK_SIZE || deckPh[1].size() != DECK_SIZE) {
		cout << "Players must be created to use this feature.\n";
		EnterKey();
		return;
	}

	int selection = 0;
	do {
		selection = 0;
		displayDeck(0);
		cout << "\nNote: The first card that you will draw is #30 and the last is #1\n";
		cout << "Options:\n";
		cout << "  1.Add specific cards to the deck\n";
		cout << "  2.Remove specific cards from the deck\n";
		cout << "  3.Fill Deck with random cards\n";
		cout << "  4.Remove all cards from the deck\n";
		cout << "  5.Exit\n";
		cout << "Please select an option:";
		cin >> selection;
		flushCin();
		if (selection < 1 || selection > 5)
			selection = 0;

		Edit option = (Edit)selection;
		clrscr();
		switch (option)
		{
		case Edit::ADD_CARDS:addCards(); break;
		case Edit::REMOVE_CARDS:removeCards(); break;
		case Edit::RANDOMLY_FILL: 
			fillDeck(0);
			break;
		case Edit::EMPTY_DECK:
			emptyDeck(0);
			EnterKey();
			break;
		case Edit::EXIT_EDIT:
			if (deckPh[0].size() < DECK_SIZE) {
				cout << "You must have " << DECK_SIZE << " cards in the deck to exit.\n\n";
				selection = INVALID;
			}
			break;
		default:
			selection = INVALID;
			break;
		}

	} while (selection != 5);


}
void MainMenu::addCards(void) {
	int selection = 0;
	do {
		if (deckPh[0].size() == DECK_SIZE) {
			cout << "Max deck size reached. You must remove cards from your deck, before you can add anymore.\n";
			EnterKey();
			return;
		}
		YCard temp;
		displayTrunk();
		cout << "\nWhich card would you like to add to the deck(enter the number, 0 to exit): ";
		cin >> selection;
		flushCin();
		if (selection < 0 || selection > trunk.size())
			selection = INVALID;
		if (selection != INVALID && selection != 0) {
			trunk.card(selection - 1, temp);
			deckPh[0].addCard(temp);
			cout << temp.getName() << " has been added to the deck\n";
			EnterKey();
		}
		clrscr();
	} while (selection != 0);


}
void MainMenu::removeCards(void) {
	int selection = 0;
	do {
		if (deckPh[0].size() == 0)
			cout << "There are no more cards in the deck. You must add some cards before you can continue\n";
			EnterKey(); {
			return;
		}
		YCard temp;
		displayDeck(0);
		cout << "\nWhich card would you like to remove from the deck(enter the number, 0 to exit): ";
		cin >> selection;
		flushCin();
		if (selection < 0 || selection > deckPh[0].size())
			selection = INVALID;
		if (selection != INVALID && selection != 0) {
			deckPh[0].removeCard(selection-1, temp);
			cout << temp.getName() << " has been removed from the deck\n";
			EnterKey();
		}
		clrscr();

	} while (selection != 0);

}
void MainMenu::emptyDeck(int player) {
	int count = deckPh[player].size() - 1;
	while (count != -1) {
		deckPh[player].removeCard(count);//removes all cards from the list.
		count--;
	}
}
void MainMenu::tradeCards(void) {
	if (deckPh[0].size() != DECK_SIZE || deckPh[1].size() != DECK_SIZE) {
		cout << "Players must be created to use this feature.\n";
		EnterKey();
		return;
	}
	int selection1 = 0;
	int selection2 = 0;
	YCard temp1;
	YCard temp2;
	do {
		selection1 = 0;
		selection2 = 0;
		displayDeck(1);
		cout << "\nSelect the # card that you want to take from Player 2(0 to exit):";
		cin >> selection1;
		flushCin();
		if (selection1 < 0 || selection1 > deckPh[1].size())
			selection1 = INVALID;
		if (selection1 != INVALID && selection1 != 0) {
			clrscr();
			displayDeck(0);
			cout << "\nSelect the # card that you want to give to Player 2(0 to exit):";
			cin >> selection2;
			flushCin();
			if (selection2 < 0 || selection2 > deckPh[0].size()) {
				selection2 = INVALID;
			}
			else if (selection2 != 0) {
				deckPh[0].removeCard(selection1 - 1, temp1);
				deckPh[1].removeCard(selection2 - 1, temp2);
				deckPh[0].addCard(temp2);
				deckPh[1].addCard(temp1);
				cout << "The cards have been traded.\n";
				EnterKey();
			}
			
		}
		if (selection1 == INVALID || selection2 == INVALID) {
			cout << "You entered an invalid input please try again.\n";
			EnterKey();
		}
		clrscr();
	} while (selection1 != 0);
	return;
}
void MainMenu::duel() {
	if (deckPh[0].size() != DECK_SIZE || deckPh[1].size() != DECK_SIZE) {
		cout << "Players must be created to use this feature.\n";
		EnterKey();
		return;
	}
		Game game(deckPh[0], deckPh[1], windowPtr);//adds the decks as stacks to the game.
		game.Start();
}

