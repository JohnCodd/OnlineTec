#include "Player.h"
#include "Client.h"

class Game
{
public:
	Game(int fps, int screenWidth, int screenHeight);
	void Run();
	void Update(double dt);
	void Render();
	void ProcessEvents(SDL_Event& e);
	void close();
	void loadTexture(std::string m_path);
	bool checkIntersection(SDL_Rect r1, SDL_Rect r2);
	bool checkCircleCollision(SDL_Rect r1, SDL_Rect r2);
	enum KeyPressSurfaces
	{
		KEY_PRESS_SURFACE_DEFAULT,
		KEY_PRESS_SURFACE_UP,
		KEY_PRESS_SURFACE_DOWN,
		KEY_PRESS_SURFACE_LEFT,
		KEY_PRESS_SURFACE_RIGHT,
		KEY_PRESS_SURFACE_TOTAL
	};
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Surface* screenSurface;
	bool m_ready;
	bool quit = false;
	int msperframe;
	Player m_player;
	Player otherPlayer;
	SDL_Texture* texture;
	Client myClient = Client("127.0.0.1", 1111); //Create client to localhost ("127.0.0.1") on port 1111
};