#pragma once

#include "Declarations.h"

class CardStack {

private:
	card* stack_array;
	int stack_size;
	int top;

public:

	CardStack(int size);
	~CardStack();

	void push(card);
	void pop(card&);
	bool isFull() const;
	bool isEmpty() const;

	void print();
	void print_with_numbers();
	void shuffle();
	void clear_stack();
	void pre_build_deck(card* list_of_cards);
	void custom_build_deck(card* list_of_cards, int* parallel_list);
	void reset_deck(CardStack source);
};