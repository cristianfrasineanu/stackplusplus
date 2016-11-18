#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "Helpers.h"
#include "ClassContainer.h"

using namespace std;

void main()
{
	try
	{
		Console console;
		View::loadViewsOptions();
		do
		{
			try
			{
				cout << " >";

				console.setLastInput(_getch());
				cout << console.getLastInput()
					<< endl;
				//console.renderNextView();
			}
			catch (const invalid_argument &e)
			{
				cout << endl
					<< e.what()
					<< endl;

				sleepAndClearBuffer(console.getDelay());

				console.reloadView();
			}
			catch (const system_error &e)
			{
				cout << e.code()
					<< " "
					<< e.what()
					<< endl;
			}
		} while (console.getLastInput() != 'q');
	}
	catch (const invalid_argument &e)
	{
		cout << e.what()
			<< endl;
	}
}
