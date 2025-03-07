#pragma once

#include <iostream>
#include "utils.h"
#include "board.h"
#include "gameConfig.h"
#include "position.h"

class Barrel {

	struct Direction { int x, y; };							// creating a struct called direction
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

	Position pos = { GameConfig::DONKEY_KONG_POS_X,GameConfig::DONKEY_KONG_POS_Y };		// representing the barrel's position
	Direction dir = { 0, 0 };								// representing the barrel's direction
	Direction last_dir = { 0,0 };							// for saving last direction
	Board* pBoard = nullptr;								// to give it a board

	char symbol = 'O';										// his visual on screen
	bool isExplode = false;									// flag for exploding from fall damage
	int fall_counter = 0;									// counter for checking fall damage 

	void draw(char c) const {								// This function prints a char on screen in current position
		gotoxy(pos.getX(), pos.getY());
		std::cout << c;
	}

public:
	// ctors
	Barrel(Board* pboard, Position position) : pBoard(pboard), pos(position){}
	Barrel(){}

	void resetBarrel(Position position) {					// resets a barrel when explodes or restarts
		isExplode = false;																
		fall_counter = 0;
		pos = position;
	}										 
	bool isOnFloor(char ch) {								// checks if the given char is a floor character 
		return (ch == 'Q' || ch == '=' || ch == '>' || ch == '<');
	}			
	void drawExplode();										// draws the explosion both on screen and current board with explosion effect
	void eraseExplode();									// erases the explosion both on screen and current board and restores from original

	void erase();											// eraces a barrel
	void move();											// changes the barrel's position
	void draw() const {										// draws the barrel both on screen and in current board
		draw(symbol);
		pBoard->updateCurrBoard(pos, symbol); // draws symbol in current board
	}

	// getters
	Board* getBoard() { return  pBoard; }					// return pointer to the barrel's board
	Position getPosition() { return pos; }					// returns the barrel's current position
	bool getIsExplode() { return isExplode; }				// returns if a barrel is about to explode
};

