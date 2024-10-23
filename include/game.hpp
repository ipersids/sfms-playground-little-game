#pragma once

#include "window.hpp"

class Game {
	public:
		Game();
		~Game();

		void HandleInput();
		void Update();
		void Render();
		Window* GetWindow();
		sf::Time GetElapsed();
		void RestartClock();
	
	private:
		void MoveCharacter();
		Window _window;
		sf::Texture _texture;
		sf::Sprite _character;
		sf::Vector2i _increment;
		sf::Clock _clock;
		sf::Time _elapsed;
};
