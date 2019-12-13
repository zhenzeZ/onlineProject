#include "Game.h"

Game::Game()
{

	windowHeight = 600;
	windowWidth = 900;

	m_window = SDL_CreateWindow("SDL WINDOW", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	int random = rand() % 2;

	//MyServer = &server;

	MyServer = new Server(1111);

	if (random == 0) {
		isChaser = false;
		m_playerDot = new Dot(true, m_player);
		m_enemyDot = new Dot(false, m_enemy);
		cout << "YOU ARE THE RUNNER" << endl;
	}
	else {
		isChaser = true;
		m_playerDot = new Dot(false, m_player);
		m_enemyDot = new Dot(true, m_enemy);
		cout << "YOU ARE THE CHASER" << endl;
	}

	MyServer->ListenForNewConnection(isChaser);

	if (IMG_Init(imgFlags) != imgFlags)
	{
		cout << "Error: " << IMG_GetError() << endl;
	}
	else {
		/*m_player = IMG_LoadTexture(m_renderer, "ASSETS\\Dot.png");
		m_enemy = IMG_LoadTexture(m_renderer, "ASSETS\\Dot.png");*/
		m_playerDot->Init(m_renderer);
		m_enemyDot->Init(m_renderer);
	}
}

Game::~Game()
{
}

void Game::run()
{
	const Uint32 fps = 60;
	const Uint32 minimumFrameTime = 1000 / fps;

	Uint32 frameTime;
	Uint32 lastFrameTime = 0;
	Uint32 deltaTime = 0;

	while (!m_exitGame) {

		processEvents();
		frameTime = SDL_GetTicks();
		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;

		update();
		render();

		//MyServer->ListenForNewConnection(isChaser);

		if ((SDL_GetTicks() - frameTime) < minimumFrameTime) {
			SDL_Delay(minimumFrameTime - (SDL_GetTicks() - frameTime));
		}
	}

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::processEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			m_exitGame = true;
			break;
		case SDL_KEYDOWN:
			if (isChaser) {
				m_enemyDot->handleEvent(event);
			}
			else {
				m_playerDot->handleEvent(event);
			}

			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_exitGame = true;
			break;
		}
	}
}

void Game::update()
{

	if (isChaser)
	{
		m_enemyDot->move(windowHeight, windowWidth);
		string posData = m_enemyDot->GetPosAsString();
		MyServer->SendString(0,posData);
		if (preMessage != MyServer->returnMessage()) {
			preMessage = MyServer->returnMessage();
			vector<int> temp = intConverter(preMessage);
			if (temp.size() == 2) {
				m_playerDot->SetPosition(temp[0], temp[1]);
				if (m_enemyDot->Checkcollision(temp[0], temp[1])) {
					m_exitGame = true;
				}
			}
			
		}
	}
	else {
		m_playerDot->move(windowHeight, windowWidth);
		string posData = m_playerDot->GetPosAsString();
		MyServer->SendString(0,posData);
		if (preMessage != MyServer->returnMessage()) {
			preMessage = MyServer->returnMessage();
			vector<int> temp = intConverter(preMessage);
			if (temp.size() == 2) {
				m_enemyDot->SetPosition(temp[0], temp[1]);
				if (m_playerDot->Checkcollision(temp[0], temp[1])) {
					m_exitGame = true;
				}
			}
			
		}
	}

}

void Game::render()
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	SDL_RenderClear(m_renderer);

	m_playerDot->render(m_renderer);
	m_enemyDot->render(m_renderer);

	SDL_RenderPresent(m_renderer);

}

vector<int> Game::intConverter(string message) {
	string::iterator end = std::remove_if(message.begin(), message.end(), notADigit);

	string all_numbers(message.begin(), end);
	std::cout << all_numbers;

	stringstream ss(all_numbers);
	vector<int> vec;
	std::cout << std::endl;
	std::cout << "Let's start next line" << std::endl;
	int i;
	for (; ss >> i;)
	{
		vec.push_back(i);
		cout << i << endl;
	}

	return vec;
}