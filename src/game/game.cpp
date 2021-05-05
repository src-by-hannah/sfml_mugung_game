/*
*	Copyright (C) 2020 by Hannah Noh
*
*	�� cpp ������ game ��ü�� �����Ѵ�.
*
*	Last Updated On 2020.05.29. FRI
*	@author : Hannah Noh
*/

#include "game.h"

/* Game ������
---------------------------------*/
Game::Game(int width, int height) {
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;

	g_score = 0;
	g_round = 1;
	g_numofBite = 0;
	g_numofItem = 0;
	g_isBite = false;
	g_isItemplus = true;
	g_isUsedItem = false;
	g_clockRestart = false;
	g_isStartPageOpen = true;

	// flower
	tFlower.loadFromFile("Images/flower.png");

	srand((unsigned int)time(NULL)); // seeding
	for (int i = 0; i < 3; i++) {
		flowerX = (float)(rand() % 1100);
		flowerY = (float)(rand() % 700);
		flowers.push_back(Flower(&tFlower, flowerX, flowerY)); // create obj
	}

	if (!bufferFlower.loadFromFile("Sound/flower_collision.wav")) {
		cout << "ȿ������ ����� �� �����ϴ�." << endl;
	}
	soundFlower.setBuffer(bufferFlower);
	soundFlower.setLoop(false);
	soundFlower.setVolume(5.0);

	// bee
	tBee.loadFromFile("Images/bee.png");
	bees.push_back(Bee(&tBee));

	if (!bufferBee.loadFromFile("Sound/bee_collision.wav"))
		cout << "ȿ������ ����� �� �����ϴ�." << endl;
	soundBee.setBuffer(bufferBee);
	soundBee.setLoop(false);

	// player
	tPlayer.loadFromFile("Images/player.png");
	player = Player(&tPlayer, WINDOW_WIDTH, WINDOW_HEIGHT);

	// honeycomb
	tHoneycomb.loadFromFile("Images/honeycomb.png");

	honeycombX = (float)(rand() % 1100);
	honeycombY = (float)(rand() % 700);
	honeycomb = Honeycomb(&tHoneycomb, honeycombX, honeycombY);
	honeycomb.setIsFirstCollision(true);

	if (!bufferHoneycomb.loadFromFile("Sound/honeycomb_collision.wav"))
		cout << "ȿ������ ����� �� �����ϴ�." << endl;
	soundHoneycomb.setBuffer(bufferHoneycomb);
	soundHoneycomb.setVolume(10.0);

	// item
	item.setRadius(70.0);
	item.setOrigin(70.0, 70.0);

	tItem.loadFromFile("Images/item.png");
	item.setTexture(&tItem);

	if (!bufferItem.loadFromFile("Sound/item.wav"))
		cout << "ȿ������ ����� �� �����ϴ�." << endl;
	soundItem.setBuffer(bufferItem);
	soundItem.setVolume(10.0);

	//text
	if (!font.loadFromFile("Font/NanumSquareEB.ttf"))
		cout << "��Ʈ ������ ������ �� ����" << endl;

	text.setFont(font);

	// background image
	tBackground.loadFromFile("Images/background.png");
	tBackground.setSmooth(true);

	sBackground.setTexture(tBackground);
	sBackground.scale(Vector2f(1.2f, 1.2f));
	sBackground.setColor(Color(0, 255, 0));

	// window
	window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
				"Mugung",
				Style::Close);
	window.setFramerateLimit(60);

	// start page
	tStartpage.loadFromFile("Images/start.png");
	sStartpage.setTexture(tStartpage);
	sStartpage.scale(Vector2f(0.39f, 0.39f));

	if (!bgm.openFromFile("Sound/bgm1.wav"))
		cout << "bgm1.wav������ �� �� �����ϴ�." << endl;
	bgm.setVolume(20.0);
}


/* ù ������ 
---------------------------------*/
void Game::startGame() {
	bgm.play();

	while (window.isOpen() && g_isStartPageOpen) {
		// action
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			startPage();
		}

		// draw start page
		window.draw(sStartpage);
		window.display();
	}
	bgm.stop();

	runGame();
}

// �޴� ���� (Ű���� �̺�Ʈ 1 or 2)
void Game::startPage() {
	if (event.type == Event::KeyPressed) {
		switch (event.key.code) {
		case Keyboard::Num1:
			g_isStartPageOpen = false;
			break;

		case Keyboard::Num2:
			showRule();
			g_isStartPageOpen = false;
			break;

		default:
			break;
		}
	}
}

// 2.�� �������� ��, ���� ��� ȭ�鿡 �׸���
void Game::showRule() {
	Texture tRule;
	Sprite sRule;

	tRule.loadFromFile("Images/rule.png");
	sRule.setTexture(tRule);
	sRule.scale(Vector2f(0.39f, 0.39f));

	window.draw(sRule);
	window.display();

	if (!Keyboard::isKeyPressed(Keyboard::Enter)) {
		showRule();
	}
}


