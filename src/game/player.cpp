/*
*	Copyright (C) 2020 by Hannah Noh
*
*	본 cpp 파일은 player 객체를 정의한다.
*
*	Last Updated On 2020.05.29. FRI
*	@author : Hannah Noh
*/

#include "player.h"
#include <string>

using namespace std;

Player::Player() {
}

Player::Player(Texture* tPlayer, int& WINDOW_WIDTH, int& WINDOW_HEIGHT) : CircleShape(50.0) {
	setTexture(tPlayer);
	setPositionCenter(WINDOW_WIDTH, WINDOW_HEIGHT);
	setOrigin(50, 50);
}

void Player::update(float x, float y) {
	move(x, y);
	playerX += x;
	playerY += y;
}

float Player::getPlayerX() {
	return playerX;
}

float Player::getPlayerY() {
	return playerY;
}

void Player::setPositionCenter(int& WINDOW_WIDTH, int& WINDOW_HEIGHT) {
	playerX = (float)(WINDOW_WIDTH / 2);
	playerY = (float)(WINDOW_HEIGHT / 2);
	setPosition(playerX, playerY);
}

void Player::isBite(Texture* tPlayer, int& numofBite) {
	string fileAddress = "Images/player_bee" + to_string(numofBite) + ".png" ;
	tPlayer->loadFromFile(fileAddress);
	setTexture(tPlayer);
}