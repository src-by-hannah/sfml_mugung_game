/*
*	Copyright (C) 2020 by Hannah Noh
*
*	본 cpp 파일은 bee 객체를 정의한다.
*
*	Last Updated On 2020.05.29. FRI
*	@author : Hannah Noh
*/

#include "bee.h"
#include <cmath>
#include <iostream>

Bee::Bee(Texture* tBee) : CircleShape(30.0) {
	m_speedX = BEE_SPEED;
	m_speedY = BEE_SPEED;
	setTexture(tBee);
	setPosition(0, 0);
	setOrigin(30, 30);
}

void Bee::update(int& WINDOW_WIDTH, int& WINDOW_HEIGHT) {
	move(m_speedX, m_speedY);

	if ((getPosition().x) < 0)
		m_speedX = BEE_SPEED;

	else if ((getPosition().x + 2 * 20) > WINDOW_WIDTH)
		m_speedX = -BEE_SPEED;

	if (getPosition().y < 0)
		m_speedY = BEE_SPEED;

	else if ((getPosition().y + 2 * 20) > WINDOW_HEIGHT)
		m_speedY = -BEE_SPEED;
}

bool Bee::isIntersecting(Player& player) {
	// The center of Circle01
	auto cur_BeeX = getPosition().x;
	auto cur_BeeY = getPosition().y;

	// The center of Circle02
	auto cur_PlayerX = player.getPosition().x;
	auto cur_PlayerY = player.getPosition().y;

	auto dist = sqrt(powf(cur_BeeX - cur_PlayerX, 2) + powf(cur_BeeY - cur_PlayerY, 2));

	if (dist < 40.0 + 30.0) {
		return true;
	}

	return false;
}

void Bee::handleCollision(Player& player, bool& g_isBite) {
	if (!isIntersecting(player)) return;
	g_isBite = true;
}