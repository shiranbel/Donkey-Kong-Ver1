#pragma once
class Barrel;
class Hero;
#include "position.h"

class GameConfig
{
	void run(bool with_color);					// activates gameplay according to the given color mode
	void printInstruction();					// prints the instruction of the game
	void printExit();							// prints the exit screen
	void printGameOver();						// prints the game over screen
	void printWinner();							// prints the winning screen
	void printPause();							// prints the puase screen
	void resetGame(int& barrel_ind, Hero& mario, Barrel* barrel_arr, int size);		// resets the game by resetting mario and the barrels
	bool checkIsWinner(Hero mario);				// checks if the hero and the princess are at the same position

public:
	static constexpr int MAX_WIDTH = 80;
	static constexpr int MAX_HEIGHT = 25;

	static constexpr int MARIO_START_POS_X = 3;
	static constexpr int MARIO_START_POS_Y = 22;
	static constexpr int JUMP_H = 2;
	static constexpr int MAX_LIFE = 3;
	static constexpr int MIN_FALL_HEIGHT_MARIO = 5; 

	static constexpr int DONKEY_KONG_POS_X = 41;
	static constexpr int DONKEY_KONG_POS_Y = 6;

	static constexpr int BARREL_ADDER = 3;
	static constexpr int NUMBER_OF_BARRELS = 7;
	static constexpr int MIN_FALL_HEIGHT_BARREL = 8; 
	static constexpr int EXPLOSION_RADIUS = 2; 

	static constexpr int LIFE_POS_X = 42;
	static constexpr int LIFE_POS_Y = 2;

	static constexpr int ESC = 27;

	static constexpr int NEW_GAME = 49;
	static constexpr int INSTRUCTION = 56;
	static constexpr int EXIT = 57;
	static constexpr int NEW_GAME_WITH_COLORS = 50;

	static constexpr int SLEEP_DURATION = 100;
	static constexpr int LOOP_COUNTER = 20;

	static constexpr int SCREENS_TOP_MARGIN = 5;

	enum class colors {
		cyan = 11,
		green = 10,
		pink = 13,
		console = 7,
		red = 12,
	};

	void menu();								// presenting the menu options
};

