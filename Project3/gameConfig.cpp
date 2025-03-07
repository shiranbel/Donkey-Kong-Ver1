#include <conio.h>
#include "gameConfig.h"
#include "board.h"
#include "hero.h"
#include "utils.h"
#include "barrel.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

// this function introduces the menu to the user with option buttons
void GameConfig::menu(){
	int choice;
	ShowConsoleCursor(false);   // hides cursor

	while (true) {
		// The Menu screen
		gotoxy(0, GameConfig::SCREENS_TOP_MARGIN);
		//       01234567890123456789012345678901234567890123456789012345678901234567890123456789
		cout << "                           WELCOME TO DONKEY KONG GAME!                         " << endl;
		cout << "                                === GAME MENU ===                               " << endl;
		cout << "                           Press:                                               " << endl;
		cout << "                          (1) Start a new game                                  " << endl;
		cout << "                          (2) Start a new game with colors                      " << endl;
		cout << "                          (8) Present instructions and keys                     " << endl;
		cout << "                          (9) EXIT                                              " << endl;
		cout << "                                                                                " << endl;
		std::cout << R"(				       ."`".
				   .-./ _=_ \.-.
				  {  (,(oYo),) }}
				  {{ |   "   |} }
				  { { \(---)/  }}
				  {{  }'-=-'{ } }
				  { { }._:_.{  }}
				  {{  } -:- { } }
				  {_{ }`===`{  _}
				  ((((\)     (/))))" << std::endl;


		choice = _getch(); // user's input
		switch (choice) {
		case NEW_GAME:				// black and white mode
			system("cls");
			run(false);
			break;
		case NEW_GAME_WITH_COLORS:	// color mode
			system("cls");
			run(true);
			break;
		case INSTRUCTION:			// instruction screen
			system("cls");
			printInstruction();
			break;
		case EXIT:					// exit screen
			system("cls");
			printExit();
			return;
		default:
			break;
		}

	}

}

// this function prints the exit screen
void GameConfig::printExit() {
	ShowConsoleCursor(false);					// hides th e cursor

	// exit screen
	gotoxy(0, GameConfig::SCREENS_TOP_MARGIN);	
	cout << "         Farewell, Mario. The princess was waiting for you to save her, "  << endl;
	cout << "                         but perhaps another time...                    "  << endl;  
	std::cout << R"( 
                   _____                 _ ____             
                  / ____|               | |  _ \            
                 | |  __  ___   ___   __| | |_) |_   _  ___ 
                 | | |_ |/ _ \ / _ \ / _` |  _ <| | | |/ _ \
                 | |__| | (_) | (_) | (_| | |_) | |_| |  __/
                  \_____|\___/ \___/ \__,_|____/ \__, |\___|
                                                  __/ |     
                                                 |___/     
)" << std::endl;
}

// this function prints the instructions screen
void GameConfig::printInstruction() {
	ShowConsoleCursor(false);		// hides the cursor

	// instructions screen
	gotoxy(0, GameConfig::SCREENS_TOP_MARGIN);	
	char ch;
	//       01234567890123456789012345678901234567890123456789012345678901234567890123456789
	cout << "                             === INSTRUCTIONS ===                               " << endl;
	cout << "                    Use the following keys to play the game:                    " << endl;
	cout << "                        - W/w : Up / Jump                                       " << endl;
	cout << "                        - X/x : Down                                            " << endl;
	cout << "                        - A/a : Left                                            " << endl;
	cout << "                        - D/d : Right                                           " << endl;
	cout << "                        - S/s : Stay                                            " << endl;
	cout << "                     Press ESC to return to the main menu.                      " << endl;
	cout << "				  _._______" << endl;
	cout << "				 | _______ |" << endl;
	cout << "				 ||,-----.||" << endl;
	cout << "				 |||     |||" << endl;
	cout << "				 |||_____|||" << endl;
	cout << "				 |`-------'|" << endl;
	cout << "				 | +     O |" << endl;
	cout << "				 |      O  |" << endl;
	cout << "				 | / /  ##,\"" << endl;
	cout << "				  `------\"" << endl;


	// returns to menu when pressing ESC
	ch = _getch();
	while (ch != ESC) {
		ch = _getch();
	}
	system("cls");
}

