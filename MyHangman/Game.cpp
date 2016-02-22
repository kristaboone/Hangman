#include "Game.h"

#include <iostream>
#include <algorithm>

// DEREK BOONE: Good practice to avoid "using namespace std"

// Constructor initializes members to defaults
Game::Game() : count( 0 ), gameOver( false ), hasWon( false ) {}

void Game::run() {
	// Output welcome message
	std::cout << "Hello! Welcome to hangman.\n"  <<
		"Player one, please enter a word!\n"<< std::endl;

	// Get word
	std::cin >> word;
	std::string thisGuess( word.size(), '_' );
	guess = thisGuess;
	
	while( 1 ) {
		bool found = false;

		// Keep prompting until new letter is guessed
		char tmp = '\0';
		while( 1 ){
			tmp = getLetter();

			if( !has_guessed( tmp ) ){
				guesses.push_back( tmp );
				break;						
			}
			std::system("cls");
			std::cout << "You've already guessed " << tmp << "! " << std::endl;
		}

		// Find position of character in word
		int pos = word.find( tmp );
		
		// If char in word, replace all instances
		if( pos != std::string::npos ) {
			replace( tmp );						
			found = true;
		}

		// Player has won if word = guess
		// Update players
		hasWon = ( word == guess );
		update( found );

		// If game over, exit
		if( gameOver ) {
			exit( );
			break;
		}
	}
}

// Get next letter from player
char Game::getLetter( ) {
	std::cout << "\nPlayer two, enter a letter!" << std::endl;

	char letter;
	std::cin >> letter;

	return letter;
}

// Updates guess by replacing sybol with a correctly guessed character
void Game::replace( char l ) {
	for ( size_t i = 0; i < word.size(); i++ ) {
		if( word.at(i) == l ) {
			guess[i] = l;	
		}
	}			
}

// Returns true if player has already guessed a character
bool Game::has_guessed( char l ) {
	bool hasFound = false;

	auto it = find( guesses.begin(), guesses.end(), l );
	if( it != guesses.end() )
		hasFound = true;

	return( hasFound );
}

// When updating:
// Let player know if guess was correct
// Let player know how many guesses they have left
// Draw the hangman
// See if the game is over
void Game::update( bool found ) {
	std::system( "cls" );
	if ( found ) {
		std::cout << "\t\t\tCorrect!" << std::endl;
	}
	else {
		std::cout << "\t\t\tIncorrect... try again!" << std::endl;
		count++;
	}
	
	if( count != 4 ) {
		std::cout << "\t\t\t" << (5-count) << " guesses left!\n" << std::endl;
	}
	else {
		std::cout << "\t\t\t" << (5-count) << " guess left!\n" << std::endl;
	}

	draw( );

	if( count == 5 || hasWon ) {
		gameOver = true;
	}

	std::cout << "\t\t\t\t" << guess << "\n" << std::endl;
}

// Exit game
void Game::exit( ) {
	if( hasWon ) {
		std::cout << "Congratulations! You've won!" << std::endl;
	}
	else {
		std::cout << "You lost! The word was " << 
				word << ". Better luck next time..." << std::endl;
	}
	std::cout << "Thanks for playing!" << std::endl;
}

// Combined effort of KV and DB
// Prints an ascii string with 3-tabbed padding
void printAscii( const std::string& line ) {

	const std::string padding = "\t\t\t";
	std::cout << padding << line << std::endl;

}

// Combined effort of KV and DB
// Draws the hangman picture
void Game::draw( ) {

	printAscii( "----------" );
	printAscii( " | \t |" );

	// Print head
	printAscii( std::string(" | \t ") + std::string( (count > 0) ? "@" : "") );

	// Print neck
	if ( count < 2 ) {
		printAscii( " | \t" );
		printAscii( " | \t" );
	}
	else {
		std::string bigStr = std::string( " | \t" ) 
			+ std::string( ( count > 2 ) ? "/" : " " )
			+ std::string( "|" )
			+ std::string( ( count > 3 ) ? "\\" : "" );
		printAscii( bigStr );
		printAscii( " | \t |" );
	}

	// Print feet
	printAscii( std::string( " | \t" ) + std::string( ( count > 4 ) ? "/ \\" : "" ) );

#if 0
	// PRINT 
	if(count > 1){
		printAscii(" | \t |");
		printAscii(" | \t |"); 
	}
	else{
		printAscii(" | \t  ");
		printAscii(" | \t  ");
	}

	if(count > 2){
		printAscii(" | \t/|");
	}
	else{
		printAscii(" | \t  ");
	}

	if(count > 3){
		printAscii(" | \t/|");
	}
	else{
		printAscii(" | \t  ");
	}

	else if(count > 2){
		cout << 
			"\t\t\t | \t @\n" <<
			"\t\t\t | \t  \n" <<
			"\t\t\t | \t  \n" <<
			" | \t  ";
	}
	else if(count == 2){
		cout << 
			"\t\t\t | \t @\n" <<
			"\t\t\t | \t |\n" <<
			"\t\t\t | \t |\n" <<
			"\t\t\t | \t  \n";
	}
	else if( count == 3){
		cout << 
			"\t\t\t | \t @\n" <<
			"\t\t\t | \t/|\n" <<
			"\t\t\t | \t |\n" <<
			"\t\t\t | \t  \n";
	}
	else if( count == 4){
		cout << 
			"\t\t\t | \t @  \n" <<
			"\t\t\t | \t/|\\\n" <<
			"\t\t\t | \t |  \n" <<
			"\t\t\t | \t    \n";
	}
	else{
		cout <<
			"\t\t\t | \t @  \n" <<
			"\t\t\t | \t/|\\\n" <<
			"\t\t\t | \t |  \n" <<
			"\t\t\t | \t/ \\\n";
	}
#endif
	printAscii( "_|_____________" );
	printAscii( "|             |" );
	printAscii( "|_____________|\n" );
}
