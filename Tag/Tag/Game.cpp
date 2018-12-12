#include "Game.h"
#include "Client.h"

Game::Game(int fps, int screenWidth, int screenHeight) : m_window(NULL), screenSurface(NULL), m_renderer(NULL), m_ready(false)
{
	m_player = Player();
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		m_window = SDL_CreateWindow("Tag", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
			//Get window surface
			screenSurface = SDL_GetWindowSurface(m_window);

			if (!myClient.Connect()) //If client fails to connect...
			{
				std::cout << "Failed to connect to server..." << std::endl;
			}
			else
			{
				m_ready = true;
			}
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}
			msperframe = (1.0 / fps) * 1000; //Set MS PER FRAME
			m_player.initTexture(m_renderer, "Resources/Sprites/redcircle.png");
		}
	}

}

void Game::Run()
{
	if (m_ready)
	{
		Uint64 NOW = SDL_GetPerformanceCounter();
		Uint64 LAST = 0;
		double dt = 0;
		SDL_Event e;
		while (quit == false)
		{
			LAST = NOW;
			NOW = SDL_GetPerformanceCounter();
			dt = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
			ProcessEvents(e);
			if (dt >= msperframe)
			{
				Update(dt);
				dt -= msperframe;
			}
			Update(dt);
			if (m_player.moved)
			{
				std::string playerPos = "X:" + std::to_string(m_player.getPosition().x) + ",Y:" + std::to_string(m_player.getPosition().y);
				myClient.SendVector(playerPos);
			}
			Render();
		}
	}
}

void Game::Update(double dt)
{
	m_player.Update(dt);
}

void Game::Render()
{
	SDL_RenderClear(m_renderer);
	m_player.Render(m_renderer);
	SDL_RenderPresent(m_renderer);
}

void Game::ProcessEvents(SDL_Event& e)
{
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
	}
}

void Game::close()
{
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::loadTexture(std::string m_path)
{

}
