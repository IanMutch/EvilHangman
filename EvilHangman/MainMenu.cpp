#include "Page.h"
#include <iostream>

/*
Default constructor
*/
MainMenu::MainMenu(Game* game) : Page(game)
{
	PageItem play("Play", std::bind(&MainMenu::OnSelectPlay, this));
	PageItem help("Help", std::bind(&MainMenu::OnSelectHelp, this));

	this->pageItems.push_back(play);
	this->pageItems.push_back(help);
}

/*
Prints the body of the page to the console
*/
void MainMenu::PrintBody()
{
	std::cout << "Enter a menu command and press Enter to begin." << std::endl;;
}

/*
Returns the next page
*/
Page* MainMenu::OnSelectPlay()
{
	return new WordLength(this->GetGame());
}

/*
Returns the previous page
*/
Page* MainMenu::OnSelectBack()
{
	return nullptr;
}

/*
Returns the help page
*/
Page* MainMenu::OnSelectHelp()
{
	return new Help(this->GetGame());
}