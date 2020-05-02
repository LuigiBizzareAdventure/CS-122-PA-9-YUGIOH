#ifndef YCARD_GUARD
#define YCARD_GUARD
#include "Header.h"
class YCard : public sf::Sprite{//Card class inherits from sprite
private:
	string name;
	int atkPoints;
	int defPoints;
	Type type;
	string typeName;
	string frontPath;
	string backPath;
	sf::Texture frontTexture;
	sf::Texture backTexture;
	int xPos;
	int yPos;
public:
	
	YCard() {
		name = "empty";
		atkPoints = 0;
		defPoints = 0;
		type = Type::initial;
		typeName = "Empty";
		frontPath = "cardTextures/Mysterious Error.png";
		backPath = "cardTextures/YuGiOh Card Back.png";
		//load textures
		/*if (!frontTexture.loadFromFile(frontPath))
		{
			cout << frontPath << " could not be found.\n";
		}*/
		/*if (!backTexture.loadFromFile(backPath))
		{
			cout << backPath << " could not be found.\n";
		}*/
		setPosition(0, 0);
		setDimensions((float)200, (float)300);
	}
	
	friend ostream& operator<<(ostream&, YCard&);//used to output card information.
	void setFrontTexture(string path) {
		frontPath = path;
		if (!frontTexture.loadFromFile(frontPath))
		{
			//cout << frontPath << " could not be found.\n";
		}
		else {
			cout << frontPath + " Has loaded succesfully\n";
			//setTexture(frontTexture, true);
		}
	}
	void setBackTexture(string path) {
		frontPath = path;
		if (!backTexture.loadFromFile(backPath))
		{
			//cout << backPath << " could not be found.\n";
		}
		else {
		}
		//default card size
		float x = 150;
		float y = 225;
		sf::Vector2f targetSize(x, y);
		setScale(targetSize.x / getLocalBounds().width, targetSize.y / getLocalBounds().height);
	}

	sf::Texture getFrontTexture(void) {
		return frontTexture;
	}
	sf::Texture getBackTexture(void) {
		return backTexture;
	}
	string getFrontPath() {
		return frontPath;
	}
	string getBackPath() {
		return backPath;
	}
	void setDimensions(float x, float y) {
		sf::Vector2f targetSize(x, y);
		setScale(targetSize.x / getLocalBounds().width, targetSize.y / getLocalBounds().height);
	}

	void setName(string);
	void setAtk(int);
	void setDef(int);
	void setType(string);
	string getName(void);
	int getAtk(void);
	int getDef(void);
	Type getType(void);
	string getTypeName(void);

	int getBoost(void);//returns the boost recieved from the card's type.
	void reset(void);//card is reset to it's default state.
};
#endif YCARD_GUARD