/*
*	Copyright (C) 2020 by Hannah Noh
*
*	본 헤더파일은 bee 객체를 선언한다.
*
*	Last Updated On 2020.05.29. FRI
*	@author : Hannah Noh
*/

#ifndef GAME_BEE__H__
#define GAME_BEE__H__

#include <SFML/Graphics.hpp>
#include "player.h"

using namespace sf;

class Bee : public CircleShape {
private:
	const float BEE_SPEED = 5.0;
	float m_speedX = BEE_SPEED, m_speedY;

public:
	Bee(Texture* tBee);

	void update(int& WINDOW_WIDTH, int& WINDOW_HEIGHT);
	bool isIntersecting(Player& player);
	void handleCollision(Player& player, bool& g_isBite);
};

#endif // !GAME_BEE__H__