#include "Page.h"
#include <iostream>

/*
Default constructor
*/
Page::Page(Game* game)
{
	this->game = game;
	this->exitPageItem = PageItem("Exit", std::bind(&Page::OnSelectExit, this));
}

/*
Displays the page and outcomes of the user input to the console
*/
Page* Page::Display()
{
	std::cout << "Evil Hangman" << std::endl << std::endl;
	std::cout << "Menu Commands" << std::endl;

	for (auto const& value : this->pageItems)
	{
		std::cout << value.first << std::endl;
	}

	std::cout << this->exitPageItem.first << std::endl << std::endl;

	this->PrintBody();
	
	std::cin >> this->userInput;

	for (auto const& value : this->pageItems)
	{
		if (value.first == this->userInput)
		{
			return value.second();
		}
	}

	if (this->userInput == this->exitPageItem.first)
	{
		return this->exitPageItem.second();
	}

	return this;
}

/*
Quits the application
*/
Page* Page::OnSelectExit()
{
	exit(0);

	return nullptr;
}