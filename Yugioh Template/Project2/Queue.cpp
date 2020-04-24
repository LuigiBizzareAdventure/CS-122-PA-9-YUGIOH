#include "Queue.h"

void Queue::enqueue(Card newCard) {
	QueueNode* newNode = new QueueNode;
	newNode->prev = nullptr;
	newNode->next = nullptr;
	newNode->card = newCard;
	QueueNode* temp;
	if (rear == nullptr) {
		rear = newNode;
		rear->next = nullptr;
		rear->prev = nullptr;
		front = rear;
	}
	else {
		newNode->next = rear;// newNode -> rear
		rear->prev = newNode;// newNode <-> rear
		rear = newNode;// rear(newNode) <-> (old rear)
	}
}

bool Queue::dequeue(Card& store) {
	if (front == nullptr) {
		//cout << "There is nothing to dequeue";
		return false;
	}
	else if (front == rear) {// executes if the front == rear
		store = front->card;
		delete front;
		front = nullptr;
		rear = nullptr;
		return true;
	}
	else {//only executes if front != rear
		store = front->card;//stores front
		front = front->prev;//front -> (old front)
		delete front->next;// front -> [deleted]
		front->next = nullptr;//front -> nullptr
		return true;
	}
}

int Queue::size(void) {
	int count = 0;
	QueueNode* current = rear;
	while (current != nullptr) {
		count++;
		current = current->next;
	}
	return count;
}
bool Queue::dequeue(void) {
	if (front == nullptr) {
		cout << "There is nothing to dequeue";
		EnterKey();
		return false;
	}
	else if (front == rear) {// executes if the front == rear
		delete front;
		front = nullptr;
		rear = nullptr;
		return true;
	}
	else {//only executes if front != rear
		front = front->prev;//front -> (old front)
		delete front->next;// front -> [deleted]
		front->next = nullptr;//front -> nullptr
		return true;
	}
}
bool Queue::card(int x, Card& card) {
	int count = 0;
	QueueNode* current = front;
	while (current != nullptr && count != x) {//loop which checks if the nodepointer contains a value or if the count has been reached.
		count++;
		current = current->prev;//
	}
	if (current == nullptr) {//cannot access data outside of the queue size.
		cout << "You tried accessing a card that is out of bounds." << endl;
		EnterKey();
		return false;
	}
	else {//card is saved to the variable paramater that was given.
		card = current->card;
		return true;
	}
}

bool Queue::peek(Card& card) {
	if (front == nullptr) {
		return false;
	}
	else {
		card = front->card;
		return true;
	}
}