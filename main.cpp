#include "Declarations.h"
#include "Queue.h"
#include "CardStack.h"

int main() {

	//Declaration of time variable so that we can generate random numbers
	clock_t t;
	t = clock();
	srand(time(NULL));

	//Card file variables
	ifstream card_file;
	card_file.open("Cards.txt", ios::in);
	int i = 1;
	string temp_data;
	std::string::size_type sz;

	//General variables
	int option = 0;
	bool playing = true;
	card list_of_cards[121];
	list_of_cards[0] = { "NULL CARD", "MissingIMG", 0, 0, "NULL" };
	bool building = true;
	bool trading = true;
	card temp_card;
	int turn_order;
	bool dueling = true;
	
	//delay(10);

	//Import cards fron Cards.txt
	while (card_file.good()) {

		getline(card_file, list_of_cards[i].Name, ',');
		getline(card_file, temp_data, ',');
		list_of_cards[i].atk = std::stoi(temp_data, &sz);
		getline(card_file, temp_data, ',');
		list_of_cards[i].def = std::stoi(temp_data, &sz);
		getline(card_file, list_of_cards[i].type, '\n');

		//cout << i << ": " << list_of_cards[i].Name << ", " << list_of_cards[i].atk << ", " << list_of_cards[i].def << ", " << list_of_cards[i].type << endl;

		i++;

	}

	//Player 1 variables
	int player1_life = 0;
	bool player1_win = false;
	card player1_hand[5];
	int p1_cards_in_hand = 0;
	CardStack player1_deck(40);
	CardStack player1_deck_copy(40);
	int p1_parallel_list[121];
	card player1_trading_deck[40];
	int p1_trade_i = 0;
	int player1_life_points = 0;
	Queue player1_attack_queue;
	Queue player1_defense_queue;
	card player1_attack_card;
	card player1_defense_card;
	int p1_battle_option;

	//Player 2 variables
	int player2_life = 0;
	bool player2_win = false;
	card player2_hand[5];
	int p2_cards_in_hand = 0;
	CardStack player2_deck(40);
	CardStack player2_deck_copy(40);
	int p2_parallel_list[121];
	card player2_trading_deck[40];
	int p2_trade_i = 0;
	int player2_life_points = 0;
	Queue player2_attack_queue;
	Queue player2_defense_queue;
	card player2_attack_card;
	card player2_defense_card;
	int p2_battle_option;



	//Test
	/*i = 1;
	while (i < 41) {

		player1_deck.push(list_of_cards[i]);
		i++;

	}
	player1_deck.shuffle();
	player1_deck.print();
	delay(20);*/


	//Game plays until option 5 is picked
	while (playing) {


		//Menu (FINISHED 3/20/20)
		do {

			system("CLS");
			print_menu();
			cin >> option;
			system("CLS");

		} while (option < 1 || option > 5);


		//Option entered above decides which mode is active
		switch (option) {

		//Display rules (FINISHED 3/20/20)
		case 1:
			
			//Display rules
			display_rules();
			option = 0;
			break;


		//Build decks (FINISHED 3/25/20)
		case 2:

			//Empty decks
			player1_deck.clear_stack();
			player2_deck.clear_stack();

			//Build player 1's deck
			do {
				cout << "Player 1, would you like a pre-build deck or a deck of your own? 1 = pre-built, 2 = custom";
				cin >> option;
			} while (option != 1 && option != 2);


			if (option == 1) {
				player1_deck.pre_build_deck(list_of_cards);				
			}
			else if (option == 2) {

				i = 1;
				p1_parallel_list[0] = 1;
				for (; i < 121; i++) {
					p1_parallel_list[i] = 0;
				}
				i = 1;
				player1_deck.custom_build_deck(list_of_cards, p1_parallel_list);

			}

			//Build player 2's deck
			do {
				cout << "Player 2, would you like a pre-build deck or a deck of your own? 1 = pre-built, 2 = custom";
				cin >> option;
			} while (option != 1 && option != 2);


			if (option == 1) {
				player2_deck.pre_build_deck(list_of_cards);
			}
			else if (option == 2) {

				i = 1;
				p2_parallel_list[0] = 1;
				for (; i < 121; i++) {
					p2_parallel_list[i] = 0;
				}
				i = 1;
				player2_deck.custom_build_deck(list_of_cards, p2_parallel_list);

			}
			

			//End deck building; clean up
			cout << endl << "Deck building is complete. Press any button to continue..." << endl;
			_getch();
			i = 1;
			option = 0;
			break;


		//Trade cards (FINISHED 3/27/20)
		case 3:

			//If there are cards in both player's decks, begin trading
			if (player1_deck.isFull() && player2_deck.isFull()) {

				i = 0;
				while (!player1_deck.isEmpty()) {				
					player1_deck.pop(player1_trading_deck[i]);
					i++;
				}
				i = 0;
				while (!player2_deck.isEmpty()) {
					player2_deck.pop(player2_trading_deck[i]);
					i++;
				}
				i = 1;

				while (trading) {

					system("CLS");
					cout << endl << "---------------------------------------------------------------------" << endl;
					cout << "Player 1's deck" << endl << endl;
					for (i = 0; i < 40; i++) {

						cout << i + 1 << ": ";
						print_card(player1_trading_deck[i]);

					}
					cout << endl << "---------------------------------------------------------------------" << endl;
					cout << "Player 2's deck" << endl << endl;
					for (i = 0; i < 40; i++) {

						cout << i + 1 << ": ";
						print_card(player2_trading_deck[i]);

					}
					cout << endl << "---------------------------------------------------------------------" << endl;

					do {
						cout << endl << "Which player wants to trade? (Enter 1 for player 1, 2 for player 2, or 0 to exit trading) :" << endl;
						cin >> option;
					} while (option != 0 && option != 1 && option != 2);

					//End trading, put cards back in decks
					if (option == 0) {
						trading = false;
						while (!player1_deck.isFull()) {
							i = 0;
							player1_deck.push(player1_trading_deck[i]);
							i++;
						}
						while (!player2_deck.isFull()) {
							i = 0;
							player2_deck.push(player2_trading_deck[i]);
							i++;
						}
						i = 1;
						player1_deck.shuffle();
						player2_deck.shuffle();
					}
					else if (option == 1) {

						cout << "Which card do you offer up player 1? Enter the number" << endl;
						cin >> p1_trade_i;
						p1_trade_i -= 1;
						cout << "Player 1 offers up " << player1_trading_deck[p1_trade_i].Name << endl;

						cout << "Which card will you offer player 2? Enter the number" << endl;
						cin >> p2_trade_i;
						p2_trade_i -= 1;
						cout << "Player 2 offers up " << player2_trading_deck[p2_trade_i].Name << endl;

						do {

							cout << endl << endl << "If both parties are in agreement for the trade of " << player1_trading_deck[p1_trade_i].Name << endl;
							cout << " for " << player2_trading_deck[p2_trade_i].Name << ", enter 1. Otherwise enter 0" << endl;
							cin >> option;

						} while (option != 1 && option != 0);

						if (option == 1) {

							temp_card = player2_trading_deck[p2_trade_i];
							player2_trading_deck[p2_trade_i] = player1_trading_deck[p1_trade_i];
							player1_trading_deck[p1_trade_i] = temp_card;

							cout << "Trade complete" << endl;
							delay(3);

						}
						else {

							cout << "The trade has been cancelled..." << endl;
							delay(3);

						}

					}
					else if (option == 2) {

						cout << "Which card do you offer up player 2? Enter the number" << endl;
						cin >> p2_trade_i;
						p2_trade_i -= 1;
						cout << "Player 2 offers up " << player2_trading_deck[p2_trade_i].Name << endl;

						cout << "Which card will you offer player 1? Enter the number" << endl;
						cin >> p1_trade_i;
						p1_trade_i -= 1;
						cout << "Player 1 offers up " << player1_trading_deck[p1_trade_i].Name << endl;

						do {

							cout << endl << endl << "If both parties are in agreement for the trade of " << player2_trading_deck[p2_trade_i].Name << endl;
							cout << " for " << player1_trading_deck[p1_trade_i].Name << ", enter 1. Otherwise enter 0" << endl;
							cin >> option;

						} while (option != 1 && option != 0);

						if (option == 1) {

							temp_card = player2_trading_deck[p2_trade_i];
							player2_trading_deck[p2_trade_i] = player1_trading_deck[p1_trade_i];
							player1_trading_deck[p1_trade_i] = temp_card;

							cout << "Trade complete..." << endl;
							delay(3);

						}
						else {

							cout << "The trade has been cancelled..." << endl;
							delay(3);

						}

					}

				}
			}
			//If decks aren't built, no trading
			else {

				cout << "Both player's decks must be built before trading..." << endl;

			}
			
			//End trading; cleanup variables
			cout << endl << "Press any button to continue..." << endl;
			_getch();	
			i = 1;
			trading = true;
			option = 0;
			break;


		//Play game (FINISHED 3/27/20)
		case 4:

			if (player1_deck.isFull() && player2_deck.isFull()) {
				option = 0;
				player1_life_points = 8000;
				player2_life_points = 8000;
				player1_deck.shuffle();
				player2_deck.shuffle();
				p1_cards_in_hand = 0;
				p2_cards_in_hand = 0;
				//player1_deck_copy.reset_deck(player1_deck);
				//player2_deck_copy.reset_deck(player2_deck);

				turn_order = coin_toss();
				delay(3);

				system("CLS");
				while (p1_cards_in_hand < 5) {
					player1_deck.pop(player1_hand[p1_cards_in_hand]);
					p1_cards_in_hand++;
				}
				while (p2_cards_in_hand < 5) {
					player2_deck.pop(player2_hand[p2_cards_in_hand]);
					p2_cards_in_hand++;
				}

				cout << "It's time to Duel!" << endl;
				delay(2);

				dueling = true;
				while (dueling) {


					//Player 1 going first
					if (turn_order == 1) {

						//Player 1's turn
						do {
							system("CLS");
							cout << "Player 1" << endl;
							for (int count = 0; count < 5; count++) {
								cout << count + 1 << ": ";
								print_card(player1_hand[count]);
							}
							cout << "Which card would you like to defend? Enter it's number" << endl;
							cin >> option;
						} while (option < 1 || option > 5);
						option -= 1;

						cout << "You have chosen " << player1_hand[option].Name << " to defend you. " << endl;
						player1_defense_queue.enqueue(player1_hand[option]);
						player1_hand[option].Name = list_of_cards[0].Name;
						delay(2);


						do {
							system("CLS");
							cout << "Player 1" << endl;
							for (int count = 0; count < 5; count++) {
								if (player1_hand[count].Name != list_of_cards[0].Name) {
									cout << count + 1 << ": ";
									print_card(player1_hand[count]);
								}						
							}
							cout << "Which card would you like to attack? Enter it's number" << endl;
							cin >> option;
						} while ((option < 1 || option > 5) || (player1_hand[option - 1].Name == list_of_cards[0].Name));
						option -= 1;

						cout << "You have chosen " << player1_hand[option].Name << " to attack for you. " << endl;
						player1_attack_queue.enqueue(player1_hand[option]);
						player1_hand[option].Name = list_of_cards[0].Name;
						delay(2);

						do {

							cout << "Now choose a battle option, ATTACK(1) DEFENSE(2)" << endl;
							cin >> p1_battle_option;

						} while (p1_battle_option != 1 && p1_battle_option != 2);
						if (p1_battle_option == 1) {
							cout << "You have chosen to attack" << endl;
						}
						else {
							cout << "You have chosen to defend" << endl;
						}
						delay(2);

						//Player 2's turn
						do {
							system("CLS");
							cout << "Player 2" << endl;
							for (int count = 0; count < 5; count++) {
								cout << count + 1 << ": ";
								print_card(player2_hand[count]);
							}
							cout << "Which card would you like to defend? Enter it's number" << endl;
							cin >> option;
						} while (option < 1 || option > 5);
						option -= 1;

						cout << "You have chosen " << player2_hand[option].Name << " to defend you. " << endl;
						player2_defense_queue.enqueue(player2_hand[option]);
						player2_hand[option].Name = list_of_cards[0].Name;
						delay(2);


						do {
							system("CLS");
							cout << "Player 2" << endl;
							for (int count = 0; count < 5; count++) {
								if (player2_hand[count].Name != list_of_cards[0].Name) {
									cout << count + 1 << ": ";
									print_card(player2_hand[count]);
								}
							}
							cout << "Which card would you like to attack? Enter it's number" << endl;
							cin >> option;
						} while ((option < 1 || option > 5) || (player2_hand[option - 1].Name == list_of_cards[0].Name));
						option -= 1;

						cout << "You have chosen " << player2_hand[option].Name << " to attack for you. " << endl;
						player2_attack_queue.enqueue(player2_hand[option]);
						player2_hand[option].Name = list_of_cards[0].Name;
						delay(2);

						do {

							cout << "Now choose a battle option, ATTACK(1) DEFENSE(2)" << endl;
							cin >> p2_battle_option;

						} while (p2_battle_option != 1 && p2_battle_option != 2);
						if (p2_battle_option == 1) {
							cout << "You have chosen to attack" << endl;
						}
						else {
							cout << "You have chosen to defend" << endl;
						}
						delay(2);

					}
					//Player 2 going first
					else if (turn_order == 2) {

						//Player 2's turn
						do {
							system("CLS");
							cout << "Player 2" << endl;
							for (int count = 0; count < 5; count++) {
								cout << count + 1 << ": ";
								print_card(player2_hand[count]);
							}
							cout << "Which card would you like to defend? Enter it's number" << endl;
							cin >> option;
						} while (option < 1 || option > 5);
						option -= 1;

						cout << "You have chosen " << player2_hand[option].Name << " to defend you. " << endl;
						player2_defense_queue.enqueue(player2_hand[option]);
						player2_hand[option].Name = list_of_cards[0].Name;
						delay(2);


						do {
							system("CLS");
							cout << "Player 2" << endl;
							for (int count = 0; count < 5; count++) {
								if (player2_hand[count].Name != list_of_cards[0].Name) {
									cout << count + 1 << ": ";
									print_card(player2_hand[count]);
								}
							}
							cout << "Which card would you like to attack? Enter it's number" << endl;
							cin >> option;
						} while ((option < 1 || option > 5) || (player2_hand[option - 1].Name == list_of_cards[0].Name));
						option -= 1;

						cout << "You have chosen " << player2_hand[option].Name << " to attack for you. " << endl;
						player2_attack_queue.enqueue(player2_hand[option]);
						player2_hand[option].Name = list_of_cards[0].Name;
						delay(2);

						do {

							cout << "Now choose a battle option, ATTACK(1) DEFENSE(2)" << endl;
							cin >> p2_battle_option;

						} while (p2_battle_option != 1 && p2_battle_option != 2);
						if (p2_battle_option == 1) {
							cout << "You have chosen to attack" << endl;
						}
						else {
							cout << "You have chosen to defend" << endl;
						}
						delay(2);

						//Player 1's turn
						do {
							system("CLS");
							cout << "Player 1" << endl;
							for (int count = 0; count < 5; count++) {
								cout << count + 1 << ": ";
								print_card(player1_hand[count]);
							}
							cout << "Which card would you like to defend? Enter it's number" << endl;
							cin >> option;
						} while (option < 1 || option > 5);
						option -= 1;

						cout << "You have chosen " << player1_hand[option].Name << " to defend you. " << endl;
						player1_defense_queue.enqueue(player1_hand[option]);
						player1_hand[option].Name = list_of_cards[0].Name;
						delay(2);


						do {
							system("CLS");
							cout << "Player 1" << endl;
							for (int count = 0; count < 5; count++) {
								if (player1_hand[count].Name != list_of_cards[0].Name) {
									cout << count + 1 << ": ";
									print_card(player1_hand[count]);
								}
							}
							cout << "Which card would you like to attack? Enter it's number" << endl;
							cin >> option;
						} while ((option < 1 || option > 5) || (player1_hand[option - 1].Name == list_of_cards[0].Name));
						option -= 1;

						cout << "You have chosen " << player1_hand[option].Name << " to attack for you. " << endl;
						player1_attack_queue.enqueue(player1_hand[option]);
						player1_hand[option].Name = list_of_cards[0].Name;
						delay(2);

						do {

							cout << "Now choose a battle option, ATTACK(1) DEFENSE(2)" << endl;
							cin >> p1_battle_option;

						} while (p1_battle_option != 1 && p1_battle_option != 2);
						if (p1_battle_option == 1) {
							cout << "You have chosen to attack" << endl;
						}
						else {
							cout << "You have chosen to defend" << endl;
						}
						delay(2);

					}
					else {

						cout << "Error in Coin Flip Function" << endl;
						dueling = false;

					}


					//Battle
					if (dueling != false) {
						system("CLS");
						cout << "Player 1: " << player1_life_points << endl;
						cout << "Player 2: " << player2_life_points << endl;
						cout << "Battle!" << endl << endl;
						delay(2);

						//Player 1's choice
						cout << "Player 1: I chose ";
						if (p1_battle_option == 1) {
							cout << "ATTACK!" << endl;
							delay(2);
							player1_attack_queue.dequeue(player1_attack_card);
							cout << "Reveal Monster! " << player1_attack_card.Name << "!" << endl;
							print_card(player1_attack_card);
							delay(2);
						}
						else {
							cout << "DEFEND!" << endl;
							delay(2);
							player1_defense_queue.dequeue(player1_defense_card);
							cout << "Reveal Monster! " << player1_defense_card.Name << "!" << endl;
							print_card(player1_defense_card);
							delay(2);
						}

						//Player 2's choice
						cout << endl;
						cout << "Player 2: I chose ";
						if (p2_battle_option == 1) {
							cout << "ATTACK!" << endl;
							delay(2);
							player2_attack_queue.dequeue(player2_attack_card);
							cout << "Reveal Monster! " << player2_attack_card.Name << "!" << endl;
							print_card(player2_attack_card);
							delay(2);
						}
						else {
							cout << "DEFEND!" << endl;
							delay(2);
							player2_defense_queue.dequeue(player2_defense_card);
							cout << "Reveal Monster! " << player2_defense_card.Name << "!" << endl;
							print_card(player2_defense_card);
							delay(2);
						}

						//Damage Calculation
						cout << "FIGHT!";
						for (int count = 0; count < 1; count++) {

							delay(1);
							cout << ".";

						}
						cout << endl;

						if (p1_battle_option == 2 && p2_battle_option == 2) {

							cout << "Both players chose defense. Both cards are discarded" << endl;
							delay(3);

						}
						else if (p1_battle_option == 1 && p2_battle_option == 1) {

							if (player1_attack_card.atk > player2_attack_card.atk) {
								cout << "Player 1's Monster was more powerful than Player 2's!" << endl;
								cout << "Player 2 loses " << player1_attack_card.atk - player2_attack_card.atk << " life points!" << endl;
								player2_life_points -= (player1_attack_card.atk - player2_attack_card.atk);
							}
							else if (player1_attack_card.atk < player2_attack_card.atk) {
								cout << "Player 2's Monster was more powerful than Player 1's!" << endl;
								cout << "Player 1 loses " << player2_attack_card.atk - player1_attack_card.atk << " life points!" << endl;
								player1_life_points -= (player2_attack_card.atk - player1_attack_card.atk);
							}
							else if (player1_attack_card.atk == player2_attack_card.atk) {
								cout << "Both Player's Monsters are evenly matched!" << endl;
								cout << "No life points are lost..." << endl;
							}
							else {
								cout << "ERROR 2";
							}

						}
						else if (p1_battle_option == 1 && p2_battle_option == 2) {

							if (player1_attack_card.atk > player2_defense_card.def) {
								cout << "Player 1's Monster overpowers Player 2's Defense Card!" << endl;
								cout << "Player 2 loses " << player1_attack_card.atk - player2_defense_card.def << " life points!" << endl;
								player2_life_points -= (player1_attack_card.atk - player2_defense_card.def);
							}
							else if (player1_attack_card.atk < player2_defense_card.def) {
								cout << "Player 2's Monster's Defense was too great for Player 1's Monster!" << endl;
								cout << "Player 1 loses " << player2_defense_card.def - player1_attack_card.atk << " life points!" << endl;
								player1_life_points -= (player2_defense_card.def - player1_attack_card.atk);
							}
							else if (player1_attack_card.atk == player2_defense_card.def) {
								cout << "Both Player's Monsters are evenly matched!" << endl;
								cout << "No life points are lost..." << endl;
							}
							else {
								cout << "ERROR 3";
							}
						}
						else if (p1_battle_option == 2 && p2_battle_option == 1) {

							if (player2_attack_card.atk > player1_defense_card.def) {
								cout << "Player 2's Monster overpowers Player 1's Defense Card!" << endl;
								cout << "Player 1 loses " << player2_attack_card.atk - player1_defense_card.def << " life points!" << endl;
								player1_life_points -= (player2_attack_card.atk - player1_defense_card.def);
							}
							else if (player2_attack_card.atk < player1_defense_card.def) {
								cout << "Player 1's Monster's Defense was too great for Player 2's Monster!" << endl;
								cout << "Player 2 loses " << player1_defense_card.def - player2_attack_card.atk << " life points!" << endl;
								player2_life_points -= (player1_defense_card.def - player2_attack_card.atk);
							}
							else if (player2_attack_card.atk == player1_defense_card.def) {
								cout << "Both Player's Monsters are evenly matched!" << endl;
								cout << "No life points are lost..." << endl;
							}
							else {
								cout << "ERROR 4";
							}
						}
						else {
							cout << "ERROR 0";
						}
						delay(5);

						//Check to see if any player has lost through losing all their life points
						if (player1_life_points <= 0) {
							cout << "Player 1 has run out of life points. Player 2 is the winner!" << endl;
							dueling = false;
							delay(2);
						}
						else if (player2_life_points <= 0) {
							cout << "Player 2 has run out of life points. Player 1 is the winner!" << endl;
							dueling = false;
							delay(2);
						}

						//Display Life Points
						system("CLS");
						cout << "Player 1: " << player1_life_points << endl;
						cout << "Player 2: " << player2_life_points << endl;
						delay(4);

						//Draw cards
						if (dueling) {

							cout << "Drawing Cards...";
							for (int count = 0; count < 1; count++) {

								delay(1);
								cout << ".";

							}
							cout << endl;

							//Player 1 draw cards
							for (int count = 0; count < 5; count++) {
								if (!player1_deck.isEmpty()) {
									if (player1_hand[count].Name == list_of_cards[0].Name) {
										player1_deck.pop(player1_hand[count]);
									}
								}
							}

							//Player 2 draw cards
							for (int count = 0; count < 5; count++) {
								if (!player2_deck.isEmpty()) {
									if (player2_hand[count].Name == list_of_cards[0].Name) {
										player2_deck.pop(player2_hand[count]);
									}
								}
							}
							
							//Check to see if there are no more cards in either player's decks
							if (player1_deck.isEmpty() && player2_deck.isEmpty()) {
								cout << "Both Players have no more cards in their deck. This duel ends in a draw";
								for (int count = 0; count < 1; count++) {

									delay(1);
									cout << ".";

								}
								cout << endl;
								dueling = false;
							}

						}

					}

					
				}

				cout << "Now that the duel is over, you will have to build new decks..." << endl;
				delay(5);

			}
			else {
				cout << "Both player's decks must be built before dueling..." << endl;
			}


			//player1_deck.reset_deck(player1_deck_copy);
			//player2_deck.reset_deck(player2_deck_copy);

			//End dueling; cleanup variables
			cout << endl << "Press any button to continue..." << endl;
			_getch();
			dueling = true;
			option = 0;
			break;


		//Exit Game (FINISHED 3/20/20)
		case 5:
			
			playing = false;
			option = 0;
			break;


		//Fail safe (FINISHED 3/20/20)
		default:

			cout << "ERROR &*$$#@! Exiting System immediately..." << endl;
			option = 0;
			break;

		}
	}

	return 0;

}