/*
*	Copyright (C) 2020 by Hannah Noh
*
*	본 헤더파일은 game 객체를 선언한다.
*
*	Last Updated On 2020.05.29. FRI
*	@author : Hannah Noh
*/

#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

#include "honeycomb.h"
#include "player.h"
#include "flower.h"
#include "bee.h"

using namespace std;
using namespace sf;

class Game {
private:
	/* 맴버 변수 */
	int WINDOW_WIDTH, WINDOW_HEIGHT;
	int g_score, g_round, g_numofBite, g_numofItem;
	bool g_isBite, g_isItemplus, g_isUsedItem, g_clockRestart, g_isStartPageOpen;

	// flower
	float flowerX, flowerY;
	vector<Flower> flowers;
	Texture tFlower;

	SoundBuffer bufferFlower;
	Sound soundFlower;

	// bee
	vector<Bee> bees;
	Texture tBee;

	SoundBuffer bufferBee;
	Sound soundBee;

	// player
	Player player;
	Texture tPlayer;

	// honeycomb
	float honeycombX, honeycombY;
	Honeycomb honeycomb;
	Texture tHoneycomb;

	SoundBuffer bufferHoneycomb;
	Sound soundHoneycomb;

	// item
	CircleShape item;
	Texture tItem;

	SoundBuffer bufferItem;
	Sound soundItem;

	// text
	string strText;
	Font font;
	Text text;

	// background image
	Texture tBackground;
	Sprite sBackground;

	// event
	Event event;

	// window
	RenderWindow window;

	// clock
	Clock clock;

	// start page
	Texture tStartpage;
	Sprite sStartpage;

	// bgm
	Music bgm;

public:
	Game(int width, int height);

	/* 맴버 함수 */
	// 첫 페이지
	void startGame();
	void startPage();
	void showRule();

	//  Game Loop
	void runGame();
	void setText(int textSize, float positionX, float positionY);
	void roundUpdate();
	void handleKeyboardEvents();
	bool collisionEvent();
	void drawGame();

	// Game Over 페이지
	void endPage();
};

#endif