#include <cstring>
#include <iostream>

#include "board.h"
#include "gameConfig.h"
#include "utils.h"

// this function resets the game by "copying" the original board
void Board::reset() {
	for (int i = 0; i < GameConfig::MAX_HEIGHT; i++) {
		memcpy(currentBoard[i], originalBoard[i], GameConfig::MAX_WIDTH + 1);
	}
}

// this function prints the board to the user according to the color mode given
void Board::print(bool with_color) const{
	char ch; 
	// for color mode - print the charcters according to their color
	if (with_color) {
		for (int i = 0; i < GameConfig::MAX_HEIGHT ; i++) {
			for (int j = 0; j < GameConfig::MAX_WIDTH; j++) {
				ch = currentBoard[i][j];   // get the char from the current board
				switch (ch) {
				// for floor characters
				case '=':
				case '<':
				case '>':
					setColor((int)GameConfig::colors::cyan);
					break;
				case 'Q':	// for border
					setColor((int)GameConfig::colors::green);
					break;
				case '&':	// for gorilla
					setColor((int)GameConfig::colors::red);
					break;
				case '$':	// for princess
					setColor((int)GameConfig::colors::pink);
					break;
				default:	// for others 
					setColor((int)GameConfig::colors::console);
					break;
				}
				std::cout << currentBoard[i][j]; // print on screen 
			}
		}
	}
	else {	// for black and white mode print the board as is
		for (int i = 0; i < GameConfig::MAX_HEIGHT - 1; i++)
			std::cout << currentBoard[i] << '\n';
		std::cout << currentBoard[GameConfig::MAX_HEIGHT - 1];
	}
}
 
// this function prints the life counter according to mario's condition  
void Board::updateLives(int lives) {
	gotoxy(GameConfig::LIFE_POS_X, GameConfig::LIFE_POS_Y);  // erasing the current lives
	for (int i = 0; i < lives + 1; i++) {   
		std::cout << ' ';
	}
	gotoxy(GameConfig::LIFE_POS_X, GameConfig::LIFE_POS_Y); // drawing the remaining lives
	for (int i = 0; i < lives; i++) {
		std::cout << '@';
	}
}

// this function set the color of the next char that will be printed on board
void Board::setColor(int color) const{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, color);
}


