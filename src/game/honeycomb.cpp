/*
*	Copyright (C) 2020 by Hannah Noh
*
*	본 cpp 파일은 bee 객체를 정의한다.
*
*	Last Updated On 2020.05.29. FRI
*	@author : Hannah Noh
*/
#include "honeycomb.h"

#include <math.h>
#include <iostream>

// 기본생성자
Honeycomb::Honeycomb() {
}

// 생성자
Honeycomb::Honeycomb(Texture* tHoneycomb, float x, float y) : CircleShape(30.0) {
	m_isFirstCollision = true;
	setTexture(tHoneycomb);
	setPosition(x, y);
	setOrigin(30, 30);
}

// 원형, 충돌 검사
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

// 매 라운드마다 랜덤으로 위치 결정
void Honeycomb::setNewPosition(float x, float y) {
	setPosition(x, y);
}

// isFirstCollision 값 설정
void Honeycomb::setIsFirstCollision(bool tf) {
	m_isFirstCollision = tf;
}

// isFirstCollision 반환
bool Honeycomb::getIsFirstCollision() {
	return m_isFirstCollision;
}