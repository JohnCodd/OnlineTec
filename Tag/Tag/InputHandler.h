#pragma once
#include "SDL.h"
#include <string>
#include <map>
class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void update();
	bool keyPressed(std::string key);
	bool keyHold(std::string key);
private:
	const Uint8* keyState;
	std::map<std::string, bool>current, previous;
};

