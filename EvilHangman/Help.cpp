#include "Page.h"
#include <iostream>

/*
Default constructor
*/
Help::Help(Game* game) : Page(game)
{
	PageItem back("Back", std::bind(&Help::OnSelectBack, this));

	this->pageItems.push_back(back);
}

/*
Prints the body of the page to the console
*/
void Help::PrintBody()
{
	std::cout << "On each screen, there are menu commands that allow you" << std::endl
		<< "to switch screen which can be entered at anypoint." << std::endl << std::endl
		<< "Evil Hangman is like the traditional game of hangman" << std::endl
		<< "with one exception, the computer cheats." << std::endl << std::endl
		<< "You can only guess at each letter once and when you do" << std::endl
		<< "the computer will switch out the word regardless if you" << std::endl
		<< "guessed correctly or not." << std::endl;
}

/*
Returns the previous page
*/
Page* Help::OnSelectBack()
{
	return new MainMenu(this->GetGame());
}