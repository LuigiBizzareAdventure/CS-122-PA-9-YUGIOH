#include "Card.h"

void Card::setName(string newName) {
	name = newName;
}
void Card::setAtk(int newAtk){
	atkPoints = newAtk;
}
void Card::setDef(int newDef) {
	defPoints = newDef;
}
void Card::setType(string x) {
	typeName = x;
	if (x.compare("initial") == 0)//Why aren't there string to enum conversions!!!!!!
		type = Type::initial;
	else if (x.compare("Fodder") == 0)
		type = Type::Fodder;
	else if (x.compare("Fiend") == 0)
		type = Type::Fiend;
	else if (x.compare("Meme") == 0)
		type = Type::Meme;
	else if (x.compare("Dragon") == 0)
		type = Type::Dragon;
	else if (x.compare("STAND") == 0)
		type = Type::STAND;
	else if (x.compare("SpellCaster") == 0)
		type = Type::SpellCaster;
	else if (x.compare("Helper") == 0)
		type = Type::Helper;
	else if (x.compare("STAND_USER") == 0)
		type = Type::STAND_USER;
	else if (x.compare("GOD") == 0)
		type = Type::GOD;
	else if (x.compare("Beast") == 0)
		type = Type::Beast;
	else {
		type = Type::initial;
		typeName = "initial";
	}
}
string Card::getName(void) {
	return name;
}
int	Card::getAtk(void) {
	return atkPoints;
}
int	Card::getDef(void){
	return defPoints;
}

Type Card::getType(void) {
	return type;
}

string Card::getTypeName(void){
	return typeName;
}
int Card::getBoost(void) {
	int boost = 0;
	switch (type)
	{
	case Type::initial:		boost = 0;break;
	case Type::Fodder:		boost = 1;break;
	case Type::Fiend:		boost = 100;break;
	case Type::Meme:		boost = 500;break;
	case Type::Dragon:		boost = 400;break;
	case Type::STAND:		boost = 1000;break;
	case Type::SpellCaster:	boost = 300;break;
	case Type::Helper:		boost = 500;break;
	case Type::STAND_USER:	boost = 500;break;
	case Type::GOD:			boost = 900;break;
	case Type::Beast:		boost = 200;break;
	default: boost = 0;  break;
	}
	return boost;
}
void Card::reset(void) {
	name = "empty";
	atkPoints = 0;
	defPoints = 0;
	type = Type::initial;
	typeName = "Empty";
}

ostream& operator<<(ostream& os, Card& card) {
	os.ios_base::setf(ios_base::left);//has all strings appear on the left by default
	os <<  setw(38) << card.getName();
	os << setw(4) << card.getAtk();
	os << " " << setw(4) << card.getDef();
	os << " " << card.getTypeName();
	return os;
}