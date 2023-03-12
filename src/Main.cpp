#include "Game.hpp"
#include "Platform/Platform.hpp"

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	// std::cout << "Hello World!" << std::endl;
#endif

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	window.create(sf::VideoMode(800.0f * screenScalingFactor, 600.0f * screenScalingFactor), "Tanks by sfml");
	platform.setIcon(window.getSystemHandle());
	Game game(&window);

	game.run();

	return 0;
}
