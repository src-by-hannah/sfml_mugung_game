/*
*	Copyright (C) 2020 by Hannah Noh
*
*	본 헤더파일은 flower 객체를 선언한다.
*
*	Last Updated On 2020.05.29. FRI
*	@author : Hannah Noh
*/

#ifndef GAME_FLOWER__H__
#define GAME_FLOWER__H__

#include <SFML/Graphics.hpp>
#include "player.h"

using namespace sf;

class Flower : public CircleShape {
private:
	bool m_deleted;

public:
	Flower(Texture* tFlower, float x, float y);

	bool isIntersecting(Player& player);
	bool handleCollision(Player& player, int& g_score);
	bool getDeleted();
};

#endif // !GAME_FLOWER__H__