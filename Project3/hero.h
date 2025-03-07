#pragma once

#include <iostream>
#include "utils.h"
#include "board.h"
#include "gameConfig.h"
#include "position.h"

class Hero {
	// movement
	struct Direction { int x, y; };											// creating a struct called direction
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };

	// keys
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);

	char symbol = '@';														// his visual on screen
	int jump_counter = 0;													// counter for checking jump height
	int fall_counter = 0;													// counter for checking fall damage
	int lives = GameConfig::MAX_LIFE;										// representing remaining lives

	bool pressedDown = false;												// checks if the down movement is from free fall or by player
	bool is_falling = false;												// flag for if the hero is about to get fall damage

	Position pos{GameConfig::MARIO_START_POS_X, GameConfig::MARIO_START_POS_Y };	// representing the Hero's position
	Direction dir { 1, 0 };													// current direction: dir.x, dir.y
	Board* pBoard = nullptr;												// to give it a board

	void draw(char c) const {												// draws a given char at the hero's position
		gotoxy(pos.getX(), pos.getY());
		std::cout << c;
	}

public:
	// ctor
	Hero(Board* pboard): pBoard(pboard){}

	void draw() const { draw(symbol); }										// draws the Hero on screen
	void erase();															// erases the hero on screen
	void move();															// changes the hero's position
	void keyPressed(char key);												// gets the key that was pressed by the user

    // getters
	int getJumpCount() const{ return jump_counter; }						// return the jump counter
	int getLife() const { return lives; }									// returns the remaining lives
	bool getIsFalling() const { return is_falling; }						// checks if he is about to get fall damage
	Position getPosition() const { return pos; }							// return the hero's current position
	Board* getBoard() const { return pBoard; }								// returns a pointer to the hero's board

	bool isOnFloor(char ch) const { return (ch == 'Q' || ch == '=' || ch == '>' || ch == '<'); } // checks if a given char is a floor character
	bool isCollision() { return (pBoard->getCharFromCurr(pos.getX(), pos.getY()) == 'O'); }		 // checks if the hero's position is on barrel
	void changelives() {																		 // decreaces the remaining lives by 1
		lives--;
		pBoard->updateLives(lives);	// reprint the remaining lives according to the change
	}
	void resetMario();														// repositions the hero to the starting position
	void handleJump();														// changes the jump counter according to the hero's position

};


