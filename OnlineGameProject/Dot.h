#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "LTexture.h"

class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 88;
	static const int DOT_HEIGHT = 88;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 5;

	//Initializes the variables
	Dot(bool chaser, SDL_Texture* texture);
	~Dot();

	void Init(SDL_Renderer *gRenderer);
	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move(int SCREEN_HEIGHT, int SCREEN_WIDTH);

	//Shows the dot on the screen
	void render(SDL_Renderer *gRenderer);
	void update(SDL_Keycode event);

	std::string GetPosAsString();

	bool Checkcollision(int centerX, int centerY);

	bool GetLocal() { return isLocalplayer; };

	int GetCenterX();
	int GetCenterY();

	void SetPosition(int x, int y);

private:
	bool isLocalplayer;
	bool isChaser;

	//The X and Y offsets of the dot
	int mPosX, mPosY;

	int width, height;

	int mCenterX, mCenterY;
	//The velocity of the dot
	int mVelX, mVelY;

	LTexture* gDotTexture;
};