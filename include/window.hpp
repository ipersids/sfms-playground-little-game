#pragma once

#include <string>

#include "constants.hpp"

namespace GameCore {

class Window {
	public:
		explicit Window(const sf::VideoMode& mode = sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                		const std::string& title = GAMENAME);
  	~Window();

		// Prevent copying
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		// public functions
		void startDraw();
		void draw(sf::Drawable& drawable);
		void endDraw();
		void closeWindow();

		bool getStatus();
		void setStatus(bool isopen);
		sf::Vector2u GetWindowSize();
		sf::RenderWindow& getRenderWindow();

	private:
		sf::RenderWindow _window;
		bool _isOpen;
};

} // namespace GameCore