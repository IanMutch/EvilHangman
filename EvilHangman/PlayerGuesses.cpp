#include "Page.h"
#include <iostream>
#include "CustomIO.h"

/*
Default constructor
*/
PlayerGuesses::PlayerGuesses(Game* game) : Page(game)
{
	PageItem back("Back", std::bind(&PlayerGuesses::OnSelectBack, this));

	this->pageItems.push_back(back);
}

/*
Displays the page and outcomes of the user input to the console
*/
Page* PlayerGuesses::Display()
{
	Page* page = Page::Display();
	
	if (page == this)
	{
		std::string input = this->GetUserInput();
		int value;

		if (GetInputAsIntStrict(input, value))
		{
			int value = std::atoi(input.c_str());
			unsigned int min = 0;
			unsigned int max = 0;

			this->GetGame()->GetMinMaxPlayerGuesses(min, max);

#pragma warning (disable : 4018)

			if (value >= min && value <= max)
			{
				this->GetGame()->SetPlayerGuesses(std::stoi(input.c_str()));

				return new RemainingWords(this->GetGame());
			}
			else
			{
				std::cout << "The specified word length is not between the minimum and maximum word lengths, please enter a new value." << std::endl;
			}

#pragma warning (default : 4018)
		}
		else
		{
			std::cout << "Invalid input, a menu item or a numeric value must be entered." << std::endl;
		}
		std::cout << "Press Enter to continue...";
		std::cin.ignore(INT_MAX, '\n');
		std::cin.get();
	}

	return page;
}

/*
Prints the body of the page to the console
*/
void PlayerGuesses::PrintBody()
{
	unsigned int min = 0;
	unsigned int max = 0;

	this->GetGame()->GetMinMaxPlayerGuesses(min, max);

	std::cout << "Between " << min - 1 << " and " << max + 1 <<", type the amount of\nguesses you would like and press Enter to continue\n" << std::endl;
}

/*
Returns the previous page
*/
Page* PlayerGuesses::OnSelectBack()
{
	return new WordLength(this->GetGame());
}