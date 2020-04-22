#include "Player.h"

void Player::addLife(unsigned int x) {
	lifePoints += x;
}
bool Player::subLife(unsigned int x) {
	lifePoints -= x;
	if (lifePoints <= 0) {
		lifePoints = 0;
		return true;//returns true if a players lifepoints becomes equal or below zero.
	}
	else
		return false;

}
void Player::setLife(void) {
	lifePoints = DEFAULT_LIFEPOINTS;
}

void Player::insertCardtoDeck(Card x) {
	deck.push(x);
}

bool Player::drawCard(void) {
	bool success;
	success = deck.pop(temp);//store the popped card to temp;
	if (success) {
		hand.addCard(temp);
	}
	return success;
}
int Player::getLife() {
	return lifePoints;
}

int Player::getDeckSize(void) {
	return deck.size();
}

bool Player::card(int x, Card& card) {
	return hand.card(x, card);
}

void addCard(Card);
int size(void);
bool removeCard(int, Card&);
bool removeCard(int);