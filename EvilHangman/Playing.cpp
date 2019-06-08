#include "Page.h"
#include <iostream>

/*
Default constructor
*/
Playing::Playing(Game* game) : Page(game)
{
	PageItem back("Return", std::bind(&Playing::OnSelectBack, this));

	this->pageItems.push_back(back);

	game->Initialise();
}

/*
Displays the page and outcomes of the user input to the console
*/
Page* Playing::Display()
{
	Page* page = Page::Display();
	std::string input = this->GetUserInput();

	if (page == this)
	{
		Game* game = this->GetGame();
		std::string input = this->GetUserInput();

		if (input.length() == 1 && isalpha(input[0]))
		{
			if (!game->HasGuessedAtLetter(input[0]))
			{
				if (game->GuessLetter(input[0]))
				{
					std::cout << "You have guessed correctly." << std::endl;

					if (game->HasWon())
					{
						std::cout << "You have bested the evil hangman!" << std::endl;

						page = new MainMenu(this->GetGame());
					}
				}
				else
				{
					std::cout << "You have guessed incorrectly" << std::endl;

					if (game->HasLost())
					{
						std::cout << "The evil hangman has bested you!" << std::endl;

						page = new MainMenu(this->GetGame());
					}
				}
			}
			else
			{
				std::cout << "You have already guessed at that letter, please choose another." << std::endl;
			}
		}
		else
		{
			std::cout << "Invalid input. Please enter either a menu command or a letter to guess at" << std::endl;
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
void Playing::PrintBody()
{
	Game* game = this->GetGame();
	const std::vector<char> &guessedLetters = game->GetGuessedLetters();

	std::cout << "Word to guess: " << game->GetMaskedWord() << std::endl;
	std::cout << "Remaining guesses: " << game->GetPlayerGuesses() << std::endl;

	if (game->GetDisplayRemainingWords())
	{
		std::cout << "Remaining words: " << game->GetRemainingWordCount() << std::endl;
	}

	for (auto const& c : guessedLetters)
	{
		std::cout << c << " ";
	}
	std::cout << std::endl;

	std::cout << "Guess a letter: ";
}

/*
Returns the previous page
*/
Page* Playing::OnSelectBack()
{
	return new MainMenu(this->GetGame());
}