#include "Game.h"
#include "Object.h"
void Game::swapTurn(int& player) {
	if (player == 1) {
		player = 0;
	}
	else
		player = 1;
}

void Game::display(void) {
	YCard temp;
	cout << "---------------------------------------------------------------------\n";
	cout << "Enemy Side\n";
	if (player[1].atkQueueActivation) {
		cout << "Attack Queue is Activated.\n";
	}
	if (player[1].defQueueActivation) {
		cout << "Defense Queue is Activated.\n";
	}
	cout << "LifePoints: " << player[1].getLife() << endl;
	cout << "Next in Atk Queue: " << ((player[1].attackQueue.peek(temp)) ? temp.getName() : "None ") << " "<< temp.getAtk() << "ATK + " << temp.getBoost() << "(" << temp.getTypeName() << ")" << endl;
	temp.reset();
	cout << "Next in Def Queue: " << ((player[1].defenseQueue.peek(temp)) ? temp.getName() : "None ") << " "<< temp.getDef() << "DEF" << endl;

	temp.reset();
	cout << "---------------------------------------------------------------------\n";
	cout << "Player Side\n";
	if (player[0].atkQueueActivation) {
		cout << "Attack Queue is Activated.\n";
	}
	if (player[0].defQueueActivation) {
		cout << "Defense Queue is Activated.\n";
	}
	cout << "LifePoints: " << player[0].getLife() << endl;
	temp.reset();
	cout << "Next in Atk Queue: " << ((player[0].attackQueue.peek(temp)) ? temp.getName() : "None") <<" " <<temp.getAtk() << "ATK + " << temp.getBoost() << "(" << temp.getTypeName() << ")" << endl;
	temp.reset();
	cout << "Next in Def Queue: " << ((player[0].defenseQueue.peek(temp)) ? temp.getName() : "None") << " "<< temp.getDef() << "DEF" << endl;
	cout << "\n---------------------------------------------------------------------\n";
}
void Game::Start() {
	player[0].setLife();
	player[1].setLife();
	YCard temp; //used for functions

	//Create Yugioh Font 
	sf::Font yugioh;
	yugioh.loadFromFile("squealer embossed.ttf");

	//render window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Yugioh");
	window.setFramerateLimit(30);
	sf::Event event;

	//Create a background
	sf::RectangleShape background(sf::Vector2f(800, 800));
	background.setFillColor(sf::Color::Black);
	background.setPosition(0, 0);

	//Create Regular Font 
	sf::Font regular;
	regular.loadFromFile("Bebas-Regular.ttf");

	// create front of coin
	Object Coin("coin.png", 275, 150, 0.5, 0.5);

	//create back of coin
	Object PokeCoin("Pokecoin.png", 275, 150, 1, 1);

	// create text for coin flip
	sf::Text Flip("We will flip a coin to see who goes first.\n              The Yugioh coin is you.\n          The Pokemon coin is the bot.", regular);
	Flip.setCharacterSize(35);
	Flip.setStyle(sf::Text::Bold);
	Flip.setFillColor(sf::Color::White);
	Flip.setPosition(130, 350);
	Flip.setLineSpacing(1.3);

	//DUEL
	sf::Text Duel("Welcome to the\n      BATTLE!", yugioh);
	Duel.setCharacterSize(100);
	Duel.setStyle(sf::Text::Bold);
	Duel.setFillColor(sf::Color::Red);
	Duel.setPosition(120, 30);

	//Player 1 goes first
	sf::Text First("You're going\n    first", regular);
	First.setCharacterSize(150);
	First.setStyle(sf::Text::Bold);
	First.setFillColor(sf::Color::Red);
	First.setPosition(110, 80);

	//Player 2 goes first
	sf::Text Second(" The bot is\ngoing first", regular);
	Second.setCharacterSize(150);
	Second.setStyle(sf::Text::Bold);
	Second.setFillColor(sf::Color::Red);
	Second.setPosition(110, 80);

	window.clear();
	window.draw(background);
	window.draw(Duel);
	window.draw(Flip);
	window.display();
	delayScreen(5);

	//flip coin
	firstPlayer = rand() % 2 + 1;
	for (int i = 0; i < 10; i++) {
		window.clear();
		window.draw(background);
		Coin.drawObject(window);
		window.display();
		delayScreen(.2);
		window.clear();
		window.draw(background);
		PokeCoin.drawObject(window);
		window.display();
		delayScreen(.2);
		window.clear();
	}
	if (firstPlayer == 0) {
		window.draw(background);
		Coin.drawObject(window);
		window.display();
		delayScreen(.8);
		window.clear();
		window.draw(background);
		window.draw(Second);
	}
	else {
		window.draw(background);
		PokeCoin.drawObject(window);
		window.display();
		delayScreen(.8);
		window.clear();
		window.draw(background);
		window.draw(Second);
	}
	window.display();
	delayScreen(2);
	window.clear();
	do {
		//draw
		while (player[0].hand.size() != 5 && player[0].getDeckSize() != 0) {
			player[0].drawCard();
		}
		while (player[1].hand.size() != 5 && player[1].getDeckSize() != 0) {
			player[1].drawCard();
		}
		//dislpay
		player[0].atkQueueActivation = 0;
		player[0].defQueueActivation = 0;
		player[1].atkQueueActivation = 0;
		player[1].defQueueActivation = 0;

		if (firstPlayer == 0) {//player goes first
			//Monster setting phase
			playerSetPhase();
			compSetPhase();
			//Monster battling phase
			playerBattlePhase();
			compBattlePhase();
		}
		else if (firstPlayer == 1) {//computer goes first
			//Monster setting phase
			compSetPhase();
			playerSetPhase();

			//Monster battling phase
			compBattlePhase();
			playerBattlePhase();
		}
		//damage calculation

		damageCalculation();


	} while (winnerCheck() == 0);
	int winner = winnerCheck();
	if (winner == 1) {
	}
	else if (winner == 2) {
	}
	window.close();
}