// this function prints the game over screen
void GameConfig::printGameOver() {
	ShowConsoleCursor(false);		// hides the cursor
	char ch;
	system("cls");					// erases the screen

	// exit screen
	gotoxy(0, GameConfig::SCREENS_TOP_MARGIN);
	std::cout << R"(		  __ _  __ _ _ __ ___   ___    _____   _____ _ __ 
		 / _` |/ _` | '_ ` _ \ / _ \  / _ \ \ / / _ \ '__|
		| (_| | (_| | | | | | |  __/ | (_) \ V /  __/ |   
		 \__, |\__,_|_| |_| |_|\___|  \___/ \_/ \___|_|   
		 |___/           
)" << std::endl;
	cout << "                       Don't give up Mario!! Save the princess                  " << endl;
	cout << "                            Press ESC to return to menu                         " << endl;

	// returns to menu when pressing ESC
	ch = _getch();
	while (ch != ESC) {
		ch = _getch();
	}
	system("cls");
	
}

// this function prints the winning screen
void GameConfig::printWinner() {
	ShowConsoleCursor(false);		// hides cursor
	system("cls");					// erases the screen

	// the victory screen
	gotoxy(0, GameConfig::SCREENS_TOP_MARGIN);
	cout << "	                        == YOU WON!!! ==                         	 " << endl;
	std::cout << R"(                                  ___________
                                 '._==_==_=_.'
                                 .-\:      /-.
                                | (|:.     |) |
                                 '-|:.     |-'
                                   \::.    /
                                    '::. .'
                                      ) (
                                    _.' '._
                                   `"""""""`)"										   << endl;
	cout << "	                                                                     " << endl;
	cout << "	              \"Oh Mario! You saved me! I LOVE YOU!\"                " << endl;
	cout << "	                  Press ESC to return to menu                        " << endl;

	// returns to menu when pressing ESC
	char ch = _getch();
	while (ch != ESC) {
		ch = _getch();
	}
	system("cls");
}

