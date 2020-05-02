#include "List.h"

void List::addCard(YCard newCard) {
	ListNode* x = new ListNode;
	x->card = newCard;
	x->next = nullptr;
	ListNode* current = top;
	ListNode* prev = nullptr;
	if (top == nullptr) {
		top = x;
		bottom = x;
	}
	else {
		prev = current;
		current = current->next;
		while (current != nullptr) {
			prev = current;
			current = current->next;
		}
		prev->next = x;
		bottom = x;

	}
}

int List::size(void) {
	int count = 0;
	ListNode* current = top;
	ListNode* prev;
	if (current == nullptr) {
		count = 0;
	}
	else {
		while (current != nullptr) {
			count++;
			prev = current;
			current = current->next;
		}
	}
	return count;
}

bool List::card(int x, YCard& card) {
	int count = 0;
	ListNode* current = top;
	while (current != nullptr && count != x) {
		count++;
		current = current->next;
	}
	if (current == nullptr) {
		cout << "You tried accessing a card that is out of bounds." << endl;
		EnterKey();
		return false;
	}
	else {
		card = current->card;
		return true;
	}
}
bool List::cardPtr(int x, YCard** cardPtr) {
	int count = 0;
	ListNode* current = top;
	while (current != nullptr && count != x) {
		count++;
		current = current->next;
	}
	if (current == nullptr) {
		cout << "You tried accessing a card that is out of bounds." << endl;
		EnterKey();
		return false;
	}
	else {
		**cardPtr = current->card;
		return true;
	}
}

bool List::removeCard(int x, YCard& store) {
	int count = 0;
	ListNode* current = top;
	ListNode* prev = nullptr;
	ListNode* temp = nullptr;
	while (current != nullptr && count != x) {
		count++;
		prev = current;
		current = current->next;
	}
	if (current == nullptr) {
		cout << "There is no card in postition " << x << " to delete." << endl;
		EnterKey();
		return false;
	}
	else if (prev != nullptr && current != nullptr) {
		prev->next = current->next;
		store = current->card;
		delete current;
		return true;
	}
	else if (prev == nullptr && current->next != nullptr) {
		store = current->card;
		temp = current->next;
		delete current;
		top = temp;
	}
	else {
		store = current->card;
		delete current;
		top = nullptr;
		return true;
	}
}

bool List::removeCard(int x) {
	int count = 0;
	ListNode* current = top;
	ListNode* prev = nullptr;
	while (current != nullptr && count != x) {
		count++;
		prev = current;
		current = current->next;
	}
	if (current == nullptr) {
		cout << "There is no card in postition " << x << " to delete." << endl;
		EnterKey();
		return false;
	}
	else if (prev != nullptr) {
		prev->next = nullptr;
		delete current;
		return true;
	}
	else {
			delete current;
			top = nullptr;
		return true;
	}
}