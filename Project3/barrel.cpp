#include "barrel.h"

// Draw all the relevant collision points of the barrel's explosion in current map
void Barrel::drawExplode() {
	int y = pos.getY();
	int x = pos.getX();
	// start from the top left corner
	for (int row = y - GameConfig::EXPLOSION_RADIUS; row <= y + GameConfig::EXPLOSION_RADIUS; row++) {   
		for (int col = x - GameConfig::EXPLOSION_RADIUS; col <= x + GameConfig::EXPLOSION_RADIUS; col++) {
			Position pos = { col, row };
			// check if pos is out of border
			if (!(col >= GameConfig::MAX_WIDTH - 1 || row >= GameConfig::MAX_HEIGHT - 1)) {
				char ch = pBoard->getCharFromOriginal(col, row); 
				// check if there's no obstacle in the printing 
				if (!isOnFloor(ch)) {						// draw only if there's no obstacle
					pBoard->updateCurrBoard(pos, symbol);	// draws in current board
					// explosion effect
					gotoxy(col, row);						
					std::cout << '\'';
				}
			}
		}
	}
	Sleep(20);
}

// Erases all the relevant collision points of the barrel's explosion from current map
void Barrel::eraseExplode() {
	int y = pos.getY();
	int x = pos.getX();
	// start from the top left corner
	for (int row = y - GameConfig::EXPLOSION_RADIUS; row <= y + GameConfig::EXPLOSION_RADIUS; row++) {
		for (int col = x - GameConfig::EXPLOSION_RADIUS; col <= x + GameConfig::EXPLOSION_RADIUS; col++) {
			Position pos = { col, row };
			// check if pos is out of border
			if (!(col >= GameConfig::MAX_WIDTH - 1 || row >= GameConfig::MAX_HEIGHT - 1)) {
				char ch = pBoard->getCharFromOriginal(col, row); 
				// check if there's no obstacle in the erasing
				if (!isOnFloor(ch)) {						// erases only if there's no obstacle
					pBoard->updateCurrBoard(pos, ch);		// erases in the current board
					// explosion effect
					gotoxy(col, row);
					std::cout << ' ';
				}
			}
		}
	}
}

// this function handles the movement of the barrel by checking the situation at next and under positions
void Barrel::move() {
	
	Position newPos = { pos.getX() + dir.x, pos.getY() + dir.y };							// get the next position of the barrel
	char next_pos_ch = pBoard->getCharFromOriginal(newPos.getX(), newPos.getY());			// gets the next position's char
	char next_pos_ch_under = pBoard->getCharFromOriginal(newPos.getX(), newPos.getY() + 1); // gets the char below the next position

	if (next_pos_ch == 'Q') {				// if collides with border erase
		erase();
	}
	if (next_pos_ch_under == ' ') {			// if nothing below fall
		dir = { 0,1 };				
		fall_counter++;
	}
	if (dir.y == 1) {						// when the barrel is falling 
		if (isOnFloor(next_pos_ch)) {		// if the next position is a floor
			dir = { 0, 0 };					// stay and check if it's fall damaged
			if (fall_counter >= GameConfig::MIN_FALL_HEIGHT_BARREL) {
				isExplode = true;
			}
			else {
				fall_counter = 0;
			}
			return;							// finish here
		}
	}
	else {									// if there is a floor below follow it's direction 
		char curr_ch_under = pBoard->getCharFromOriginal(pos.getX(), pos.getY() + 1);	// get the char below the current position

		if (curr_ch_under == '>') {			// go right
			last_dir = dir;
			dir = { 1, 0 };
		}
		else if (curr_ch_under == '<') {	// go left
			last_dir = dir;
			dir = { -1, 0 };
		}
		else if (curr_ch_under == '=') {	// move according to your last direction
			dir = last_dir;
		}

		if (next_pos_ch == 'Q') {			// if collides with border stay 
			dir = { 0, 0 };
			return;
		}
	}

	pos = newPos;							// change position
}

// this function erases the barrel from the original and current board
void Barrel::erase() {
	// get the current x, y position
	int x = pos.getX();
	int y = pos.getY();
	draw(pBoard->getCharFromOriginal(x,y));								// get the char from the original board
	pBoard->updateCurrBoard(pos, pBoard->getCharFromOriginal(x, y));	// draw it in the current board
}