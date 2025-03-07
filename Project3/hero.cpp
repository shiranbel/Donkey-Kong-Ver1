#include "hero.h"
#include "gameConfig.h"
#include "position.h"
#include <Windows.h>

// this function erases mario from the screen
void Hero::erase() {
	// check which mode the board is in
	if (pBoard->getSetColor()) {										// if color mode
		char ch = pBoard->getCharFromOriginal(pos.getX(), pos.getY());	// get the char from the current position in the original board
		switch (ch) {													// check in which color do you need to restore now
		case 'H':														// for ladder
			pBoard->setColor((int)GameConfig::colors::console);
			break;
		default:														// for others
			pBoard->setColor((int)GameConfig::colors::cyan);
			break;
		}
		draw(pBoard->getCharFromOriginal(pos.getX(), pos.getY()));		// restore the character from the original board
		pBoard->setColor((int)GameConfig::colors::console);				// bring back console color
	}
	else                // if black and white mode
		draw(pBoard->getCharFromOriginal(pos.getX(), pos.getY()));		// restore using console color
}

// this function makes sure that mario is jumping with a height of 2 chars 
void Hero::handleJump() {
	if (jump_counter == 1)
		++jump_counter;
	else if (jump_counter == GameConfig::JUMP_H) // when getting to the top free fall
		jump_counter = 0;
}

// this function takes the pressed key and changes the dir accordingly by checking the current, next and below chars
void Hero::keyPressed(char key) {

	char curr_pos_ch = pBoard->getCharFromOriginal(pos.getX(), pos.getY());				// get the char at the current position
	char curr_pos_ch_under = pBoard->getCharFromOriginal(pos.getX(), pos.getY() + 1);	// get the char below the current position

	// traverse the keys array
	for (size_t i = 0; i < numKeys; i++) {
		
		if (std::tolower(key) == 'w') {													// handle up movement
			if (curr_pos_ch != 'H' && !isOnFloor(curr_pos_ch)) {						// jump - if my position is not ladder or floor	
				if (!isOnFloor(curr_pos_ch_under)) { break; }                           // checks if is there a floor under mario - to avoid double jump
				else if (jump_counter < GameConfig::JUMP_H) {							// change direction to up (without changing x direction) and add to jump counter
					dir.y = -1;
					jump_counter++;
				}
			}
			else {																		// climb
				dir = { 0, -1 };														// change direction to straight up
			}
			break;
		} 
		else if (std::tolower(key) == 'x') {											// go down
			if (!isOnFloor(curr_pos_ch_under) && curr_pos_ch != 'H') { break; }			// block going down while jumping
			else {
				dir = { 0, 1 };															// change direction to straight down
				pressedDown = true;														// remember that it's down from the player and not free fall
			}
		}
		else if (std::tolower(key) == 's') {											// stay 
			if (!isOnFloor(curr_pos_ch_under) && curr_pos_ch != 'H') { break; }			// block stay while jumping
			else {
				dir = { 0, 0 };															// change direction to stay
			}
		}																				// other keys - right and left
		else if (std::tolower(key) == keys[i]) {
			dir = directions[i];
			return;
		}
	}
}

// this function handles the movement of mario by changing it's position according to the hero's situation and dir
void Hero::move() {
	Position newPos = { pos.getX() + dir.x, pos.getY() + dir.y };
	char next_pos_ch = pBoard->getCharFromOriginal(newPos.getX(), newPos.getY());					   // get the char of the next position

	// borders check
	if (newPos.getX() >= GameConfig::MAX_WIDTH - 1 || newPos.getY() >= GameConfig::MAX_HEIGHT - 1) {   // check if the next position is out of the board - example: jumping in corners
		dir = { 0,1 };																				   // if yes, fall and look for obstacle
		if (isOnFloor(next_pos_ch))																	   // if the next position is floor stay
			dir = { 0, 0 };

		pos.setX(pos.getX() + dir.x);																   // change position
		pos.setY(pos.getY() + dir.y);
		return;																						   // finish here
	}

	// free fall: check if there's no floor underneath and we are not in a middle of a jump
	if (pBoard->getCharFromOriginal(pos.getX(), pos.getY() + 1) == ' ' && jump_counter == 0) {
		fall_counter++;
		dir.y = 1;																						// fall and look for obstacles
		Position newPos = { pos.getX() + dir.x, pos.getY() + dir.y };
		char next_pos_ch = pBoard->getCharFromCurr(newPos.getX(), newPos.getY());						// get the new next position char
		if (isOnFloor(next_pos_ch)) 																	// check if it's an obstacle
			dir = { 0, 0 };
		
		pos.setX(pos.getX() + dir.x);																	// change position
		pos.setY(pos.getY() + dir.y);
		return;																							// finish here
	}

	if (dir.x != 0) {																				// if there's a movement in x direction
		// check if in my current position i'm on floor
		char ch_under = pBoard->getCharFromCurr(pos.getX(), pos.getY() + 1);						// get the char below my current position 
		char next_pos_ch_under = pBoard->getCharFromOriginal(newPos.getX(), newPos.getY() + 1);		// get the char below my next position
		if (isOnFloor(ch_under)) {																	// if i'm standing on a floor
			if (fall_counter >= 5)																	// handle fall damage
				is_falling = true;
			else fall_counter = 0;
		}
		if (!isOnFloor(next_pos_ch_under) && dir.y == 1) {											// handle landing on edge of floor
			dir.y = 0;
			return;
		}
		if (isOnFloor(next_pos_ch)) {																// if my next position is a floor - stop
			dir.y = 0;
			return;
		}
		if (ch_under == 'H' && jump_counter == 0) {													// handle being on a ladder when jumping
			dir.y = 1;
			pos.setX(pos.getX() + dir.x);															// change position
			pos.setY(pos.getY() + dir.y);
			return;																					// finish here
		}
	}
	else if (dir.y == -1 && jump_counter == 0) {													// handle climbing
		char curr_pos_ch = pBoard->getCharFromCurr(pos.getX(), pos.getY());							// get the current position char
		if (curr_pos_ch == ' ') {																	// stop above a floor
			dir = { 0, 0 };
			pos.setX(pos.getX() + dir.x);
			pos.setY(pos.getY() + dir.y);
			return;
		}
	}
	else if (dir.y == 1) {																			// down
		char under_floor_ch = pBoard->getCharFromCurr(newPos.getX(), newPos.getY() + 1);			// get the char under the floor
		if (under_floor_ch == 'H' && pressedDown) {													// if theres a ladder and i'm not free falling
			pressedDown = false;
			erase();																				// force down
			pos = newPos;
			draw();
		}
		else if (isOnFloor(next_pos_ch)) {															// if there's no ladder stay
			dir = { 0, 0 };																			// stay on floor
			if (fall_counter >= 5) {																// handle fall damage
				is_falling = true;
			}
			else fall_counter = 0;
			return;
		}
	}

	pos = newPos;																					// update position
}

// this function reposition mario to the starting position when eliminated by barrels or fall damage
void Hero::resetMario() {
	is_falling = false;
	fall_counter = 0;
	pos = { GameConfig::MARIO_START_POS_X, GameConfig::MARIO_START_POS_Y };
	dir = { 0, 0 };
}