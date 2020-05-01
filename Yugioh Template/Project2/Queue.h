#include "Header.h"
#include "YCard.h"
struct QueueNode {
	YCard card;
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
	void enqueue(YCard);//adds a new data member to the rear.
	bool dequeue(YCard&);//removes a data member from the front and stores.
	bool dequeue();//removes a data member from the front without storing.
	int size();//traverses through the queue and returns the size.
	bool peek(YCard&);//reveals the next item in the queue and returns true if succesful.
	bool card(int, YCard&);//given an index position checks the queue for a card. returns true if succesful.

};