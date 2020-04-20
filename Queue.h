#ifndef QUEUE_H
#define QUEUE_H
#pragma once

#include "Declarations.h"

class Queue {

private:
	struct QNode {

		card monster;
		QNode* next;

	};
	QNode* front;
	QNode* rear;

	int num_cards;

public:

	Queue();
	~Queue();

	void enqueue(card);
	void dequeue(card&);

	bool isEmpty();
	int count();

	void clear();

};

#endif