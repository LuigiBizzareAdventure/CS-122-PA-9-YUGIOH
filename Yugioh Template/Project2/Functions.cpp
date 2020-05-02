#include "Header.h"

void EnterKey(void) {
	flushCin();
	cout << "Press The ENTER Key To Continue.";
	getchar();
	clrscr();
}

void delayScreen(double seconds) {
	double milli_seconds = 1000 * seconds;
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds);
}