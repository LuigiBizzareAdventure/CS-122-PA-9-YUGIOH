#include "Declarations.h"
#include "Queue.h"
#include "CardStack.h"


void delay(int number_of_seconds) {

	int milli_seconds = 1000 * number_of_seconds;
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds);

}


void print_menu() {

	cout << "Welcome to Yu-Gi-Oh" << endl;
	cout << "Enter an option below to proceed" << endl;
	cout << "1: Display Rules" << endl;
	cout << "2: Build Deck" << endl;
	cout << "3: Trade cards (Must have built decks first)" << endl;
	cout << "4: Play Yu-Gi-Oh" << endl;
	cout << "5: Exit Game" << endl;

}

void display_rules() {

	cout << endl << "Rules: " << endl;
	cout << "Players start the Duel with either a pre-made deck" << endl << "or they may choose to start with a deck of their choosing." << endl;
	cout << "Players who choose to make their own deck may choose" << endl << "the cards that they want to put in their deck." << endl;
	cout << "Decks consist of only Monster cards as opposed to the" << endl << "actual game of Yu-Gi-Oh." << endl << endl;
	cout << "After the decks are made and ready, the player who goes" << endl << "first is decided at random with a coin toss" << endl;
	cout << "Players start off with 8000 life points. The duel is over" << endl << "when either player's life total reaches 0." << endl;
	cout << "Each player draws 5 cards from the top of their deck.";
	cout << "During each player's turn, they place one monster from their hand" << endl << "one the field in their attack and defense queues.";
	cout << "After this, they choose whether they want to attack or defend" << endl;
	cout << "Damage plays out after each round accordingly: " << endl << endl;
	cout << "If a player chooses defense and the opponent chooses attack..." << endl << "The player with the defense monster takes no damage" << endl;
	cout << "If the attack of the attack monster is higher than the defense monster's defense," << endl << "the difference in points is dealt to the defender's life points" << endl;
	cout << "If the attack of the attack monster is the same as the defense monster's defense," << endl << "neither are destroyed, but discarded after the round";
	cout << "If the attack of the attack monster is lower than the defense monster's defense," << endl << "the difference in points is dealt to the attacker's life points" << endl;
	cout << endl << "If both players choose defense..." << endl;
	cout << "Both cards are discarded and neither player takes damage" << endl << endl;
	cout << "If both players choose attack..." << endl;
	cout << "The player with the monster with the lowest attack takes damage" << endl << "equal to the difference in the 2 monster's attacks." << endl;
	cout << "If the monsters's attacks are the same, then both are destroyed and" << endl << "neither player takes damage." << endl;
	cout << endl << "Rounds continue to play until one player has no life points." << endl;
	cout << "After each round, each player draws cards until they have 5 in their hand" << endl;
	cout << "If a player runs out of cards in their deck, they lose the game" << endl;
	cout << "Decks consist of 40 cards either pre-made or custom made" << endl << "Even though this isn't exactly part of PA 5, this more closely follows" << endl << "official Yu-Gi-Oh rules" << endl;
	cout << "Decks can only have 1 copy of each card" << endl << endl;

	delay(15);

}

void print_card(card target_card) {

	cout << "| " << target_card.Name << " |" << endl << "| " << target_card.type << endl <<  "| " << target_card.atk << " | " << target_card.def << " | "  << endl << endl;

}

void print_hand(card hand[]) {

	int i = 0;
	while (i < 5) {

		print_card(hand[i]);
		i++;
	}

}

int coin_toss() {

	int option = 0;
	int result = 0;
	int player = 0;

	clock_t t;
	t = clock();
	srand(time(NULL));

	cout << "Both players start at 8000 life points" << endl;

	player = rand() % 2 + 1;
	cout << "Now to decide who goes first, player " << player << ", call the coin flip" << endl;

	do {
		cout << "HEADS (1) TAILS (2)" << endl;
		cin >> option;
	} while (option != 1 && option != 2);

	cout << endl << "Flipping coin..." << endl;

	cout << "  _____   " << endl;
	cout << " |  _  |  " << endl;
	cout << "|  <.>  | " << endl;
	cout << " |_____|  " << endl;
	delay(1);


	for (int i = 0; i < 3; i++) {

		system("CLS");
		cout << "  _____   " << endl;
		cout << " |  _  |  " << endl;
		cout << "|  <.>  | " << endl;
		cout << " |_____|  " << endl;
		delay(1);

		system("CLS");
		cout << "          " << endl;
		cout << " ________ " << endl;
		cout << "  |____|  " << endl;
		cout << "          " << endl;
		delay(1);

		system("CLS");
		cout << "  _____   " << endl;
		cout << " |     |  " << endl;
		cout << "|       | " << endl;
		cout << " |_____|  " << endl;
		delay(1);

		system("CLS");
		cout << "          " << endl;
		cout << "  ______  " << endl;
		cout << "_|______|_" << endl;
		cout << "          " << endl;
		delay(1);		

	}

	result = rand() % 2 + 1;

	if (result == 1) {

		system("CLS");
		cout << "  _____   " << endl;
		cout << " |  _  |  " << endl;
		cout << "|  <.>  | " << endl;
		cout << " |_____|  " << endl;

		cout << "The coin landed on heads" << endl;
		delay(1);

	}
	else if (result == 2) {

		system("CLS");
		cout << "  _____   " << endl;
		cout << " |     |  " << endl;
		cout << "|       | " << endl;
		cout << " |_____|  " << endl;

		cout << "The coin landed on tails" << endl;
		delay(1);

	}
	if (result == option) {

		cout << "Player " << player << " guessed correctly so" << endl;
		cout << "they will be going first." << endl;
		return player;

	}
	else {

		cout << "Player " << player << " guessed incorrently so" << endl;
		int other_player;
		if (player == 1) {
			other_player = 2;
		}
		else {
			other_player = 1;
		}
		cout << "Player " << other_player << " will go first" << endl;
		return other_player;
	}
	

}