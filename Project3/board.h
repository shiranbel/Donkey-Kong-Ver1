#pragma once
#include "gameConfig.h"
#include "position.h"

class Board {
	// original board
	const char* originalBoard[GameConfig::MAX_HEIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                                   LIFE: @@@                                  Q", // 2
		  "Q                                                                              Q", // 3
		  "Q    $                                                                         Q", // 4
		  "Q========   =======                                         ===========   =====Q", // 5
		  "Q                H                      &                    H                 Q", // 6
		  "Q                H               <<<<<<<<>>>>>>>             H                 Q", // 7
		  "Q                H                                           H                 Q", // 8
		  "Q                H                                           H                 Q", // 9
		  "Q                H                                           H                 Q", // 10
		  "Q          <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>           Q", // 11
		  "Q           H                                                    H             Q", // 12
		  "Q           H                                                    H             Q", // 13
		  "Q           H                                                    H             Q", // 14
		  "Q    >>>>>>>>>>>>>>>>>>>>>>>>>                      <<<<<<<<<<<<<<<<<<<<<<<<   Q", // 15
		  "Q                    H                                    H                    Q", // 16
		  "Q                    H                                    H                    Q", // 17
		  "Q                    H                                    H                    Q", // 18
		  "Q           ==================   =================   ===============           Q", // 19
		  "Q                                       H                                      Q", // 20
		  "Q                                       H                                      Q", // 21
		  "Q                                       H                                      Q", // 22
		  "Q==============================================================================Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
	
	//current board
	char currentBoard[GameConfig::MAX_HEIGHT][GameConfig::MAX_WIDTH + 1];
	bool set_color = false;					// for color options
	void reset();							// draws the board from original 

public:
	// ctor
	Board(bool with_color) {
		set_color = with_color;
		reset();
		print(with_color);
	} 

	void print(bool with_color) const;												// prints the board on screen
	void setColor(int color) const;													// setting the color of a printed char on screen

	//getters
	char getCharFromCurr(int x, int y) const { return currentBoard[y][x]; }			// returns the char from current board in the given position
	char getCharFromOriginal(int x, int y) const { return originalBoard[y][x]; }	// returns the char from original board in the given position
	bool getSetColor() { return set_color; }										// check if the board is in color mode or not

	// updates
	void updateCurrBoard(Position pos, char ch) { currentBoard[pos.getY()][pos.getX()] = ch; }	// puts a char in a given position in the currnt board
	void updateLives(int lives);													// prints the remaining lives of the hero
};