// this function prints the pausing screen
void GameConfig::printPause() {
	ShowConsoleCursor(false);	// hides the cursor
	system("cls");				// eracing the screen
	// visuals
	gotoxy(0, GameConfig::SCREENS_TOP_MARGIN);
	cout << R"(
		.-------.    ____      ___    _    .-'''-.     .-''-.   
		\  _(`)_ \ .'  __ `. .'   |  | |  / _     \  .'_ _   \  
		| (_ o._)|/   '  \  \|   .'  | | (`' )/`--' / ( ` )   ' 
		|  (_,_) /|___|  /  |.'  '_  | |(_ o _).   . (_ o _)  | 
		|   '-.-'    _.-`   |'   ( \.-.| (_,_). '. |  (_,_)___| 
		|   |     .'   _    |' (`. _` /|.---.  \  :'  \   .---. 
		|   |     |  _( )_  || (_ (_) _)\    `-'  | \  `-'    / 
		/   )     \ (_ o _) / \ /  . \ / \       /   \       /  
		`---'      '.(_,_).'   ``-'`-''   `-...-'     `'-..-'   
		    )" << endl;
	cout << "\n";
	cout << "                                Press ESC to resume";
}

// this function checks if the hero is at the same position of the princess
bool GameConfig::checkIsWinner(Hero mario) {
	return (mario.getBoard()->getCharFromOriginal(mario.getPosition().getX(), mario.getPosition().getY()) == '$');
}

// this function resets the game when the hero is damaged by resetting the hero and the barrels
void GameConfig::resetGame(int& barrel_ind, Hero& mario, Barrel* barrel_arr, int size) {
	mario.resetMario();						// resets the hero

	for (int i = 0; i < barrel_ind; i++)	// erase all barrels
		barrel_arr[i].erase();

	barrel_ind = 0;							// keads to resseting the barrels
	mario.changelives();					// decreace the hero's remaining lives
}

// this function runs the game loop and handles the game's actions and effects
void GameConfig::run(bool with_color) {

	ShowConsoleCursor(false);					// hides cursor

	Barrel barrel_arr[NUMBER_OF_BARRELS] = {};	// initializes max barrels array
	Board board(with_color);					// prints the board in the given color mode
	board.setColor((int)GameConfig::colors::console);	// set the color back to consile color for the next printing
	Hero mario(&board);							// create the hero int the board

	int game_loop_counter = 0;					// used to measure the time of the barrels' exit
	int barrel_ind = 0;							// used as the physical size of the barrels in the array
	int barrel_adder = BARREL_ADDER;			// used to change the barrel's direction during creation

	
	while (true) {                                                           // game loop
		
		if (mario.getIsFalling()) {                                          // checks if Mario has fallen and reset the game if necessary 
			resetGame(barrel_ind, mario, barrel_arr, NUMBER_OF_BARRELS);
			if (mario.getLife() == 0) {
				printGameOver();
				return;
			}
		}

		if (game_loop_counter == 0 && barrel_ind < NUMBER_OF_BARRELS) {      // create barrels
			Barrel b( &board,{ DONKEY_KONG_POS_X + barrel_adder, DONKEY_KONG_POS_Y });
			barrel_arr[barrel_ind] = b;                                      
			barrel_adder *= -1;   // change barrel's direction
			barrel_ind++;
		}

		mario.draw();                                                        // draw the hero
		
	    for (int i = 0; i < barrel_ind; i++)                                 // draw all barrels
			barrel_arr[i].draw();

		if ((mario.isCollision())) {                                         // checks if Mario has collision with barrel and reset the game if necessary 
			resetGame(barrel_ind, mario, barrel_arr, NUMBER_OF_BARRELS);
			if (mario.getLife() == 0) {
				printGameOver();
				return;
			}
		}

		if (mario.getJumpCount() > 0)                                        // fix jump counter
			mario.handleJump();

		if (_kbhit()) {                                                      // get keyborad clicks
			char key = _getch();
			if (key == ESC) {                                                // check if the player pauses
				while (true) {												 // play when pressing ESC
					system("cls");
					printPause();
					if (_getch() == ESC) {
						system("cls");
						board.print(with_color);
						break;
					}
				}
			}
			mario.keyPressed(key);                                           // preparing Mario for his next movement based on the key.
		}                                               
		Sleep(SLEEP_DURATION);
		 
		mario.erase();                                                       // illusion of Mario's movement
		mario.move();														 // change position

		if (checkIsWinner(mario)) {											 // check if mario won
			printWinner();
			return;
		} 
		
		if ((mario.isCollision())) {                                        // check collision after Mario's movement
			resetGame(barrel_ind, mario, barrel_arr, NUMBER_OF_BARRELS);
			if (mario.getLife() == 0) {
				printGameOver();
				return;
			}
		}
		
		for (int i = 0; i < barrel_ind; i++) {                               // erase all barrels and move them
			barrel_arr[i].erase();
			barrel_arr[i].move();

			if (barrel_arr[i].getIsExplode()) { 	                         // check if barrel explodes
				barrel_arr[i].drawExplode();                                 // draw all the relevant collision points of the barrel's explosion in current map

				if ((mario.isCollision())) {                                 // check collision after barrel's explosion
					resetGame(barrel_ind, mario, barrel_arr, NUMBER_OF_BARRELS);
					if (mario.getLife() == 0) {
						printGameOver();
						return;
					}
				}

				barrel_arr[i].eraseExplode();                                // erase all collision points of the barrel's explosion from current map
				barrel_arr[i].resetBarrel({ DONKEY_KONG_POS_X + barrel_adder,  DONKEY_KONG_POS_Y });    // reset the exploded barrel
				barrel_adder *= -1;											 // blarrel direction handle
			}
		}

		game_loop_counter = (barrel_ind == 0) ? 0 : game_loop_counter + 1; 	 // game loop counter 

		if (game_loop_counter > LOOP_COUNTER)								 // for barrel creation handle
			game_loop_counter = 0;
	}
}