#include "Page.h"
#include <iostream>
#include <stdio.h>
#include "CustomIO.h"

/*
Default constructor
*/
WordLength::WordLength(Game* game) : Page(game)
{
	PageItem back("Back", std::bind(&WordLength::OnSelectBack, this));

	this->pageItems.push_back(back);
}

/*
Displays the page and outcomes of the user input to the console
*/
Page* WordLength::Display()
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

			this->GetGame()->GetMinMaxWordLength(min, max);

#pragma warning (disable : 4018)

			if (value >= min && value <= max)
			{
				this->GetGame()->SetWordLength(std::stoi(input.c_str()));

				return new PlayerGuesses(this->GetGame());
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
void WordLength::PrintBody()
{
	unsigned int min = 0;
	unsigned int max = 0;

	this->GetGame()->GetMinMaxWordLength(min, max);

	std::cout << "Between " << min - 1 << " and " << max + 1 << ", type the length of the word you would like\nto guess at and press Enter to continue.\n" << std::endl;
}

/*
Returns the previous page
*/
Page* WordLength::OnSelectBack()
{
	return new MainMenu(this->GetGame());
}