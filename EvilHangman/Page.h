#pragma once

#include <vector>
#include <string>
#include <functional>
#include "Game.h"

class Page;

typedef std::pair<std::string, std::function<Page*()>> PageItem;

class Page
{
public:
	Page(Game* game);
	inline Game* GetGame() const { return this->game; }
	virtual Page* Display();
protected:
	std::vector<PageItem> pageItems;
	PageItem exitPageItem;

	virtual void PrintBody() = 0;
	inline std::string GetUserInput() const { return this->userInput; }
	virtual Page* OnSelectBack() = 0;
private:
	Game* game;
	std::string userInput;

	Page* OnSelectExit();
};

class MainMenu : public Page
{
public:
	MainMenu(Game* game);
protected:
	void PrintBody();
	Page* OnSelectBack() override;
private:
	Page* OnSelectPlay();
	Page* OnSelectHelp();
};

class Help : public Page
{
public:
	Help(Game* game);
protected:
	void PrintBody();
	Page* OnSelectBack() override;
};

class WordLength : public Page
{
public:
	WordLength(Game* game);
	Page* Display() override;
protected:
	void PrintBody();
	Page* OnSelectBack() override;
};

class PlayerGuesses : public Page
{
public:
	PlayerGuesses(Game* game);
	Page* Display() override;
protected:
	void PrintBody();
	Page* OnSelectBack() override;
};

class RemainingWords : public Page
{
public:
	RemainingWords(Game* game);
	Page* Display() override;
protected:
	void PrintBody();
	Page* OnSelectBack() override;
};

class Playing : public Page
{
public:
	Playing(Game* game);
	Page* Display() override;
protected:
	void PrintBody();
	Page* OnSelectBack() override;
};