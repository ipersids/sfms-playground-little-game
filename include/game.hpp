#pragma once

#include <vector>
#include <memory>
#include <iostream>

// #include <SFML/Window.hpp>

#include "window.hpp"
#include "physic-world.hpp"
#include "physic-object.hpp"
#include "constants.hpp"

namespace GameCore {

class Game {
	public:
		Game();
		Game(std::unique_ptr<Window> window, std::unique_ptr<PhysicsWorld> world);
		~Game();

		// Prevent copying
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		void loadObject(const PhysicsBodyConfig& config);
		void loadObject(std::unique_ptr<PhysicObject> object);
		void run();
		const std::unique_ptr<PhysicsWorld> getWorldId() const;

	private:
		std::unique_ptr<Window> _window;
		std::unique_ptr<PhysicsWorld> _physicsWorld;
		std::vector<std::unique_ptr<PhysicObject>> _characters;

		void update();
		void render();
		void processEvents();
};

} // namespace GameCore
