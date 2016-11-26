#include "Console.h"

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
				console.takeActionOrNext();
			}
			catch (const invalid_argument &e)
			{
				toast(e.what(), string("error"));

				sleepAndClearBuffer(console.getDelay());
				console.reloadView();
			}
		} while (!console.shouldExit());
	}
	catch (const invalid_argument &e)
	{
		toast(e.what(), string("error"));
	}
	catch (const system_error &e)
	{
		clearScreen();

		toast(e.what(), string("error"));
	}
}