int Game::winnerCheck(void) {
	int winner = 0;
	if (player[1].getLife() == 0) {
		winner = 1;
	}
	else if (player[0].getLife() == 0) {
		winner = 2;
	}
	else if (player[0].getDeckSize() == 0 || player[1].getDeckSize() == 0) {
		winner = 3; //game is a draw if either player has no cards in their deck.
	}
	else {
		winner = 0;
	}
	return winner;
}


void Game::playerSetPhase() {
	Card temp;
	int selection;
	//render window
	sf::RenderWindow window2(sf::VideoMode(800, 600), "Yugioh");
	window2.setFramerateLimit(30);
	sf::Event event;

	//Create a background
	sf::RectangleShape background(sf::Vector2f(800, 800));
	background.setFillColor(sf::Color::Black);
	background.setPosition(0, 0);

	//Create Regular Font 
	sf::Font regular;
	regular.loadFromFile("Bebas-Regular.ttf");

	//Choose card for attacking
	sf::Text Choose("Choose A Card For Attacking(1-5):", regular);
	Choose.setCharacterSize(50);
	Choose.setStyle(sf::Text::Bold);
	Choose.setFillColor(sf::Color::Red);
	Choose.setPosition(110, 100);
	Choose.setLineSpacing(1.3);


	string player1stats = "Player1 Health: " + to_string(player[0].getLife());
	string player2stats = "Player2 Health: " + to_string(player[1].getLife());

	// Player stats
	sf::Text Stats("   " + player1stats + "            " + player2stats, regular);
	Stats.setCharacterSize(40);
	Stats.setStyle(sf::Text::Bold);
	Stats.setFillColor(sf::Color::White);
	Stats.setPosition(0, 0);
	Stats.setLineSpacing(1.3);

	//Create card
	float positionx= 10, positiony= 330; 
	player[0].hand.card(0, temp);
	Object cardObject(temp.getName()+".png", positionx, positiony);
	cardObject.setDimensions((float)150, (float)225);

	int handSize = player[0].hand.size();
	selection = 0;

	window2.clear();
	window2.draw(background);
	window2.draw(Choose);
	window2.draw(Stats);
	cardObject.drawObject(window2);
	for (int i = 1; i < 5; i++) {
		positionx += 160;
		player[0].hand.card(i, temp);
		cardObject.setString(temp.getName() + ".png");
		cardObject.setObjectPosition(positionx, positiony);
		cardObject.setDimensions((float)150, (float)225);
		cardObject.drawObject(window2);
	}
	window2.display();
	while (window2.isOpen()) {
		while ((window2.pollEvent(event))) {
			if (event.type == sf::Event::Closed) {
				window2.close();
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))) {
				selection = 0;
				window2.close();
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))) {
				selection = 1;
				window2.close();
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))) {
				selection = 2;
				window2.close();
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))) {
				selection = 3;
				window2.close();
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))) {
				selection = 4;
				window2.close();
			}
		}
		
	}
	player[0].hand.removeCard(selection-1+1, temp);
	player[0].attackQueue.enqueue(temp);

	//render window
	sf::RenderWindow window3(sf::VideoMode(800, 600), "Yugioh");
	window3.setFramerateLimit(30);
	sf::Event event1;
	handSize--;
	Choose.setString("Choose A Card For Defending:");
	selection = 0;
	positionx = 10;
	window3.clear();
	window3.draw(background);
	window3.draw(Choose);
	window3.draw(Stats);
	cardObject.drawObject(window3);
	for (int i = 0; i < 4; i++) {
		player[0].hand.card(i, temp);
		cardObject.setString(temp.getName() + ".png");
		cardObject.setObjectPosition(positionx, positiony);
		cardObject.setDimensions((float)200, (float)300);
		cardObject.drawObject(window3);
		positionx += 210;
	}
	window3.display();
	while (window3.isOpen()) {
		while ((window3.pollEvent(event1))) {
			if (event1.type == sf::Event::Closed) {
				window3.close();
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))) {
				selection = 0;
				window3.close();
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))) {
				selection = 1;
				window3.close();
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))) {
				selection = 2;
				window3.close();
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))) {
				selection = 3;
				window3.close();
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))) {
				selection = 4;
				window3.close();
			}
		}

	}

	player[0].hand.removeCard(selection-1, temp);
	player[0].defenseQueue.enqueue(temp);
}

