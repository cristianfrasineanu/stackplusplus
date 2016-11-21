#include "Helpers.h"

void sleepAndClearBuffer(unsigned delay)
{
	Sleep(delay);

	// Clear the keyboard buffer during the sleep cycle (if there are any keys pressed), 
	// so whatever keys are hit are discarded
	while (_kbhit())
	{
		_getch();
	}
}

void clearScreen()
{
	system("cls");
}