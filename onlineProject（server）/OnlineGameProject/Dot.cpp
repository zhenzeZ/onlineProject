#include "Dot.h"

Dot::Dot(bool chaser, SDL_Texture* texture)
{
	gDotTexture = new LTexture(texture);

	isChaser = chaser;


	if (isChaser)
	{
		gDotTexture->setColor(244, 66, 66);
		//Initialize the offsets
		mPosX = 0;
		mPosY = 0;

		//Initialize the velocity
		mVelX = 0;
		mVelY = 0;
	}
	else
	{
		gDotTexture->setColor(66, 69, 244);
		//Initialize the offsets
		mPosX = 300;
		mPosY = 300;

		//Initialize the velocity
		mVelX = 0;
		mVelY = 0;
	}

	width = 10;
	height = 10;
}

Dot::~Dot()
{
	gDotTexture->free();
}

void Dot::SetPosition(int x, int y)
{
	mPosX = x;
	mPosY = y;

	mCenterX = mPosX + (width / 2);
	mCenterY = mPosY + (height / 2);
}

//"dot.bmp"
void Dot::Init(SDL_Renderer *gRenderer)
{
	if (isChaser)
	{
		if (!gDotTexture->loadFromFile("ASSETS\\Player.png", gRenderer))
		{
			printf("Failed to load dot texture!\n");
		}
	}
	else {
		if (!gDotTexture->loadFromFile("ASSETS\\Enemy.png", gRenderer))
		{
			printf("Failed to load dot texture!\n");
		}
	}
}

void Dot::handleEvent(SDL_Event& e)
{
	if (isChaser)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: mVelY = -DOT_VEL; break;
			case SDLK_s: mVelY = DOT_VEL; break;
			case SDLK_a: mVelX = -DOT_VEL; break;
			case SDLK_d: mVelX = DOT_VEL; break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: mVelY = 0; break;
			case SDLK_s: mVelY = 0; break;
			case SDLK_a: mVelX = 0; break;
			case SDLK_d: mVelX = 0; break;
			}
		}
	}
	else if (!isChaser)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: mVelY = -DOT_VEL; break;
			case SDLK_DOWN: mVelY = DOT_VEL; break;
			case SDLK_LEFT: mVelX = -DOT_VEL; break;
			case SDLK_RIGHT: mVelX = DOT_VEL; break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: mVelY = 0; break;
			case SDLK_DOWN: mVelY = 0; break;
			case SDLK_LEFT: mVelX = 0; break;
			case SDLK_RIGHT: mVelX = 0; break;
			}
		}
	}
}

void Dot::move(int SCREEN_HEIGHT, int SCREEN_WIDTH)
{
	//Move the dot left or right
	mPosX += mVelX;

	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH))
	{
		//Move back
		mPosX -= mVelX;
	}

	//Move the dot up or down
	mPosY += mVelY;

	//If the dot went too far up or down
	if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT))
	{
		//Move back
		mPosY -= mVelY;
	}

	mCenterX = mPosX + (width / 2);
	mCenterY = mPosY + (height / 2);
}

void Dot::render(SDL_Renderer *gRenderer)
{
	//Show the dot
	gDotTexture->render(mPosX, mPosY, gRenderer);
}

std::string Dot::GetPosAsString()
{
	std::string data = "X: " + std::to_string(mPosX);
	std::string dataY = " , Y: " + std::to_string(mPosY);
	data = data + dataY;
	//return string("X: "+to_string(mPosX) + ", " + "Y: " +to_string(mPosY));
	return data;
}

int Dot::GetCenterX()
{
	return mCenterX;
}

int Dot::GetCenterY()
{
	return mCenterY;
}

bool Dot::Checkcollision(int centerX, int centerY)
{
	int distance = sqrt(((mCenterX - centerX) * (mCenterX - centerX)) + ((mCenterY - centerY) * (mCenterY - centerY)));
	
	if (distance <= width)
	{
		return true;
	}
	else
	{
		return false;
	}
}