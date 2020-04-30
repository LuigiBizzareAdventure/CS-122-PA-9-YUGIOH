#ifndef HEADER_GUARD
#define HEADER_GUARD
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<fstream>
#include<string.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iomanip>
#include <cstdlib>
using namespace std;

#define clrscr() system("cls")//used to clear the screen
#define flushCin() cin.seekg(ios_base::end) //used to clear Cin

#define CREATE_PLAYERS 1
#define EDIT_DECK 2
#define TRADE_CARDS 3
#define DUEL 4
#define LOAD_TRUNK 5
#define EXIT 6
#define DEFAULT_LIFEPOINTS 8000
#define DECK_SIZE 30

enum class Edit {
	ADD_CARDS = 1,
	REMOVE_CARDS = 2,
	RANDOMLY_FILL = 3,
	EMPTY_DECK = 4,
	EXIT_EDIT = 5,


};

#define INVALID -1
//#define ADD_CARDS 1
//#define REMOVE_CARDS 2
//#define RANDOMLY_FILL 3
//#define EMPTY_DECK 4
//#define EXIT_EDIT 5
enum class Type{
	initial,
	Fodder,
	Fiend,
	Meme,
	Dragon,
	STAND,
	SpellCaster,
	Helper,
	STAND_USER,
	GOD,
	Beast,

	//Added 4/27/20. Incoorperates new cards from Cards.txt 
	Rock,
	Warrior,
	Machine,
	Divine,
	Fairy,
	SeaSerpent,
	Thunder,
	Dinosaur,
	Insect,


};




void EnterKey(void);//prompts the user to press enter, then clears the screen.

#endif