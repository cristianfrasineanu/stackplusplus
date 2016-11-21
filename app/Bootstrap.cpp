#include "Console.h"
#include <vld>

using namespace std;

void main()
{
	try
	{
		View::loadViewsOptions();
		Console console;
		do
		{
			try
			{
				console.showPrompt();
				console.setLastInput(_getch());
				if (console.takeActionIfAny() == false)
				{
					console.renderNextView();
				}
			}
			catch (const invalid_argument &e)
			{
				cout << e.what();

				sleepAndClearBuffer(console.getDelay());
				console.reloadView();
			}
		} while (!console.shouldExit());
	}
	catch (const invalid_argument &e)
	{
		cout << e.what()
			<< endl;
	}
	catch (const system_error &e)
	{
		clearScreen();

		cout << e.code()
			<< " "
			<< e.what()
			<< endl;
	}
}
