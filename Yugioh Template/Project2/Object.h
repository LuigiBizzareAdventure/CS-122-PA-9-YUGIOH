#ifndef OBJECT_H
#define OBJECT_H

#include "Header.h"
#include <SFML/Graphics.hpp>

class Object {
private:
	sf::Texture aTexture;
	sf::Sprite aSprite;
public:
	Object() {
		//Default
	}

	Object(std::string imgDirectory) {
		if (!aTexture.loadFromFile(imgDirectory)) {
			std::cerr << "Error\n";
		}
		aSprite.setTexture(aTexture);
	}

	Object(std::string imgDirectory, float positionX, float positionY) {
		if (!aTexture.loadFromFile(imgDirectory)) {
			std::cerr << "Error\n";
		}
		aSprite.setTexture(aTexture);
		aSprite.setPosition(positionX, positionY);
	}

	Object(std::string imgDirectory, float positionX, float positionY, float scaleX, float scaleY) {
		if (!aTexture.loadFromFile(imgDirectory)) {
			std::cerr << "Error\n";
		}
		aSprite.setTexture(aTexture);
		aSprite.setPosition(positionX, positionY);
		aSprite.setScale(scaleX, scaleY);
	}
	

	void setString(string astring) {
		aTexture.loadFromFile(astring);
		aSprite.setTexture(aTexture);
	}
	void drawObject(sf::RenderWindow* windowPtr) {
		windowPtr->draw(aSprite);
	}
	
	void setObjectPosition(float x, float y) {
		aSprite.setPosition(x, y);
	}

	void setScale(float x, float y) {
		aSprite.setScale(x, y);
	}

	void setDimensions(float x, float y) {
		sf::Vector2f targetSize(x, y);
		aSprite.setScale(targetSize.x / aSprite.getLocalBounds().width, targetSize.y / aSprite.getLocalBounds().height);
	}

	void moveObject(char direction, float moveSpeed) {
		if (direction == 'u') {
			aSprite.move(0, -moveSpeed);
		}
		else if (direction == 'd') {
			aSprite.move(0, moveSpeed);
		}
		else if (direction == 'l') {
			aSprite.move(-moveSpeed, 0);
		}
		else if (direction == 'r') {
			aSprite.move(moveSpeed, 0);
		}
	}
};





#endif