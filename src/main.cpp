/*
*	Copyright (C) 2020 by Hannah Noh
*
*	This file is "main.cpp".
*
*	-------------------------- Requirements ---------------------------
*	1. Add the "<path_to_sfml/>/include" to your c++ include path.
*	2. Then add "<path_to_sfml>/lib" to the linker extra library path.
*	3. Must Have... add "sfml-system.lib", "sfml-window.lib",
*						 "sfml-graphics.lib", "sfml-audio.lib"
*	--------------------------------------------------------------------
*
*	SFML Ver. : 2.5.1
*
*	Last Updated On 2020.05.29. FRI
*	@author : 20190149 Hannah Noh
*	Web page : <https://nyajjyang-portfolio.tistory.com/29>
*/

#include "game/game.h"

int main() {
	int WINDOW_WIDTH = 1200;
	int WINDOW_HEIGHT = 800;
	Game game(WINDOW_WIDTH, WINDOW_HEIGHT);

	game.startGame();

	return 0;
}