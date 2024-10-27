#include "game.hpp"

using namespace GameCore;

Game::Game() : _window(std::make_unique<Window>()),
							 _physicsWorld(std::make_unique<PhysicsWorld>()) {
}

Game::Game(std::unique_ptr<Window> window,
					 std::unique_ptr<PhysicsWorld> world) 
					 : _window(std::move(window)),
					 	 _physicsWorld(std::move(world)) {
}

Game::~Game() {
	_characters.clear();
}

void Game::loadObject(const PhysicsBodyConfig& config) {
	try {
		auto character = std::make_unique<PhysicObject>(*_physicsWorld->getWorldId(), config);
		_characters.push_back(std::move(character));
		std::cout << "Added new object. Total objects: " << _characters.size() << std::endl;
	} catch (const std::runtime_error& e) {
		std::cerr << "Failed to load physics object: " << e.what() << std::endl; 
	}
}

void Game::loadObject(std::unique_ptr<PhysicObject> object) {
	_characters.push_back(std::move(object));
}

void Game::run() {
  while (_window->getStatus()) {
    processEvents();
    update();
    render();

		// TODO: implement timer to run 60fps
    sf::sleep(sf::milliseconds(3));
  }
}

void Game::update() {
	_physicsWorld->step();
	for (auto& obj : _characters) {
		obj->update();
	}
}

void Game::render() {
  _window->startDraw();

  for (auto& obj : _characters) {
		obj->draw(_window->getRenderWindow());
  }

  _window->endDraw();
}

void Game::processEvents() {
	sf::Event event;
	while (_window->getRenderWindow().pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				_window->setStatus(false);
				break;

			default:
				break;
		}
	}
};
