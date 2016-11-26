#include "Helpers.h"

void toLowerCase(string &input)
{
	transform(input.begin(), input.end(), input.begin(),
			  [](unsigned char ch) { return tolower(ch); });
}

void sleepAndClearBuffer(unsigned delay)
{
	Sleep(delay);

	// Clear the keyboard buffer during the sleep cycle (if there are any keys pressed).
	while (_kbhit())
	{
		_getch();
	}
}

void clearScreen()
{
	system("cls");
}