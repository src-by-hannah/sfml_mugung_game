/*
*	Copyright (C) 2020 by Hannah Noh
*
*	�� cpp ������ bee ��ü�� �����Ѵ�.
*
*	Last Updated On 2020.05.29. FRI
*	@author : Hannah Noh
*/
#include "honeycomb.h"

#include <math.h>
#include <iostream>

// �⺻������
Honeycomb::Honeycomb() {
}

// ������
Honeycomb::Honeycomb(Texture* tHoneycomb, float x, float y) : CircleShape(30.0) {
	m_isFirstCollision = true;
	setTexture(tHoneycomb);
	setPosition(x, y);
	setOrigin(30, 30);
}

// ����, �浹 �˻�
bool Honeycomb::isIntersecting(Player& player) {
	if (!m_isFirstCollision) return false;
	// The center of Circle01
	auto cur_HoneycombX = getPosition().x;
	auto cur_HoneycombY = getPosition().y;

	// The center of Circle02
	auto cur_PlayerX = player.getPosition().x;
	auto cur_PlayerY = player.getPosition().y;

	auto dist = sqrt(powf(cur_HoneycombX - cur_PlayerX, 2) + powf(cur_HoneycombY - cur_PlayerY, 2));

	if (dist < 40.0 + 30.0) {
		return true;
	}

	return false;
}

// �� ���帶�� �������� ��ġ ����
void Honeycomb::setNewPosition(float x, float y) {
	setPosition(x, y);
}

// isFirstCollision �� ����
void Honeycomb::setIsFirstCollision(bool tf) {
	m_isFirstCollision = tf;
}

// isFirstCollision ��ȯ
bool Honeycomb::getIsFirstCollision() {
	return m_isFirstCollision;
}