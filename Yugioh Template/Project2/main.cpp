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

	//Create a rectangle to represent the menu
	sf::RectangleShape menu1(sf::Vector2f(600, 800));
	menu1.setFillColor(sf::Color::Color(139, 69, 19, 255));
	menu1.setPosition(100, 0);

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
				delayScreen(1.5);
				window.clear();
				menu.duel();
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
	return 0;
}
