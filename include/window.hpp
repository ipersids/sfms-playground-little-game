#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
// #include <SFML/Audio.hpp>
// #include <SFML/Network.hpp>
// #include <SFML/System.hpp>

#define GAMENAME "Little Game"

class Window {
	public:
		// constructors
		Window();
		Window(const std::string& title,
			const sf::Vector2u& size);
		// destructor
		~Window();

		// public functions
		void Clear();
		void Display();
		void Update();
		void Draw(sf::Drawable& drawable);

		bool isDone() ;
		bool isFullscreen() ;
		sf::Vector2u GetWindowSize() ;
		void SwitchFullscreen(bool mode);

	private:
		// handle setting up the window
		void SetUp(const std::string& title,
			const sf::Vector2u& size);
		void Destroy();
		void Create();
		// variables
		sf::RenderWindow _window;
		sf::Vector2u _size;
		std::string _title;
		bool _isDone;
		bool _isFullscreen;
};
