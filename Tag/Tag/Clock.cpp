#include "Clock.h"
#include "SDL.h"

Clock::Clock() :
	m_startTicks(0),
	m_pausedTicks(0),
	m_paused(false),
	m_started(false)
{
}

Clock::~Clock()
{
}

void Clock::start()
{
	//Start the timer
	m_started = true;

	//Unpause the timer
	m_paused = false;

	//Get the current clock time
	m_startTicks = SDL_GetTicks();
}

void Clock::stop()
{
	//Stop the timer
	m_started = false;

	//Unpause the timer
	m_paused = false;
}

void Clock::pause()
{
	//If the timer is running and isn't already paused
	if ((m_started == true) && (m_paused == false))
	{
		//Pause the timer
		m_paused = true;

		//Calculate the paused ticks
		m_pausedTicks = SDL_GetTicks() - m_startTicks;
	}
}

void Clock::unpause()
{
	//If the timer is paused
	if (m_paused == true)
	{
		//Unpause the timer
		m_paused = false;

		//Reset the starting ticks
		m_startTicks = SDL_GetTicks() - m_pausedTicks;

		//Reset the paused ticks
		m_pausedTicks = 0;
	}
}

int Clock::getTicks()
{
	//If the timer is running
	if (m_started == true)
	{
		//If the timer is paused
		if (m_paused == true)
		{
			//Return the number of ticks when the timer was paused
			return m_pausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			return SDL_GetTicks() - m_startTicks;
		}
	}

	//If the timer isn't running
	return 0;
}