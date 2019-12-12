#pragma once
#include "Dot.h"
#include "LTexture.h"
#include "Client.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct not_digit {
	bool operator()(const char c)
	{
		return c != ' ' && !isdigit(c);
	}
};

class Game {
public:
	Game();
	~Game();

	void run();
private:
	int windowHeight;
	int windowWidth;

	void processEvents();
	void update();
	void render();

	not_digit notADigit;
	vector<int> intConverter(string message);

	string preMessage;

	bool m_exitGame;

	bool isChaser;

	Client* MyClient; //Create server on port 100

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	Dot* m_playerDot;
	Dot* m_enemyDot;

	SDL_Texture* m_player;
	SDL_Texture* m_enemy;
};