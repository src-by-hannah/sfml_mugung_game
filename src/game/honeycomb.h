/*
*	Copyright (C) 2020 by Hannah Noh
*
*	본 헤더파일은 honeycomb 객체를 선언한다.
*
*	Last Updated On 2020.05.29. FRI
*	@author : Hannah Noh
*/

#ifndef GAME_HONEYCOMB__H__
#define GAME_HONEYCOMB__H__

#include <SFML/Graphics.hpp>
#include "player.h"

using namespace sf;

class Honeycomb : public CircleShape {
private:
	bool m_isFirstCollision;

public:
	Honeycomb();
	Honeycomb(Texture* tHoneycomb, float x, float y);

	bool isIntersecting(Player& player);
	void setNewPosition(float x, float y);
	void setIsFirstCollision(bool tf);
	bool getIsFirstCollision();
};

#endif // !GAME_HONEYCOMB__H__