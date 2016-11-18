#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "ClassContainer.h"

using namespace std;

void main()
{
	try
	{
		Console console;

		do
		{
			try
			{
				cout << " >";

				console.setLastInput(_getch());
				cout << console.getLastInput()
					<< endl;
			}
			catch (const invalid_argument &e)
			{
				cout << endl
					<< e.what()
					<< endl;

				Sleep(console.getDelay());

				// Clear the keyboard buffer during the sleep cycle (if there are any keys pressed), 
				// so as long as the keyboard is hit during that period, the input won't be taken into consideration.
				while (_kbhit())
				{
					_getch();
				}

				console.reloadView();
			}
		} while (console.getLastInput() != 'q');
	}
	catch (const invalid_argument &e)
	{
		cout << e.what()
			<< endl;
	}

}
