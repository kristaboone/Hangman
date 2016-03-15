#include "Game.h"
#include <iostream>

int main( ) {

	// Create and run game
	Game myGame;
	myGame.run();

	std::cout << "Press enter to continue . . ." << std::endl;
	std::cin.get();

	return 0;
}
