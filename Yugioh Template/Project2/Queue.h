#include "Header.h"
#include "Card.h"
struct QueueNode {
	Card card;
	QueueNode* next;
	QueueNode* prev;
};
class Queue {// FILO
private:
	QueueNode* front;//represents the front of the queue where the oldest data members are dequeued.
	QueueNode* rear;//represents the rear of the queue where the newest data members are queued.
public:
	Queue() {//constructor
		front = nullptr;
		rear = nullptr;
	};
	~Queue() {//deletes every member in the queue.
		while (front != nullptr) {
			dequeue();
		}
	};
	void enqueue(Card);//adds a new data member to the rear.
	bool dequeue(Card&);//removes a data member from the front and stores.
	bool dequeue();//removes a data member from the front without storing.
	int size();//traverses through the queue and returns the size.
	bool peek(Card&);//reveals the next item in the queue and returns true if succesful.
	bool card(int, Card&);//given an index position checks the queue for a card. returns true if succesful.

};