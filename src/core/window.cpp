#include "../include/window.hpp"

using namespace GameCore;

Window::Window(const sf::VideoMode& mode,
               const std::string& title) {
	_window.create(mode, title, sf::Style::Titlebar | sf::Style::Close);
	_isOpen = true;
}

Window::~Window() {
	closeWindow();
}

void Window::startDraw() {
	_window.clear(sf::Color::White);
}

void Window::draw(sf::Drawable& drawable) {
	_window.draw(drawable);
}

void Window::endDraw() {
	_window.display();
}

bool Window::getStatus() {
	return _isOpen;
}

void Window::setStatus(bool isopen) {
	_isOpen = isopen;
}

void Window::closeWindow() {
	_window.close();
}

sf::Vector2u Window::GetWindowSize() {
	sf::Vector2u size = _window.getSize();
	return size;
}

sf::RenderWindow&  Window::getRenderWindow() {
	return _window;
}
