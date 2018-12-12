#include "Player.h"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

Player::Player()
{
	position = Vector2f(100, 100);
	m_rect.x = 100;
	m_rect.y = 100;
	m_rect.w = 50;
	m_rect.h = 50;
	mSpeed = 0.5f;
}

void Player::Update(double dt)
{
	input.update();
	handleInput();
	vel *= dt;

	//std::cout << dt << std::endl;

	position += vel;

	if ((position.x < 0) || (position.x + m_rect.w > SCREEN_WIDTH))
	{
		//Move back
		position.x -= vel.x;
	}
	if ((position.y < 0) || (position.y + m_rect.h > SCREEN_HEIGHT))
	{
		//Move back
		position.y -= vel.y;
	}
}

void Player::Render(SDL_Renderer* renderer)
{
	m_rect.x = (int)position.x;
	m_rect.y = (int)position.y;
	SDL_RenderCopy(renderer, mTexture, NULL, &m_rect);
}

void Player::initTexture(SDL_Renderer* renderer, std::string string)
{
	mTexture = loadTexture(string, renderer);
}

void Player::handleInput()
{
	vel.zeroVector();
	moved = false;
	//Select surfaces based on key press
	if (input.keyHold("W"))
	{
		vel.y = -1;
		moved = true;
	}
	if (input.keyHold("S"))
	{
		vel.y = 1;
		moved = true;
	}
	if (input.keyHold("A"))
	{
		vel.x = -1;
		moved = true;
	}
	if (input.keyHold("D"))
	{		
		vel.x = 1;
		moved = true;
	}
	if (vel != Vector2f(0, 0))
	{
		vel = vel.normalise() * mSpeed;
	}
}

Vector2f Player::getPosition()
{
	return position;
}

SDL_Texture* Player::loadTexture(std::string path, SDL_Renderer* renderer)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}