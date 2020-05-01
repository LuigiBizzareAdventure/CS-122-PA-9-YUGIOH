#ifndef YCARD_GUARD
#define YCARD_GUARD
#include "Header.h"
class YCard {
private:
	string name;
	int atkPoints;
	int defPoints;
	Type type;
	string typeName;
	string frontTexture;
	string backTexture;
public:
	YCard() {
		name = "empty";
		atkPoints = 0;
		defPoints = 0;
		type = Type::initial;
		typeName = "Empty";

	}
	friend ostream& operator<<(ostream&, YCard&);//used to output card information.
	
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