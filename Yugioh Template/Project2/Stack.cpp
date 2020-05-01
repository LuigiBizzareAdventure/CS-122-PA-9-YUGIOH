#include "Stack.h"



void Stack::push(YCard newCard) {
	StackNode* newNode = new StackNode;
	newNode->card = newCard;
	newNode->next = nullptr;
	StackNode* temp = top;
	if (top == nullptr) {
		top = newNode;
	}
	else {
		newNode->next = top;
		top = newNode;
	}
}

bool Stack::pop(YCard& store) {
	StackNode* temp = top;
	if (top == nullptr) {
		cout << "There is nothing left to pop." << endl;
		return false;
	}
	else {
		store = top->card;
		top = top->next;
		delete temp;
		return true;
	}
}
bool Stack::pop(void) {
	StackNode* temp = top;
	if (top == nullptr) {
		cout << "There is nothing left to pop." << endl;
		return false;
	}
	else {
		top = top->next;
		delete temp;
		return true;
	}
}

int Stack::size(void) {
	int count = 0;
	StackNode* current = top;
	while (current != nullptr) {
		count++;
		current = current->next;
	}
	return count;
}
bool Stack::card(int x, YCard& card) {
	int count = 0;
	StackNode* current = top;
	while (current != nullptr && count != x) {//loop which checks if the nodepointer contains a value or if the count has been reached.
		count++;
		current = current->next;//
	}
	if (current == nullptr) {//cannot access data outside of the stack size.
		cout << "You tried accessing a card that is out of bounds." << endl;
		return false;
	}
	else {//card is saved to the variable paramater that was given.
		card = current->card;
		return true;
	}
}