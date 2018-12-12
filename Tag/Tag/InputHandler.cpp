#include "InputHandler.h"



InputHandler::InputHandler()
{
	keyState = SDL_GetKeyboardState(NULL);

	current["W"] = false;
	current["A"] = false;
	current["S"] = false;
	current["D"] = false;

	previous = current;
}


InputHandler::~InputHandler()
{
}

void InputHandler::update()
{
	SDL_PumpEvents();
	previous = current;

	current["W"] = keyState[SDL_SCANCODE_W];
	current["A"] = keyState[SDL_SCANCODE_A];
	current["S"] = keyState[SDL_SCANCODE_S];
	current["D"] = keyState[SDL_SCANCODE_D];
}

bool InputHandler::keyPressed(std::string key)
{
	return current[key] != previous[key];
}

bool InputHandler::keyHold(std::string key)
{
	return current[key];
}
