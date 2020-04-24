
#ifndef CARD_GUARD
#define CARD_GUARD
#include "Header.h"



class Card {
private:
	string name;
	int atkPoints;
	int defPoints;
	Type type;
	string typeName;
public:
	Card() {
		name = "empty";
		atkPoints = 0;
		defPoints = 0;
		type = Type::initial;
		typeName = "Empty";
	}
	friend ostream& operator<<(ostream&, Card&);//used to output card information.
	
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
#endif CARD_GUARD