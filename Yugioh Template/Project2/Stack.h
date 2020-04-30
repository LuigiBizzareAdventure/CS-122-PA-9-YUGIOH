#include "Header.h"
#include "Card.h"

struct StackNode {//Node used for the stack class.
	Card card;
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
	void push(Card);//pushes new data onto the stack
	bool pop(Card&);//pops data off of the stack and stores it in the parameter.
	bool pop();//pops data off the stack without storing.
	int size();//returns the size of the stack.
	bool card(int, Card&);//given an index position, checks the stack for a card. returns true if succesful.

};