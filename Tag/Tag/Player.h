#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Vector2f.h"
#include "InputHandler.h"

class Player
{
public:
	Player();
	void Update(double dt);
	void Render(SDL_Renderer* renderer);
	void initTexture(SDL_Renderer* renderer, std::string string);
	void handleInput();
	Vector2f getPosition();
	SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
	bool moved;
private:
	Vector2f vel, position;
	float mSpeed = 0;
	SDL_Texture* mTexture = NULL;
	SDL_Rect m_rect;
	InputHandler input;
};