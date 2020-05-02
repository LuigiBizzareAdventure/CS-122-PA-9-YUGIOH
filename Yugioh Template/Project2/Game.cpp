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
	windowPtr->clear();
	windowPtr->setFramerateLimit(30);
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

	windowPtr->clear();
	windowPtr->draw(background);
	windowPtr->draw(Duel);
	windowPtr->draw(Flip);
	windowPtr->display();
	delayScreen(5);

	//flip coin
	firstPlayer = rand() % 2;
	for (int i = 0; i < 10; i++) {
		windowPtr->clear();
		windowPtr->draw(background);
		Coin.drawObject(windowPtr);
		windowPtr->display();
		delayScreen(.2);
		windowPtr->clear();
		windowPtr->draw(background);
		PokeCoin.drawObject(windowPtr);
		windowPtr->display();
		delayScreen(.2);
		windowPtr->clear();
	}
	if (firstPlayer == 0) {
		windowPtr->draw(background);
		Coin.drawObject(windowPtr);
		windowPtr->display();
		delayScreen(.8);
		windowPtr->clear();
		windowPtr->draw(background);
		windowPtr->draw(First);
	}
	else {
		windowPtr->draw(background);
		PokeCoin.drawObject(windowPtr);
		windowPtr->display();
		delayScreen(.8);
		windowPtr->clear();
		windowPtr->draw(background);
		windowPtr->draw(Second);
	}
	windowPtr->display();
	delayScreen(2);
	windowPtr->clear();
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
	//winning messages
	int winner = winnerCheck();


	//Create Yugioh Font 
	sf::Font yugioh;
	yugioh.loadFromFile("squealer embossed.ttf");

	//Create Regular Font 
	sf::Font regular;
	regular.loadFromFile("Bebas-Regular.ttf");

	//first player win text
	sf::Text winner1("Congratulations You have won", yugioh);
	winner1.setCharacterSize(65);
	winner1.setStyle(sf::Text::Bold);
	winner1.setFillColor(sf::Color::Black);
	winner1.setPosition(125, 20);
	winner1.setOutlineThickness(1.5);
	winner1.setOutlineColor(sf::Color::Color(150, 150, 150, 255));

	//second player win text
	sf::Text winner2("The Computer has won!", yugioh);
	winner2.setCharacterSize(65);
	winner2.setStyle(sf::Text::Bold);
	winner2.setFillColor(sf::Color::Black);
	winner2.setPosition(125, 20);
	winner2.setOutlineThickness(1.5);
	winner2.setOutlineColor(sf::Color::Color(150, 150, 150, 255));

	////Tie player win text
	sf::Text tieText("The Computer has won!", yugioh);
	tieText.setCharacterSize(65);
	tieText.setStyle(sf::Text::Bold);
	tieText.setFillColor(sf::Color::Black);
	tieText.setPosition(125, 20);
	tieText.setOutlineThickness(1.5);
	tieText.setOutlineColor(sf::Color::Color(150, 150, 150, 255));

	//Create a background
	sf::RectangleShape background(sf::Vector2f(800, 800));
	background.setFillColor(sf::Color::Black);
	background.setPosition(0, 0);

	if (winner == 1) {//player 1 wins




	}
	else if (winner == 2) {//playeer 2 wins
	}
	else {//tie

	}
	windowPtr->close();
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
	YCard temp;
	int selection;
	//render window
	windowPtr->setFramerateLimit(30);
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
	float positionx = 10, positiony = 330; 
	player[0].hand.card(0, temp);
	selection = -1;
	int handSize = player[0].hand.size();

	while (windowPtr->isOpen() && selection == -1) {
		while ((windowPtr->pollEvent(event))) {
			if (event.type == sf::Event::Closed) {
				windowPtr->close();
			}
		}
		positionx = 10, positiony = 330;
		selection = -1;
		windowPtr->clear();
		windowPtr->draw(background);
		windowPtr->draw(Choose);
		windowPtr->draw(Stats);
		sf::Sprite cardSprite;
		sf::Texture texture;
		for (int i = 0; i < 5; i++) {
			player[0].hand.card(i, temp);
			texture.loadFromFile(temp.getFrontPath());
			cardSprite.setTexture(texture);
			cardSprite.setPosition(positionx, positiony);
			float x = 150;
			float y = 225;
			sf::Vector2f targetSize(x, y);
			cardSprite.setScale(targetSize.x / cardSprite.getLocalBounds().width, targetSize.y / cardSprite.getLocalBounds().height);
			windowPtr->draw(cardSprite);
			positionx += 160;

		}
		windowPtr->display();
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))) {
			selection = 0;
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))) {
			selection = 1;
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))) {
			selection = 2;
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))) {
			selection = 3;
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))) {
			selection = 4;
		}
	}
		
	player[0].hand.removeCard(selection, temp);
	player[0].attackQueue.enqueue(temp);

	//render window
	sf::Event event1;
	selection = -1;
	handSize--;
	Choose.setString("Choose A Card For Defending:");
	positionx = 10;
	while (windowPtr->isOpen() && selection == -1) {
		while ((windowPtr->pollEvent(event1))) {
			if (event1.type == sf::Event::Closed) {
				windowPtr->close();
			}
			positionx = 10;
			selection = -1;
			windowPtr->clear();
			windowPtr->draw(background);
			windowPtr->draw(Choose);
			windowPtr->draw(Stats);
			sf::Sprite cardSprite;
			sf::Texture texture;
			for (int i = 0; i < 4; i++) {
				player[0].hand.card(i, temp);
				texture.loadFromFile(temp.getFrontPath());
				cardSprite.setTexture(texture);
				cardSprite.setPosition(positionx, positiony);
				float x = 150;
				float y = 225;
				sf::Vector2f targetSize(x, y);
				cardSprite.setScale(targetSize.x / cardSprite.getLocalBounds().width, targetSize.y / cardSprite.getLocalBounds().height);
				windowPtr->draw(cardSprite);
				positionx += 160;

			}
			windowPtr->display();
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))) {
				selection = 0;
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))) {
				selection = 1;
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))) {
				selection = 2;
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))) {
				selection = 3;
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))) {
				selection = 4;
			}
		}

	}

	player[0].hand.removeCard(selection, temp);
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
	
	YCard temp1;
	YCard temp2;

	player[0].attackQueue.peek(temp1);
	player[0].defenseQueue.peek(temp2);



	windowPtr->create(sf::VideoMode(800, 600), "Battle Phase!");
	windowPtr->setFramerateLimit(30);
	sf::Event event;

	//Create a background
	sf::RectangleShape background(sf::Vector2f(800, 800));
	background.setFillColor(sf::Color::Black);
	background.setPosition(0, 0);

	//Create Regular Font 
	sf::Font regular;
	regular.loadFromFile("Bebas-Regular.ttf");

	//Text for the Screen
	sf::Text Battle("Battle Phase! Select which queue you would like to activate.", regular);
	Battle.setCharacterSize(25);
	Battle.setStyle(sf::Text::Bold);
	Battle.setFillColor(sf::Color::Red);
	Battle.setPosition(50, 50);
	Battle.setLineSpacing(1.1);


	//Shows attack value and defense value of hidden cards

	sf::Text Attack("1)ATK: " + temp1.getAtk(), regular);
	Attack.setCharacterSize(25);
	Attack.setStyle(sf::Text::Bold);
	Attack.setFillColor(sf::Color::Red);
	Attack.setPosition(100, 250);
	Attack.setLineSpacing(1.1);

	sf::Text Defend("2)DEF: " + temp2.getDef(), regular);
	Defend.setCharacterSize(25);
	Defend.setStyle(sf::Text::Bold);
	Defend.setFillColor(sf::Color::Red);
	Defend.setPosition(500, 250);
	Defend.setLineSpacing(1.1);






	//Loading up the sprites

	Object cardSprite2("YuGiOh Card Back.png", 500, 300);
	cardSprite2.setDimensions((float)150, (float)225);

	Object cardSprite1("YuGiOh Card Back.png", 100, 300);
	cardSprite1.setDimensions((float)150, (float)225);
	

	
	//Printing to the screen
	
	
	windowPtr->clear();
	windowPtr->draw(background);
	windowPtr->draw(Battle);
	windowPtr->draw(Attack);
	windowPtr->draw(Defend);
	cardSprite1.drawObject(windowPtr);
	cardSprite2.drawObject(windowPtr);



	windowPtr->display();

	int selection = 0;					//Int selection moved outside of while looop


	while (windowPtr->isOpen()) {
		while (windowPtr->pollEvent(event)) {



			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))) {
				selection = 1;
				windowPtr->close();
			}
																																					//While loop here used to determine Attack or Defence by Selection int

			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))) {
				selection = 2;
				windowPtr->close();
			}




		}
	}






	//Half of this has been comment-ed out as it wasn't needed anymore. Still works though to look and make sure the right cards show and attack values show.
	
	do {
		//selection = 0;
		display();
		cout << "Battle Phase:\n";
		cout << "Which Queue would you like to activate?\n";
		cout << "   1.Attack Queue\n";
		cout << "   2.Defense Queue\n";
		cout << "Make a selection: ";
		//cin >> selection;
		flushCin();
	/*	if (selection != 1 && selection != 2) {
			selection = INVALID;
			cout << "\nPlease make a valid selection.\n";
			EnterKey();
		}*/
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



	//Creating text to continue, show attack value, and show defense value.

	sf::Text Continue("Press Enter to Continue", regular);
	Continue.setCharacterSize(30);
	Continue.setStyle(sf::Text::Bold);
	Continue.setFillColor(sf::Color::Red);
	Continue.setPosition(350, 250);
	Continue.setLineSpacing(1.1);
	



	
	sf::Text Attacker("Attack Queue Activated!\nATK:" + temp1.getAtk(), regular);
	Attacker.setCharacterSize(30);
	Attacker.setStyle(sf::Text::Bold);
	Attacker.setFillColor(sf::Color::Red);
	Attacker.setPosition(350, 150);
	Attacker.setLineSpacing(1.1);

	sf::Text Defender("Defence Queue Activated!\nDEF:" + temp2.getDef(), regular);
	Defender.setCharacterSize(30);
	Defender.setStyle(sf::Text::Bold);
	Defender.setFillColor(sf::Color::Red);
	Defender.setPosition(350, 150);
	Defender.setLineSpacing(1.1);

	windowPtr->create(sf::VideoMode(800, 600), "Chosen Card!");							//creates another screen since I closed the last one.


	if (player[0].atkQueueActivation = 1) {

		Object cardSprite3(temp1.getName() + ".png", 100, 150);
		cardSprite3.setDimensions((float)225, (float)337.5);

		cardSprite3.drawObject(windowPtr);										//Checks whether attack or defense is used, then prints out the card, and its atk/def value.
		windowPtr->draw(Attacker);
		windowPtr->draw(Continue);
		windowPtr->display();

	}
	else {

		Object cardSprite3(temp2.getName() + ".png", 100, 150);
		cardSprite3.setDimensions((float)225, (float)337.5);
		
		cardSprite3.drawObject(windowPtr);
		windowPtr->draw(Defender);
		windowPtr->draw(Continue);
		windowPtr->display();
		



	}












	
	while (windowPtr->isOpen()) {
		while (windowPtr->pollEvent(event)) {

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))) {
				windowPtr->close();
			}

		}
	}

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