/* Game Loop 
---------------------------------*/
void Game::runGame() {
	// main bgm
	if (!bgm.openFromFile("Sound/bgm2.wav"))
		cout << "bgm2.wav������ �� �� �����ϴ�." << endl;
	bgm.play();
	bgm.setLoop(true);

	while (window.isOpen()) {
		// round update
		if (flowers.size() == 0) {
			roundUpdate();
		}

		//item ����
		if (g_score % 5 == 0 && g_score != 0 && g_isItemplus) {
			soundItem.play();
			g_numofItem++;
			g_isItemplus = false;
		}

		// ���� �� ���� ����
		strText = "Score : " + to_string(g_score) +
			"\n\nRound : " + to_string(g_round) +
			"\n\nLife : " + to_string(3 - g_numofBite) + " / 3" +
			"\n\nItem : " + to_string(g_numofItem);
		setText(20, 50, 100);

		/* Event */

		// player�� Keyboard Events
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			handleKeyboardEvents();
		}

		/* �浹 ���� */
		if (collisionEvent()) {
			break;
		}

		/* Draw */
		drawGame();
		window.display();
	}

}

// Text ����
void Game::setText(int textSize, float positionX = 100, float positionY = 800 / 2) {
	text.setString(strText);
	text.setCharacterSize(textSize);
	text.setPosition(positionX, positionY - (textSize / 2));
}

// ���� ������Ʈ
void Game::roundUpdate() {
	window.clear(sf::Color::Black);
	g_round++;

	for (int i = 0; i < (3 * g_round); i++) {
		flowerX = (float)(rand() % 1200);
		flowerY = (float)(rand() % 800);

		flowers.push_back(Flower(&tFlower, flowerX, flowerY));
	}

	honeycombX = (float)(rand() % 1100);
	honeycombY = (float)(rand() % 700);
	honeycomb.setPosition(honeycombX, honeycombY);
	honeycomb.setIsFirstCollision(true);

	bees.push_back(Bee(&tBee));
	player.setPositionCenter(WINDOW_WIDTH, WINDOW_HEIGHT);

	strText = "Round #" + to_string(g_round);
	setText(100);

	window.draw(text);
	window.display();

	Sleep(600);
}

// Ű���� �̺�Ʈ (player�� ��ġ �̵�)
void Game::handleKeyboardEvents() {
	if (event.type == Event::KeyPressed) {
		switch (event.key.code) {
		case Keyboard::Up:
			if (player.getPlayerY() > 0) {
				player.update(0.0, -10.0);
			}
			break;

		case Keyboard::Down:
			if (player.getPlayerY() < WINDOW_HEIGHT) {
				player.update(0.0, 10.0);
			}
			break;

		case Keyboard::Left:
			if (player.getPlayerX() > 0) {
				player.update(-10.0, 0.0);
			}
			break;

		case Keyboard::Right:
			if (player.getPlayerX() < WINDOW_WIDTH) {
				player.update(10.0, 0.0);
			}
			break;

		case Keyboard::Tab:
			if (g_numofItem > 0) {
				g_numofItem--;
				g_isUsedItem = true;
				g_clockRestart = true;
			}

		default:
			break;
		}
	}
}

// �浹 ���� Ȯ��
bool Game::collisionEvent() {
	// bee�� ��ġ update, bee-player �浹 ����
	for (auto& bee : bees) {
		bee.update(WINDOW_WIDTH, WINDOW_HEIGHT);

		if (!(g_isUsedItem)) {
			bee.handleCollision(player, g_isBite);
		}
	}

	// bee-player �浹���� ���,
	if (g_isBite) {
		soundBee.play();
		if (g_numofBite == 2) {
			endPage();
			return true;
		}

		player.setPositionCenter(WINDOW_WIDTH, WINDOW_HEIGHT);
		g_numofBite += 1;
		g_isBite = false;
		player.isBite(&tPlayer, g_numofBite);
	}

	// flower-player �浹 ����
	for (auto& flower : flowers) {
		if (flower.handleCollision(player, g_score)) {
			soundFlower.play();
			g_isItemplus = true;
		}
	}

	// �浹�� flower ��ü ����
	flowers.erase(remove_if(begin(flowers), end(flowers), [](Flower& flo) {
		return flo.getDeleted();
	}), end(flowers));

	// honecomb-player �浹 ����
	if (honeycomb.isIntersecting(player) && !(g_isUsedItem)) {
		soundHoneycomb.play();
		bees.push_back(Bee(&tBee));
		honeycomb.setIsFirstCollision(false);
	}

	return false;
}

// ������ Window�� �׸���
void Game::drawGame() {
	window.draw(sBackground);
	if (honeycomb.getIsFirstCollision()) window.draw(honeycomb);

	for (auto& flower : flowers)
		window.draw(flower);

	for (auto& bee : bees)
		window.draw(bee);

	window.draw(player);

	if (g_isUsedItem) {
		if (g_clockRestart) {
			clock.restart();
			g_clockRestart = false;
		}
		item.setPosition(player.getPlayerX(), player.getPlayerY());

		Time elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() < 10.0f) {
			window.draw(item);
		}
		else
			g_isUsedItem = false;
	}

	window.draw(text);
}


/* Game Over ������
---------------------------------*/
void Game::endPage() {
	// ������ ����Ǿ��� �� ����
	bgm.stop();
	if (!bgm.openFromFile("Sound/gameOver.wav"))
		cout << "ȿ������ ����� �� �����ϴ�." << endl;
	bgm.play();
	bgm.setLoop(false);

	window.clear(Color::Black);

	strText = "Game Over!";
	setText(100);

	window.draw(text);
	window.display();

	Sleep(5000);
}