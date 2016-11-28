#include "Console.h"

using namespace std;

void main()
{
	Console::initTerminal();
	try
	{
		Console console;
		do
		{
			try
			{
				console.showPrompt();
				console.setLastInput(getch());
				console.takeActionOrNext();
			}
			catch (const invalid_argument &e)
			{
				toast(string(e.what()), string("error"));

				sleepAndFlushInput(console.getDelay());
				clearPreviousLines(0);
			}
		} while (!console.shouldExit());
	}
	catch (const invalid_argument &e)
	{
		clearScreen();
		toast(string(e.what()), string("error"));
	}
	catch (const system_error &e)
	{
		clearScreen();
		toast(string(e.what()), string("error"));
	}
}
