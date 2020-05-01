#include "Header.h"
#include "YCard.h"

struct StackNode {//Node used for the stack class.
	YCard card;
	StackNode* next;
};

class Stack {//datatype used for the deck and graveyard.
private:
	StackNode* top;//Node is used from header.
	StackNode* temp;
public:
	Stack() {
		top = nullptr;
		//temp = nullptr;
	}
	~Stack() {
		while (top != nullptr) {
			while (top != nullptr) {
				pop();

			}
		}
	};
	void push(YCard);//pushes new data onto the stack
	bool pop(YCard&);//pops data off of the stack and stores it in the parameter.
	bool pop();//pops data off the stack without storing.
	int size();//returns the size of the stack.
	bool card(int, YCard&);//given an index position, checks the stack for a card. returns true if succesful.

};