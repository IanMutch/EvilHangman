#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>

/*
Default constructor
*/
void Game::Initialise()
{
	std::string fileName = ".\\Resources\\Dictionary";
	std::ifstream file;

	fileName.append(std::to_string(this->wordLength) + ".txt");
	file.open(fileName);
	
	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			words.push_back(line);
		}
		file.close();
	}

	this->maskedWord = std::string(this->wordLength, LETTER_MASK);
}

/*
Sets the players guesses
*/
void Game::SetPlayerGuesses(const unsigned int &playerGuesses) 
{ 
	if (playerGuesses >= MIN_GUESSES && playerGuesses <= MAX_GUESSES)
	{
		this->playerGuesses = playerGuesses;
	}
	else
	{
		throw "Specified player guesses are not within the minimum and maximum values";
	}
}

/*
Sets the target word length
*/
void Game::SetWordLength(const unsigned int &wordLength) 
{ 
	if (wordLength >= MIN_WORD_LENGTH && wordLength <= MAX_WORD_LENGTH)
	{
		this->wordLength = wordLength;
	}
	else
	{
		throw "Specified word length is not within the minimum and maximum values";
	}
}

/*
Returns true if the passed character has been guessed at
*/
const bool Game::HasGuessedAtLetter(const char &guess) const
{
	for (auto const& c : this->guessedLetters)
	{
		if (c == guess)
		{
			return true;
		}
	}

	return false;
}

/*
Attempts a guess at the masked word, returning true if the guess was correct
*/
const bool Game::GuessLetter(const char &guess)
{
	if (playerGuesses == 0)
	{
		throw "Player has no guesses remaining to attempt a guess";
	}

	const WordGroupMap wordGroups = this->GetWordGroups(guess);
	WordGroup bestMatch;

	this->guessedLetters.push_back(guess);

	for (auto const &wordGroup : wordGroups)
	{
		if (bestMatch.first.empty() || bestMatch.second.size() < wordGroup.second.size())
		{
			bestMatch = wordGroup;
		}
	}
	this->words = bestMatch.second;

	if (this->maskedWord != bestMatch.first)
	{
		this->maskedWord = bestMatch.first;

		return true;
	}
	
	this->playerGuesses--;

	return false;
}

/*
Returns a map of masked word keys with their matching words
*/
const WordGroupMap Game::GetWordGroups(const char &guess) const
{
	WordGroupMap wordGroups;

	for (auto const& word : words)
	{
		std::string maskedWord;

		if (this->GetMaskedWord(word, guess, maskedWord))
		{
			bool hasKey = false;

			for (auto &wordGroup : wordGroups)
			{
				if (wordGroup.first == maskedWord)
				{
					wordGroup.second.push_back(word);
					hasKey = true;
					break;
				}
			}

			if (!hasKey)
			{
				std::vector<std::string> words;
				words.push_back(word);
				
				wordGroups.insert(WordGroup(maskedWord, words));
			}
		}
	}

	return wordGroups;
}

/*
Returns a masked word created from a word based on the current masked word and the users guess
*/
const bool Game::GetMaskedWord(const std::string &word, const char &guess, std::string &outMaskedWord) const
{
	outMaskedWord = word;

	for (unsigned int i = 0; i < word.length(); i++)
	{
		const char letter = word[i];
		const bool isMasked = this->maskedWord[i] == LETTER_MASK;
		const bool hasMatched = this->maskedWord[i] == letter;

		if (!isMasked)
		{
			if (!hasMatched)
			{
				return false;
			}
		}
		else if(letter != guess)
		{
			outMaskedWord[i] = LETTER_MASK;
		}
	}

	return true;
}