#include "../include/window.hpp"

Window::Window() {
	SetUp(GAMENAME, sf::Vector2u(640, 480));
}

Window::Window(const std::string& title, const sf::Vector2u& size) {
	SetUp(title, size);
}

Window::~Window() {
	Destroy();
}

void Window::Clear() {
	_window.clear(sf::Color(204, 204, 255));
}

void Window::Display() {
	_window.display();
}

void Window::Update() {
	sf::Event event;
	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			_isDone = true;
		} else if (event.type == sf::Event::KeyPressed && event.key.code  == sf::Keyboard::F5) {
			SwitchFullscreen(true);
		} else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape
							 && isFullscreen())
			SwitchFullscreen(false);
	}
}

void Window::SwitchFullscreen(bool mode) {
	_isFullscreen = mode;
	Destroy();
	Create();
}

void Window::Draw(sf::Drawable& drawable) {
	_window.draw(drawable);
}

bool Window::isDone() {
	return _isDone;
}

bool Window::isFullscreen() {
	return _isFullscreen;
}

sf::Vector2u Window::GetWindowSize() {
	return _size;
}

void Window::SetUp(const std::string& title, const sf::Vector2u& size) {
	_title = title;
	_size = size;
	_isDone = false;
	_isFullscreen = false;
	Create();
}

void Window::Create() {
	auto style = (_isFullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
	_window.create({_size.x, _size.y, 32}, _title, style);
}

void Window::Destroy() {
	_window.close();
}
