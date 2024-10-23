#include "../include/game.hpp"

Game::Game(): _window(GAMENAME, sf::Vector2u(640, 480)) {
	_texture.loadFromFile("assets/circle.png");
	_character.setTexture(_texture);
	sf::Vector2u size = _texture.getSize();
	_increment = sf::Vector2i(4, 4);
}

Game::~Game() { }

void Game::HandleInput() {
	_window.Update();
}

void Game::Update() {
	_window.Update();
	MoveCharacter();
}

void Game::MoveCharacter() {
	sf::Vector2u windSize = _window.GetWindowSize();
	sf::Vector2u textSize = _texture.getSize();
	
	if ((_character.getPosition().x > windSize.x - textSize.x && _increment.x > 0)
			|| (_character.getPosition().x < 0 && _increment.x < 0))
				_increment.x = -_increment.x;

	if ((_character.getPosition().y > windSize.y - textSize.y && _increment.y > 0)
			|| (_character.getPosition().y < 0 && _increment.y < 0))
				_increment.y = -_increment.y;

	_character.setPosition(
		_character.getPosition().x + _increment.x,
		_character.getPosition().y + _increment.y
	);
}

void Game::Render() {
	_window.Clear();
	_window.Draw(_character);
	_window.Display();
}

Window* Game::GetWindow() {
	return &_window;
}

sf::Time Game::GetElapsed() {
	return _elapsed;
}

void Game::RestartClock() {
	_elapsed = _clock.restart();
}