void Game::compSetPhase() {
	YCard temp;
	int randPick;
	//attack Queue
//	display();
	randPick = rand() % player[1].hand.size();
	player[1].hand.removeCard(randPick, temp);
	player[1].attackQueue.enqueue(temp);

	//cout << "Computer has added " << temp.getName() << " to the Attack Queue\n";

	randPick = rand() % player[1].hand.size();
	player[1].hand.removeCard(randPick, temp);
	player[1].defenseQueue.enqueue(temp);

	//cout << "Computer has added " << temp.getName() << " to the Defense Queue\n";

	//EnterKey();
}


void Game::playerBattlePhase() {
	int selection = 0;
	do {
		selection = 0;
		display();
		cout << "Battle Phase:\n";
		cout << "Which Queue would you like to activate?\n";
		cout << "   1.Attack Queue\n";
		cout << "   2.Defense Queue\n";
		cout << "Make a selection: ";
		cin >> selection;
		flushCin();
		if (selection != 1 && selection != 2) {
			selection = INVALID;
			cout << "\nPlease make a valid selection.\n";
			EnterKey();
		}
	} while (selection == INVALID);
	
	cout << "Player activates the " << ((selection == 1) ? "Attack Queue" : "Defense Queue" )<< endl;
	if (selection == 1) {
		player[0].atkQueueActivation = 1;
		player[0].defQueueActivation = 0;
	}
	else {
		player[0].atkQueueActivation = 0;
		player[0].defQueueActivation = 1;
	}
	EnterKey();

}

void Game::compBattlePhase() {
	YCard temp;
	int randPick;
	//attack Queue
	randPick = rand() % 2;
	if (randPick == 1) {
		player[1].atkQueueActivation = 1;
		player[1].defQueueActivation = 0;
	}
	else {
		player[1].atkQueueActivation = 0;
		player[1].defQueueActivation = 1;
	}
	//cout << " Computer activates the " << ((randPick == 1) ? "Attack Queue" : "Defense Queue") << endl;

	//EnterKey();
}

//hubba bubba

void Game::damageCalculation() {
	//cout << "Calculation:\n\n";
	//display();
	//cout << "\n";
	YCard monster[2];
	int playerBattlePoints;
	int compBattlePoints;

	//player activation
	if (player[0].atkQueueActivation == 1) {
		player[0].attackQueue.dequeue(monster[0]);
		playerBattlePoints = monster[0].getAtk() + monster[0].getBoost();
		//cout << "Player: " << monster[0].getName() << " has been activated to Attack with " << playerBattlePoints << "ATK"<<endl;
	}
	else {
		player[0].defenseQueue.dequeue(monster[0]);
		playerBattlePoints = monster[0].getDef();
		//cout << "Player: " << monster[0].getName() << " has been activated to Defend with " << playerBattlePoints <<" DEF" <<endl ;
	}

	//computer activation
	if (player[1].atkQueueActivation == 1) {
		player[1].attackQueue.dequeue(monster[1]);
		compBattlePoints = monster[1].getAtk() + monster[1].getBoost();
		//cout << "Computer: " << monster[1].getName() << " has been activated to Attack with " << compBattlePoints << "ATK" << endl;
	}
	else {
		player[0].defenseQueue.dequeue(monster[1]);
		compBattlePoints = monster[1].getDef();
		//cout << "Computer: " << monster[1].getName() << " has been activated to Defend with " << compBattlePoints << " DEF" << endl;
	}

	int difference = 0;

	//4 cases
	if (player[0].atkQueueActivation != 0 && player[1].atkQueueActivation != 0) {//ATK-ATK, ATK-DEF, DEF-ATK
		
		difference = playerBattlePoints - compBattlePoints;
		//cout << playerBattlePoints << "(Player) - " << compBattlePoints << "(enemy) = " << difference << endl;
		//calculation
		//cout << "\n";
		if (difference == 0) {
			//cout << "No Player takes damage.\n";
		}
		else if (difference < 0) {
			//cout << "Player has taken " << abs(difference) << " damage!\n";
			player[0].subLife(abs(difference));
		}
		else {
			//cout << "Computer has taken " << abs(difference) << "damage!\n";
			player[1].subLife(abs(difference));
		}
	}
	else {//DEF-DEF
		difference = playerBattlePoints - compBattlePoints;
		//cout << "Both players have activated the defense queue." << endl;
		//cout << "\n";
		//cout << "No Player takes damage.\n";
	}
	//cout << "\n";
	//EnterKey();
}