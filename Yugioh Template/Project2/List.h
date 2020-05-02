#include "Header.h"
#include "YCard.h"

struct ListNode {
	YCard card;
	ListNode* next;
};


class List {// linked list used for both hand and placeholder deck.
private:
	ListNode* top;
	ListNode* bottom;
	ListNode* temp;
public:
	List() {
		top = nullptr;
		bottom = nullptr;
		temp = nullptr;
	}
	void addCard(YCard);//dynamically allocates space for the new card.
	int size(void);//checks hand size.
	bool card(int, YCard&);//copies the selected card the Card parameter, returns true, if successful.
	bool cardPtr(int, YCard**);
	bool removeCard(int, YCard&);//removes a card given an index. Stores the removed card in the input parameter.
	bool removeCard(int);
};