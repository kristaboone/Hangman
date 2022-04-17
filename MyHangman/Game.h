#pragma once
#include <string>
#include <vector>

class Game {
public:
	Game();			// PUBLIC CONSTRUCTOR
	void run();		// PUBLIC FUNCTION

private:
	// Private variables
	bool gameOver;
	bool hasWon;
	int count;
	std::string wordOrPhraseLower;
	std::string wordOrPhrase;
	std::string guess;
	std::vector< char > guesses;
	
	// Private functions
	bool has_guessed(char l);
	char getLetter();
	void draw();
	void replace(char l);
	void update(bool found);
	void exit();
	std::string setupInitialGuess(const std::string& aInputWordOrPhrase) const;
};
