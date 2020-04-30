#include "Header.h"
#include "MainMenu.h"
#include "Object.h"

#pragma warning(disable : 4996)
int main(void) {

	srand(time(NULL));//generates a seed for random numbers

	MainMenu menu;
	menu.loadTrunk();//loads cards from the csv file
	menu.createPlayers();
	int firstPlayer = 0;

	//render window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Yugioh");
	window.setFramerateLimit(30);
	sf::Event event;

	//Create Yugioh Font 
	sf::Font yugioh;
	yugioh.loadFromFile("squealer embossed.ttf");


	//Create Regular Font 
	sf::Font regular;
	regular.loadFromFile("Bebas-Regular.ttf");

	//Diplay welcome
	sf::Text welcome("Welcome to Yu-gi-oh!", yugioh);
	welcome.setCharacterSize(65);
	welcome.setStyle(sf::Text::Bold);
	welcome.setFillColor(sf::Color::Black);
	welcome.setPosition(125, 20);
	welcome.setOutlineThickness(1.5);
	welcome.setOutlineColor(sf::Color::Color(150,150,150,255));

	//Diplay menu options
	sf::Text text("1. Duel \n2. Exit\n", regular);
	text.setCharacterSize(34);
	//text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Color(10,10,10,255));
	text.setPosition(120, 120);
	text.setLineSpacing(1.3);

	//Create a background
	sf::RectangleShape background(sf::Vector2f(800, 800));
	background.setFillColor(sf::Color::Black);
	background.setPosition(0, 0);

	//create dragon sprite
	Object spriteDragon("BlizzardDragon.png", 300, 380, 0.2, 0.2);

	//create front of coin
	Object Coin("coin.png", 275, 150, 0.5, 0.5);

	//create back of coin
	Object PokeCoin("Pokecoin.png", 275, 150, 1, 1);

	//Create a rectangle to represent the menu
	sf::RectangleShape menu1(sf::Vector2f(600, 800));
	menu1.setFillColor(sf::Color::Color(139, 69, 19, 255));
	menu1.setPosition(100, 0);

	//DUEL
	sf::Text Duel("Welcome to the\n      BATTLE!", yugioh);
	Duel.setCharacterSize(100);
	Duel.setStyle(sf::Text::Bold);
	Duel.setColor(sf::Color::Red);
	Duel.setPosition(120, 30);

	//coin flip text
	sf::Text Flip("We will flip a coin to see who goes first.\n              The Yugioh coin is you.\n          The Pokemon coin is the bot.", regular);
	Flip.setCharacterSize(35);
	Flip.setStyle(sf::Text::Bold);
	Flip.setColor(sf::Color::White);
	Flip.setPosition(130, 350);

	//Player 1 goes first
	sf::Text First("You're going\nfirst", regular);
	First.setCharacterSize(150);
	First.setStyle(sf::Text::Bold);
	First.setColor(sf::Color::Red);
	First.setPosition(120, 30);

	//Player 2 goes first
	sf::Text Second("The bot is\ngoing first", regular);
	Second.setCharacterSize(150);
	Second.setStyle(sf::Text::Bold);
	Second.setColor(sf::Color::Red);
	Second.setPosition(120, 30);

	//Exit
	sf::Text Exit("Exit!", yugioh);
	Exit.setCharacterSize(150);
	Exit.setStyle(sf::Text::Bold);
	Exit.setColor(sf::Color::Red);
	Exit.setPosition(250, 160);
	Exit.setLineSpacing(1.3);

	//Render
	window.clear();
	window.draw(background);
	window.draw(menu1);
	spriteDragon.drawObject(window);
	window.draw(welcome);
	window.draw(text);
	window.display();
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))){
			//new screen
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

				//give c++ code firstPlayer
				menu.duel(firstPlayer);
				
				//delay screen
				delayScreen(1.5);
				//old screen
				window.clear();
				window.draw(background);
				window.draw(menu1);
				spriteDragon.drawObject(window);
				window.draw(welcome);
				window.draw(text);
				window.display();
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))) {
			//new screen
				window.clear();
				window.draw(background);
				window.draw(Exit);
				window.display();
				//delay screen
				delayScreen(1.5);
			//exit
				window.clear();
				window.close();
		}
		//else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))) {
		//	//new screen
		//		window.clear();
		//		window.draw(background);
		//		window.draw(Trade);
		//		window.display();
		//		//delay screen
		//		delayScreen(3);
		//	//old screen
		//		window.clear();
		//		window.draw(background);
		//		window.draw(menu1);
		//		window.draw(spriteDragon);
		//		window.draw(welcome);
		//		window.draw(text);
		//		window.display();
		//}
		//else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))) {
		//	//new screen
		//		window.clear();
		//		window.draw(background);
		//		window.draw(Duel);
		//		window.display();
		//		//delay screen
		//		delayScreen(3);
		//	//old screen
		//		window.clear();
		//		window.draw(background);
		//		window.draw(menu1);
		//		window.draw(spriteDragon);
		//		window.draw(welcome);
		//		window.draw(text);
		//		window.display();
		//}
		//else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))) {
		//	//new screen
		//		window.clear();
		//		window.draw(background);
		//		window.draw(loadTrunk);
		//		window.display();
		//		//delay screen
		//		delayScreen(3);
		//	//old screen
		//		window.clear();
		//		window.draw(background);
		//		window.draw(menu1);
		//		window.draw(spriteDragon);
		//		window.draw(welcome);
		//		window.draw(text);
		//		window.display();
		//}
		//else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))) {
		//	window.clear();
		//	window.close();
		//}
	}
	int selection = 0;
	do {
		selection = menu.display();
		clrscr();
		switch (selection) {
			//	case CREATE_PLAYERS:menu.createPlayers(); break;
			//	case EDIT_DECK:menu.editDeck(); break;
			//	case TRADE_CARDS: menu.tradeCards(); break;
		case DUEL: menu.duel(firstPlayer); break;
			//	case LOAD_TRUNK: menu.loadTrunk(); break;
		case EXIT:break;
		default: selection = 0;  cout << "Please select a valid option.\n"; EnterKey(); break;
		}
	} while (selection != EXIT);
	return 0;
}
