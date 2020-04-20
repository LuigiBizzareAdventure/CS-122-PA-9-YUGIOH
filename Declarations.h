#pragma once

/*

	File Creator: John Sbur
	Assignment: PA 5
	Created: 3/20/20
	Last Updated 3/27/20

	Purpose: To include libraries, define structs, and define functions for all source code files in PA 5.

*/

//Note: FINISHED implies tested and completed code

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>

struct card {

	string Name;
	string picture_link;
	int atk;
	int def;
	string type;

};

void delay(int number_of_seconds);
void print_menu();
void display_rules();
void print_card(card target_card);
int coin_toss();
