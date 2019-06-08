#include "Page.h"
#include <iostream>

/*
Default constructor
*/
RemainingWords::RemainingWords(Game* game) : Page(game)
{
	PageItem back("Back", std::bind(&RemainingWords::OnSelectBack, this));

	this->pageItems.push_back(back);
}

/*
Displays the page and outcomes of the user input to the console
*/
Page* RemainingWords::Display()
{
	Page* page = Page::Display();
	std::string input = this->GetUserInput();

	if (page == this)
	{
		if (input == "Yes")
		{
			this->GetGame()->SetDisplayRemainingWords(true);
			page = new Playing(this->GetGame());
		}
		else if(input == "No")
		{
			this->GetGame()->SetDisplayRemainingWords(false);
			page = new Playing(this->GetGame());
		}
		else
		{
			std::cout << "Invalid input, a menu item or either Yes or No must be entered" << std::endl;
			std::cout << "Press Enter to continue...";
			std::cin.ignore(INT_MAX, '\n');
			std::cin.get();
		}
	}

	return page;
}

/*
Prints the body of the page to the console
*/
void RemainingWords::PrintBody()
{
	std::cout << "Type either Yes or No if you would like to display the\namount of possible words remaining to guess at" << std::endl;
}

/*
Returns the previous page
*/
Page* RemainingWords::OnSelectBack()
{
	return new PlayerGuesses(this->GetGame());
}