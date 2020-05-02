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
	//temp.reset();
	cout << "Next in Def Queue: " << ((player[1].defenseQueue.peek(temp)) ? temp.getName() : "None ") << " "<< temp.getDef() << "DEF" << endl;

	//temp.reset();
	cout << "---------------------------------------------------------------------\n";
	cout << "Player Side\n";
	if (player[0].atkQueueActivation) {
		cout << "Attack Queue is Activated.\n";
	}
	if (player[0].defQueueActivation) {
		cout << "Defense Queue is Activated.\n";
	}
	cout << "LifePoints: " << player[0].getLife() << endl;
	//temp.reset();
	cout << "Next in Atk Queue: " << ((player[0].attackQueue.peek(temp)) ? temp.getName() : "None") <<" " <<temp.getAtk() << "ATK + " << temp.getBoost() << "(" << temp.getTypeName() << ")" << endl;
	//temp.reset();
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
	sf::Text First("You're going\n      first", regular);
	First.setCharacterSize(150);
	First.setStyle(sf::Text::Bold);
	First.setFillColor(sf::Color::Red);
	First.setPosition(80, 80);

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
	

	//first player win text
	sf::Text winner1("Congratulations!\n   You have won!", yugioh);
	winner1.setCharacterSize(120);
	winner1.setStyle(sf::Text::Bold);
	winner1.setFillColor(sf::Color::Red);
	winner1.setPosition(0, 100);


	//second player win text
	sf::Text winner2("The Computer\n    has won!", yugioh);
	winner2.setCharacterSize(120);
	winner2.setStyle(sf::Text::Bold);
	winner2.setFillColor(sf::Color::Red);
	winner2.setPosition(75, 100);

	////Tie player win text
	sf::Text tieText("You TIED!", yugioh);
	tieText.setCharacterSize(180);
	tieText.setStyle(sf::Text::Bold);
	tieText.setFillColor(sf::Color::Red);
	tieText.setPosition(80, 150);

	windowPtr->clear();
	windowPtr->draw(background);

	if (winner == 1) {//player 1 wins
		windowPtr->draw(winner1);
	}
	else if (winner == 2) {//playeer 2 wins
		windowPtr->draw(winner2);
	}
	else {//tie
		windowPtr->draw(tieText);
	}
	windowPtr->display();
	delayScreen(2);
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
	delayScreen(.5);

	//defense
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
		}

	}
	delayScreen(.5);

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
	string bug;
	string attack = "\nATK:" + to_string(temp1.getAtk()) + "\nEnter 1 To Select Attack Queue";
	string defend = "\nDEF:" + to_string(temp2.getDef()) + "\nEnter 2 To Select Defend Queue";

	

	sf::Text Attack(temp1.getName() + attack, regular);
	bug = "1)ATK: " + temp1.getAtk();
	cout << bug << endl;
	Attack.setCharacterSize(25);
	Attack.setStyle(sf::Text::Bold);
	Attack.setFillColor(sf::Color::Red);
	Attack.setPosition(50, 190);
	Attack.setLineSpacing(1.1);

	sf::Text Defend(temp2.getName() + defend, regular);
	bug = "2)DEF: " + temp2.getDef();
	cout << bug << endl;
	Defend.setCharacterSize(25);
	Defend.setStyle(sf::Text::Bold);
	Defend.setFillColor(sf::Color::Red);
	Defend.setPosition(450, 190);
	Defend.setLineSpacing(1.1);






	//Loading up the sprites

	Object cardSprite1(temp1.getFrontPath(), 50, 300);
	cardSprite1.setDimensions((float)150, (float)225);

	Object cardSprite2(temp2.getFrontPath(), 450, 300);
	cardSprite2.setDimensions((float)150, (float)225);
	

	
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
	//display();
	//do {
	//	//selection = 0;
	//	
	//	/*cout << "Battle Phase:\n";
	//	cout << "Which Queue would you like to activate?\n";
	//	cout << "   1.Attack Queue\n";
	//	cout << "   2.Defense Queue\n";
	//	cout << "Make a selection: ";*/
	//	//cin >> selection;
	//	flushCin();
	///*	if (selection != 1 && selection != 2) {
	//		selection = INVALID;
	//		cout << "\nPlease make a valid selection.\n";
	//		EnterKey();
	//	}*/
	//} while (selection == INVALID);
	
	//cout << "Player activates the " << ((selection == 1) ? "Attack Queue" : "Defense Queue" )<< endl;
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
	Continue.setPosition(350, 300);
	Continue.setLineSpacing(1.1);
	



	
	sf::Text Attacker("Attack Queue Activated!\nATK:" + to_string(temp1.getAtk()), regular);
	Attacker.setCharacterSize(30);
	Attacker.setStyle(sf::Text::Bold);
	Attacker.setFillColor(sf::Color::Red);
	Attacker.setPosition(350, 150);
	Attacker.setLineSpacing(1.1);

	sf::Text Defender("Defence Queue Activated!\nDEF:" + to_string(temp2.getDef()), regular);
	Defender.setCharacterSize(30);
	Defender.setStyle(sf::Text::Bold);
	Defender.setFillColor(sf::Color::Red);
	Defender.setPosition(350, 150);
	Defender.setLineSpacing(1.1);

	windowPtr->create(sf::VideoMode(800, 600), "Chosen Card!");							//creates another screen since I closed the last one.


	if (player[0].atkQueueActivation == 1) {

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
	selection = 0;
	while (windowPtr->isOpen() && selection == 0) {
		while ((windowPtr->pollEvent(event))) {
			if (event.type == sf::Event::Closed) {
				windowPtr->close();
			}
		}
		selection = 0;

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))) {
				selection = 1;
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

	//render window
	windowPtr->setFramerateLimit(30);

	//Create a background
	sf::RectangleShape background(sf::Vector2f(800, 800));
	background.setFillColor(sf::Color::Black);
	background.setPosition(0, 0);

	windowPtr->draw(background);

	//Create Regular Font 
	sf::Font regular;
	regular.loadFromFile("Bebas-Regular.ttf");

	string player1stats = "Player1 Health: " + to_string(player[0].getLife());
	string player2stats = "Player2 Health: " + to_string(player[1].getLife());

	// Player stats
	sf::Text Stats("   " + player1stats + "            " + player2stats, regular);
	Stats.setCharacterSize(40);
	Stats.setStyle(sf::Text::Bold);
	Stats.setFillColor(sf::Color::White);
	Stats.setPosition(0, 0);
	Stats.setLineSpacing(1.3);

	//Battle text
	sf::Text Fight("FIGHT", regular);
	Fight.setCharacterSize(40);
	Fight.setStyle(sf::Text::Bold);
	Fight.setFillColor(sf::Color::Red);
	Fight.setPosition(0, 0);
	Fight.setLineSpacing(1.3);

	//Attack Mode Text
	sf::Text Attack("ATTACK", regular);
	Attack.setCharacterSize(40);
	Attack.setFillColor(sf::Color::Red);
	Attack.setPosition(0, 0);
	Attack.setLineSpacing(1.3);

	//Defense Mode Text
	sf::Text Defense("DEFENSE", regular);
	Defense.setCharacterSize(40);
	Defense.setFillColor(sf::Color::Red);
	Defense.setPosition(0, 0);
	Defense.setLineSpacing(1.3);

	//Attack Value
	sf::Text ATKVAL("ATK: ", regular);
	ATKVAL.setCharacterSize(40);
	ATKVAL.setFillColor(sf::Color::Red);
	ATKVAL.setPosition(0, 0);
	ATKVAL.setLineSpacing(1.3);

	//Defense Value
	sf::Text DEFVAL("DEF: ", regular);
	DEFVAL.setCharacterSize(40);
	DEFVAL.setFillColor(sf::Color::Red);
	DEFVAL.setPosition(0, 0);
	DEFVAL.setLineSpacing(1.3);

	//Create cards
	float player_positionx = 50, player_positiony = 200;
	float comp_positionx = 550, comp_positiony = 200;

	

	//player activation
	if (player[0].atkQueueActivation == 1) {
		player[0].attackQueue.dequeue(monster[0]);
		playerBattlePoints = monster[0].getAtk() + monster[0].getBoost();
		//cout << "Player: " << monster[0].getName() << " has been activated to Attack with " << playerBattlePoints << "ATK"<<endl;
		Attack.setPosition(50, 150);
		DEFVAL.setPosition(50, 500);
		DEFVAL.setString("ATK: " + playerBattlePoints);
		windowPtr->draw(Attack);
		windowPtr->draw(ATKVAL);
	}
	else {
		player[0].defenseQueue.dequeue(monster[0]);
		playerBattlePoints = monster[0].getDef();
		//cout << "Player: " << monster[0].getName() << " has been activated to Defend with " << playerBattlePoints <<" DEF" <<endl ;
		Defense.setPosition(50, 150);
		DEFVAL.setPosition(50, 500);
		DEFVAL.setString("DEF: " + playerBattlePoints);
		windowPtr->draw(Defense);
		windowPtr->draw(DEFVAL);

	}

	//computer activation
	if (player[1].atkQueueActivation == 1) {
		player[1].attackQueue.dequeue(monster[1]);
		compBattlePoints = monster[1].getAtk() + monster[1].getBoost();
		//cout << "Computer: " << monster[1].getName() << " has been activated to Attack with " << compBattlePoints << "ATK" << endl;
		Attack.setPosition(550, 150);
		ATKVAL.setPosition(550, 500);
		ATKVAL.setString("ATK: " + compBattlePoints);
		windowPtr->draw(Attack);
		windowPtr->draw(ATKVAL);
	}
	else {
		player[0].defenseQueue.dequeue(monster[1]);
		compBattlePoints = monster[1].getDef();
		//cout << "Computer: " << monster[1].getName() << " has been activated to Defend with " << compBattlePoints << " DEF" << endl;
		Defense.setPosition(550, 150);
		DEFVAL.setPosition(550, 500);
		DEFVAL.setString("DEF: " + compBattlePoints);
		windowPtr->draw(Defense);
		windowPtr->draw(DEFVAL);
	}

	//Draw Player Card
	sf::Sprite cardSprite1;
	sf::Texture texture1;
	texture1.loadFromFile(monster[0].getFrontPath());
	cardSprite1.setTexture(texture1);
	cardSprite1.setPosition(player_positionx, player_positiony);
	float x = 150;
	float y = 225;
	sf::Vector2f targetSize(x, y);
	cardSprite1.setScale(targetSize.x / cardSprite1.getLocalBounds().width, targetSize.y / cardSprite1.getLocalBounds().height);
	windowPtr->draw(cardSprite1);

	//Draw Computer Card
	sf::Sprite cardSprite2;
	sf::Texture texture2;
	texture2.loadFromFile(monster[1].getFrontPath());
	cardSprite2.setTexture(texture2);
	cardSprite2.setPosition(comp_positionx, comp_positiony);
	x = 150;
	y = 225;
	cardSprite1.setScale(targetSize.x / cardSprite2.getLocalBounds().width, targetSize.y / cardSprite2.getLocalBounds().height);
	windowPtr->draw(cardSprite2);

	windowPtr->display();

	delayScreen(2);


	int fightx = 0;
	int fighty = 0;
	int fightCharSize = 20;



	//display battle intro
	int intro = 0;
	while (intro < 120) {

		windowPtr->draw(background);

		cardSprite1.setPosition(player_positionx, player_positiony);
		windowPtr->draw(cardSprite1);

		cardSprite2.setPosition(comp_positionx, comp_positiony);
		windowPtr->draw(cardSprite2);


		if (player[0].atkQueueActivation == 1) {
			playerBattlePoints = monster[0].getAtk() + monster[0].getBoost();
			Attack.setPosition(50, 150);
			DEFVAL.setPosition(50, 500);
			//DEFVAL.setString("ATK: " + playerBattlePoints);
			windowPtr->draw(Attack);
			windowPtr->draw(ATKVAL);
		}
		else {
			playerBattlePoints = monster[0].getDef();
			Defense.setPosition(50, 150);
			DEFVAL.setPosition(50, 500);
			//DEFVAL.setString("DEF: " + playerBattlePoints);
			windowPtr->draw(Defense);
			windowPtr->draw(DEFVAL);

		}

		if (player[1].atkQueueActivation == 1) {
			compBattlePoints = monster[1].getAtk() + monster[1].getBoost();
			Attack.setPosition(550, 150);
			ATKVAL.setPosition(550, 500);
			//ATKVAL.setString("ATK: " + compBattlePoints);
			windowPtr->draw(Attack);
			windowPtr->draw(ATKVAL);
		}
		else {
			compBattlePoints = monster[1].getDef();
			Defense.setPosition(550, 150);
			DEFVAL.setPosition(550, 500);
			//DEFVAL.setString("DEF: " + compBattlePoints);
			windowPtr->draw(Defense);
			windowPtr->draw(DEFVAL);
		}

		Fight.setPosition((float)fightx, (float)fighty);
		Fight.setCharacterSize(fightCharSize);

		windowPtr->draw(Fight);

		fightx += 2;
		fighty += 2;
		fightCharSize += 1;

		intro++;

		windowPtr->display();

	}




	//battle sequence
	int battle1 = 0;
	while (battle1 < 30) {

		windowPtr->draw(background);
		
		cardSprite1.setPosition(player_positionx, player_positiony);
		windowPtr->draw(cardSprite1);

		cardSprite2.setPosition(comp_positionx, comp_positiony);
		windowPtr->draw(cardSprite2);

		if (player[0].atkQueueActivation == 1) {
			playerBattlePoints = monster[0].getAtk() + monster[0].getBoost();
			Attack.setPosition(50, 150);
			ATKVAL.setPosition(50, 500);
			//ATKVAL.setString("ATK: " + playerBattlePoints);
			windowPtr->draw(Attack);
			windowPtr->draw(ATKVAL);
		}
		else {
			playerBattlePoints = monster[0].getDef();
			Defense.setPosition(50,150);
			DEFVAL.setPosition(50, 500);
			//DEFVAL.setString("DEF: " + playerBattlePoints);
			windowPtr->draw(Defense);
			windowPtr->draw(DEFVAL);

		}

		if (player[1].atkQueueActivation == 1) {
			compBattlePoints = monster[1].getAtk() + monster[1].getBoost();
			Attack.setPosition(550,150);
			ATKVAL.setPosition(550, 500);
			//ATKVAL.setString("ATK: " + compBattlePoints);
			windowPtr->draw(Attack);
			windowPtr->draw(ATKVAL);
		}
		else {
			compBattlePoints = monster[1].getDef();
			Defense.setPosition(550, 150);
			DEFVAL.setPosition(550, 500);
			//DEFVAL.setString("DEF: " + compBattlePoints);
			windowPtr->draw(Defense);
			windowPtr->draw(DEFVAL);
		}

		comp_positionx += 1;
		player_positionx -= 1;

		battle1 += 1;

		windowPtr->display();

	}

	battle1 = 0;
	while (battle1 < 20) {

		windowPtr->draw(background);

		cardSprite1.setPosition(player_positionx, player_positiony);
		windowPtr->draw(cardSprite1);

		cardSprite2.setPosition(comp_positionx, comp_positiony);
		windowPtr->draw(cardSprite2);

		if (player[0].atkQueueActivation == 1) {
			playerBattlePoints = monster[0].getAtk() + monster[0].getBoost();
			Attack.setPosition(50, 150);
			ATKVAL.setPosition(50, 500);
			//ATKVAL.setString("ATK: " + playerBattlePoints);
			windowPtr->draw(Attack);
			windowPtr->draw(ATKVAL);
		}
		else {
			playerBattlePoints = monster[0].getDef();
			Defense.setPosition(50, 150);
			DEFVAL.setPosition(50, 500);
			//DEFVAL.setString("DEF: " + playerBattlePoints);
			windowPtr->draw(Defense);
			windowPtr->draw(DEFVAL);

		}

		if (player[1].atkQueueActivation == 1) {
			compBattlePoints = monster[1].getAtk() + monster[1].getBoost();
			Attack.setPosition(550, 150);
			ATKVAL.setPosition(550, 500);
			//ATKVAL.setString("ATK: " + compBattlePoints);
			windowPtr->draw(Attack);
			windowPtr->draw(ATKVAL);
		}
		else {
			compBattlePoints = monster[1].getDef();
			Defense.setPosition(550, 150);
			DEFVAL.setPosition(550, 500);
			//DEFVAL.setString("DEF: " + compBattlePoints);
			windowPtr->draw(Defense);
			windowPtr->draw(DEFVAL);
		}

		comp_positionx -= 2;
		player_positionx += 2;

		battle1 += 1;

		windowPtr->display();

	}

	battle1 = 0;
	while (battle1 < 10) {
		background.setFillColor(sf::Color::White);
		windowPtr->draw(background);
		background.setFillColor(sf::Color::Black);
		windowPtr->draw(background);
		battle1 += 1;

		windowPtr->display();

	}

	while (comp_positionx != 550 && player_positionx != 50) {

		windowPtr->draw(background);
 
		windowPtr->draw(background);

		cardSprite1.setPosition(player_positionx, player_positiony);
		windowPtr->draw(cardSprite1);

		cardSprite2.setPosition(comp_positionx, comp_positiony);
		windowPtr->draw(cardSprite2);

		if (player[0].atkQueueActivation == 1) {
			playerBattlePoints = monster[0].getAtk() + monster[0].getBoost();
			Attack.setPosition(50, 150);
			ATKVAL.setPosition(50, 500);
			//ATKVAL.setString("ATK: " + playerBattlePoints);
			windowPtr->draw(Attack);
			windowPtr->draw(ATKVAL);
		}
		else {
			playerBattlePoints = monster[0].getDef();
			Defense.setPosition(50, 150);
			DEFVAL.setPosition(50, 500);
			//DEFVAL.setString("DEF: " + playerBattlePoints);
			windowPtr->draw(Defense);
			windowPtr->draw(DEFVAL);

		}

		if (player[1].atkQueueActivation == 1) {
			compBattlePoints = monster[1].getAtk() + monster[1].getBoost();
			Attack.setPosition(550, 150);
			ATKVAL.setPosition(550, 500);
			//ATKVAL.setString("ATK: " + compBattlePoints);
			windowPtr->draw(Attack);
			windowPtr->draw(ATKVAL);
		}
		else {
			compBattlePoints = monster[1].getDef();
			Defense.setPosition(550, 150);
			DEFVAL.setPosition(550, 500);
			//DEFVAL.setString("DEF: " + compBattlePoints);
			windowPtr->draw(Defense);
			windowPtr->draw(DEFVAL);
		}

		player_positionx -= 1;
		comp_positionx += 1;

		windowPtr->display();

	}
	//End battle sequence


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

	delayScreen(1);

	windowPtr->draw(background);

	player1stats = "Player1 Health: " + to_string(player[0].getLife());
	player2stats = "Player2 Health: " + to_string(player[1].getLife());

	Stats.setString("   " + player1stats + "            " + player2stats);
	windowPtr->draw(Stats);
	windowPtr->draw(cardSprite1);
	windowPtr->draw(cardSprite2);

	if (player[0].atkQueueActivation == 1) {
		playerBattlePoints = monster[0].getAtk() + monster[0].getBoost();
		Attack.setPosition(50, 150);
		ATKVAL.setPosition(50, 500);
		ATKVAL.setString("ATK: " + playerBattlePoints);
		windowPtr->draw(Attack);
		windowPtr->draw(ATKVAL);
	}
	else {
		playerBattlePoints = monster[0].getDef();
		Defense.setPosition(50, 150);
		DEFVAL.setPosition(50, 500);
		DEFVAL.setString("DEF: " + playerBattlePoints);
		windowPtr->draw(Defense);
		windowPtr->draw(DEFVAL);

	}

	if (player[1].atkQueueActivation == 1) {
		compBattlePoints = monster[1].getAtk() + monster[1].getBoost();
		Attack.setPosition(550, 150);
		ATKVAL.setPosition(550, 500);
		ATKVAL.setString("ATK: " + compBattlePoints);
		windowPtr->draw(Attack);
		windowPtr->draw(ATKVAL);
	}
	else {
		compBattlePoints = monster[1].getDef();
		Defense.setPosition(550, 150);
		DEFVAL.setPosition(550, 500);
		DEFVAL.setString("DEF: " + compBattlePoints);
		windowPtr->draw(Defense);
		windowPtr->draw(DEFVAL);
	}

	windowPtr->display();

	delayScreen(5);

	//EnterKey();
}