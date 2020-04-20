#include "Declarations.h"
#include "Queue.h"
#include "CardStack.h"

CardStack::CardStack(int size) {

	stack_array = new card[size];
	stack_size = size;
	top = -1;

}

CardStack::~CardStack() {

	delete [] stack_array;

}

void CardStack::push(card new_card) {

	if (!isFull()) {
		
		top++;
		stack_array[top] = new_card;
		//cout << "Added card" << endl;

	}
	else {

		cout << "Stack full" << endl;

	}
}

void CardStack::pop(card &card_destination) {

	if (!isEmpty()) {

		card_destination = stack_array[top];
		top -= 1;

	}
	else {

		cout << "Stack empty" << endl;

	}

}

bool CardStack::isFull() const {

	bool status;

	if (top == stack_size - 1) {

		status = true;

	}
	else {

		status = false;

	}

	return status;

}

bool CardStack::isEmpty() const {

	bool status;

	if (top == -1) {

		status = true;

	}
	else {

		status = false;

	}

	return status;

}

void CardStack::print() {

	int i = 0;
	card* stack_cards = new card[stack_size];

	while (!isEmpty()) {

		pop(stack_cards[i]);
		print_card(stack_cards[i]);
		i++;

	}
	i--;
	while (i >= 0) {

		push(stack_cards[i]);
		i--;

	}


}

void CardStack::print_with_numbers() {

	int i = 0;
	int counter = 1;
	card* stack_cards = new card[stack_size];

	while (!isEmpty()) {

		pop(stack_cards[i]);
		cout << i << ": " << endl;
		print_card(stack_cards[i]);
		i++;
		counter++;

	}
	i--;
	while (i >= 0) {

		push(stack_cards[i]);
		i--;

	}


}

void CardStack::shuffle() {

	int i = 0;
	int random = 0;
	card* stack_cards = new card[stack_size];
	int* parallel_array = new int[stack_size];

	while (!isEmpty()) {

		pop(stack_cards[i]);
		//print_card(stack_cards[i]);
		i++;

	}
	i--;
	while (i >= 0) {

		random = (rand() % stack_size);

		if (parallel_array[random] != 1) {

			push(stack_cards[random]);
			parallel_array[random] = 1;
			i--;

		}

	}


}

void CardStack::clear_stack() {

	card temp;
	while (!isEmpty()) {
		pop(temp);
	}

}

void CardStack::pre_build_deck(card* list_of_cards) {

	for (int count = 0; count < 1; count++) {

		system("CLS");

		cout << endl << "Generating pre-built deck";

		for (int count2 = 0; count2 < 3; count2++) {
			delay(1);
			cout << ".";
		}

		cout << endl;

	}

	int i = 1;
	i = 1;
	while (i < 41) {

		push(list_of_cards[i]);
		i++;

	}
	i = 1;
	shuffle();
	print();

	cout << endl << "Deck generated. Press any button to continue..." << endl;
	_getch();
	system("CLS");

}

void CardStack::custom_build_deck(card* list_of_cards, int* parallel_list) {

	bool building = true;
	int option = 0;
	int i = 1;

	system("CLS");

	for (; i < 121; i++) {
		cout << i << ": " << list_of_cards[i].Name << ", " << list_of_cards[i].atk << ", " << list_of_cards[i].def << ", " << list_of_cards[i].type << endl;
	}

	cout << "This is a list of every card in our data base. Pick any card one at a time to add to your deck" << endl;
	cout << "A deck cannot contain more than 1 of the same card." << endl << endl;
	cout << endl << endl << "Enter the number of the card you want to add" << endl;

	while (building) {
		

		cin >> option;

		if (parallel_list[option] != 1) {
			cout << option << ": " << list_of_cards[option].Name << ", " << list_of_cards[option].atk << ", " << list_of_cards[option].def << ", " << list_of_cards[option].type << endl;
			cout << endl << "Added..." << endl;
			parallel_list[option] = 1;
			push(list_of_cards[option]);

		}
		else {
			cout << "The card " << list_of_cards[option].Name << " is already in your deck..." << endl;
			delay(1);
		}

		if (isFull()) {
			building = false;
			cout << "Your deck is now complete..." << endl;
			shuffle();
			print();
			cout << endl << "Press any button to continue..." << endl;
			_getch();
		}

	}
}

void CardStack::reset_deck(CardStack source) {

	source.stack_array = stack_array;
	source.stack_size = stack_size;
	source.top = top;

}