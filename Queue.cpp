#include "Declarations.h"
#include "Queue.h"
#include "CardStack.h"

Queue::Queue() {

	front = nullptr;
	rear = nullptr;
	num_cards = 0;

}

Queue::~Queue() {

	clear();

}

void Queue::enqueue(card new_card) {

	QNode* newNode = nullptr;

	newNode = new QNode;
	newNode->monster = new_card;
	newNode->next = nullptr;

	if (isEmpty())
	{
		front = newNode;
		rear = newNode;
	}
	else
	{
		rear->next = newNode;
		rear = newNode;
	}

	num_cards++;

}

void Queue::dequeue(card &card_destination) {

	QNode* temp = nullptr;

	if (isEmpty()) {

		cout << "Empty Queue" << endl;

	}
	else {

		card_destination = front->monster;

		temp = front;
		front = front->next;
		delete temp;

		num_cards--;

	}

}

bool Queue::isEmpty() {

	bool status;

	if (num_cards > 0) {

		status = false;

	}
	else {

		status = true;

	}

	return status;

}

int Queue::count() {

	return num_cards;

}

void Queue::clear() {

	card monster;

	while (!isEmpty()) {

		dequeue(monster);

	}

}
