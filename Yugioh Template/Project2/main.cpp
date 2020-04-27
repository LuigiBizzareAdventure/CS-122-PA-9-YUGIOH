#include "Header.h"
#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#pragma warning(disable : 4996)
int main(void) {


	//fasdasdasdasd

	srand(time(NULL));//generates a seed for random numbers

	//render window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Yugioh");
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
	sf::Text text("1. Create Players\n2. Edit Deck\n3. Trade Cards With Opponent\n4. Duel\n5. Load Trunk\n6. Exit\n", regular);
	text.setCharacterSize(34);
	//text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Color(10,10,10,255));
	text.setPosition(120, 120);
	text.setLineSpacing(1.3);

	//Create a background
	sf::RectangleShape background(sf::Vector2f(800, 800));
	background.setFillColor(sf::Color::Black);
	background.setPosition(0, 0);


	//create logo
	sf::Texture logo;
	logo.loadFromFile("BlizzardDragon.png");
	logo.setSmooth(true);
	
	//create sprite
	sf::Sprite spriteDragon;
	spriteDragon.setTexture(logo);
	spriteDragon.setPosition(300, 380);
	spriteDragon.setScale(0.2,.2);

	//Create a rectangle to represent the menu
	sf::RectangleShape menu1(sf::Vector2f(600, 800));
	menu1.setFillColor(sf::Color::Color(139, 69, 19, 255));
	menu1.setPosition(100, 0);

	//Create players
	sf::Text players("Creating Players", regular);
	players.setCharacterSize(100);
	players.setStyle(sf::Text::Bold);
	players.setColor(sf::Color::Color(10, 10, 10, 255));
	players.setPosition(120, 120);
	players.setLineSpacing(1.3);

	//Create players
	sf::Text editDeck("Edit deck", regular);
	editDeck.setCharacterSize(100);
	editDeck.setStyle(sf::Text::Bold);
	editDeck.setColor(sf::Color::Color(10, 10, 10, 255));
	editDeck.setPosition(120, 120);
	editDeck.setLineSpacing(1.3);

	//Create players
	sf::Text Trade("Trading cards", regular);
	Trade.setCharacterSize(100);
	Trade.setStyle(sf::Text::Bold);
	Trade.setColor(sf::Color::Color(10, 10, 10, 255));
	Trade.setPosition(120, 120);
	Trade.setLineSpacing(1.3);

	//Create players
	sf::Text Duel("Welcome to the battle!", regular);
	Duel.setCharacterSize(100);
	Duel.setStyle(sf::Text::Bold);
	Duel.setColor(sf::Color::Color(10, 10, 10, 255));
	Duel.setPosition(120, 120);
	Duel.setLineSpacing(1.3);

	//Create players
	sf::Text loadTrunk("Loaded trunk", regular);
	loadTrunk.setCharacterSize(100);
	loadTrunk.setStyle(sf::Text::Bold);
	loadTrunk.setColor(sf::Color::Color(10, 10, 10, 255));
	loadTrunk.setPosition(120, 120);
	loadTrunk.setLineSpacing(1.3);

	//Render
	window.clear();
	window.draw(background);
	window.draw(menu1);
	window.draw(spriteDragon);
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
				window.draw(players);
				window.display();
			//old screen
				window.clear();
				window.draw(background);
				window.draw(menu1);
				window.draw(spriteDragon);
				window.draw(welcome);
				window.draw(text);
				window.display();
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))) {
			//new screen
				window.clear();
				window.draw(background);
				window.draw(editDeck);
				window.display();
			//old screen
				window.clear();
				window.draw(background);
				window.draw(menu1);
				window.draw(spriteDragon);
				window.draw(welcome);
				window.draw(text);
				window.display();
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))) {
			//new screen
				window.clear();
				window.draw(background);
				window.draw(Trade);
				window.display();
			//old screen
				window.clear();
				window.draw(background);
				window.draw(menu1);
				window.draw(spriteDragon);
				window.draw(welcome);
				window.draw(text);
				window.display();
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))) {
			//new screen
				window.clear();
				window.draw(background);
				window.draw(Duel);
				window.display();
			//old screen
				window.clear();
				window.draw(background);
				window.draw(menu1);
				window.draw(spriteDragon);
				window.draw(welcome);
				window.draw(text);
				window.display();
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))) {
			//new screen
				window.clear();
				window.draw(background);
				window.draw(loadTrunk);
				window.display();
			//old screen
				window.clear();
				window.draw(background);
				window.draw(menu1);
				window.draw(spriteDragon);
				window.draw(welcome);
				window.draw(text);
				window.display();
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))) {
			window.clear();
			window.close();
		}
	}


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
