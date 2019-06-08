#pragma once

#include <vector>
#include <string>
#include <map>

#define MIN_GUESSES 5
#define MAX_GUESSES 18
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 29
#define LETTER_MASK '*'

typedef std::pair<std::string, std::vector<std::string>> WordGroup;
typedef std::map<std::string, std::vector<std::string>> WordGroupMap;

class Game
{
public:
	inline void GetMinMaxPlayerGuesses(unsigned int &min, unsigned int &max) { min = MIN_GUESSES; max = MAX_GUESSES; }
	void SetPlayerGuesses(const unsigned int &playerGuesses);
	inline const unsigned int GetPlayerGuesses() const { return this->playerGuesses; }

	inline void GetMinMaxWordLength(unsigned int &min, unsigned int &max) { min = MIN_WORD_LENGTH; max = MAX_WORD_LENGTH; }
	void SetWordLength(const unsigned int &wordLength);
	inline const unsigned int GetWordLength() const { return this->wordLength; }

	inline void SetDisplayRemainingWords(const bool &displayRemainingWords) { this->displayRemainingWords = displayRemainingWords; }
	inline const bool GetDisplayRemainingWords() const { return this->displayRemainingWords; }

#pragma warning (disable : 4267)
	inline const unsigned int GetRemainingWordCount() const { return this->words.size(); }
#pragma warning (default : 4267)
	inline const std::string GetMaskedWord() const { return this->maskedWord; }
	inline const std::vector<char> GetGuessedLetters() const { return this->guessedLetters; }
	inline const bool HasWon() const { return this->maskedWord.find(LETTER_MASK) == std::string::npos; }
	inline const bool HasLost() const { return this->playerGuesses == 0; }

	void Initialise();
	const bool HasGuessedAtLetter(const char &guess) const;
	const bool GuessLetter(const char &guess);
private:
	unsigned int playerGuesses;
	unsigned int wordLength;
	bool displayRemainingWords;
	std::vector<std::string> words;
	std::string maskedWord;
	std::vector<char> guessedLetters;

	const WordGroupMap GetWordGroups(const char &guess) const;
	const bool GetMaskedWord(const std::string &word, const char &guess, std::string &outMaskedWord) const;
};

