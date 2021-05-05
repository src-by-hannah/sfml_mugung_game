/*
*	Copyright (C) 2020 by Hannah Noh
*
*	본 cpp 파일은 flower 객체를 정의한다.
*
*	Last Updated On 2020.05.29. FRI
*	@author : Hannah Noh
*/
#include "flower.h"

#include <math.h>
#include <iostream>

Flower::Flower(Texture* tFlower, float x, float y) : CircleShape(30.0) {
	setTexture(tFlower);
	setPosition(x, y);
	setOrigin(30, 30);
	m_deleted = false;
}

bool Flower::isIntersecting(Player& player) {
	// The center of Circle01
	auto cur_FlowerX = getPosition().x;
	auto cur_FlowerY = getPosition().y;

	// The center of Circle02
	auto cur_PlayerX = player.getPosition().x;
	auto cur_PlayerY = player.getPosition().y;

	auto dist = sqrt(powf(cur_FlowerX - cur_PlayerX, 2) + powf(cur_FlowerY - cur_PlayerY, 2));

	if (dist < 40.0 + 30.0) {
		return true;
	}

	return false;
}

bool Flower::handleCollision(Player& player, int& g_score) {
	if (!isIntersecting(player)) return false;

	m_deleted = true;
	g_score++;

	return true;
}

bool Flower::getDeleted() {
	return m_deleted;
}
