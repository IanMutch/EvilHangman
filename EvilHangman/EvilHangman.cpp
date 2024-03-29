// EvilHangMan.cpp : Defines the entry point for the console application.
//

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif

#include "Page.h"
#include <iostream>
#include "ConsoleCmds.h"

int main()
{
	Game* game = new Game();
	Page* currentPage = new MainMenu(game);

	while (currentPage != nullptr)
	{
		Page* next = currentPage->Display();

		if (next != currentPage)
		{
			Page* oldPage = currentPage;
			currentPage = next;
			delete oldPage;
		}

		ClearConsole();
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
    return 0;
}