#pragma once

#include "constants.hpp"

namespace GameCore {

class PhysicObject {
	public:
		explicit PhysicObject(const b2WorldId& world, const PhysicsBodyConfig& config);
		~PhysicObject();

		// Prevent accidental copying
		PhysicObject(const PhysicObject&) = delete;
		PhysicObject& operator=(const PhysicObject&) = delete;

		void update();
		void draw(sf::RenderWindow& window);
		sf::Sprite& getSprite();

	private:
		b2BodyId _body;
		sf::Sprite _sprite;
		sf::Texture _texture;
};

} // namespace GameCore
