#pragma once
#include "Dot.h"
#include "LTexture.h"

using namespace std;

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

	bool m_exitGame;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	Dot* m_playerDot;
	Dot* m_enemyDot;

	SDL_Texture* m_player;
	SDL_Texture* m_enemy;
};