#include "physic-object.hpp"
#include <iostream>

using namespace GameCore;

PhysicObject::~PhysicObject() {
	if (b2Body_IsValid(_body)) {
		b2DestroyBody(_body);
	}
}

PhysicObject::PhysicObject(const b2WorldId& world, const PhysicsBodyConfig& config) {
	if (!_texture.loadFromFile(config.texturePath)) {
    std::cerr << "Failed to load circle texture!" << std::endl;
  }
	// Body definition
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = config.type;
	bodyDef.position = config.position;
	// Create the body
	_body = b2CreateBody(world, &bodyDef);

	if (!b2Body_IsValid(_body)) {
		throw std::runtime_error("Failed to create physics body");
	}

	// Shape definition
	b2ShapeDef bodyShapeDef = b2DefaultShapeDef();
	bodyShapeDef.density = config.density;
	bodyShapeDef.friction = config.friction;
	// Create the shape (fixture)
	float width = (_texture.getSize().x / 2.0f);
	float height = (_texture.getSize().y / 2.0f);

	b2ShapeId shapeId = {0};
	if (config.iscircle) {
		b2Circle bodyCircle;
		bodyCircle.center = (b2Vec2){0.0f, 0.0f};
		bodyCircle.radius = width / PTM_RATIO;
		shapeId = b2CreateCircleShape(_body, &bodyShapeDef, &bodyCircle);
	} else {
		b2Polygon bodyBox = b2MakeBox(width / PTM_RATIO, height / PTM_RATIO);
		shapeId = b2CreatePolygonShape(_body, &bodyShapeDef, &bodyBox);
	}

	if (!b2Shape_IsValid(shapeId)) {
		b2DestroyBody(_body);
		throw std::runtime_error("Failed to create shape");
	}

  _sprite.setTexture(_texture);
  _sprite.setOrigin(width, height);

  // Make sprite clearly visible for debugging
  _sprite.setColor(sf::Color(204, 204, 255));
  
  // Set initial position
  float screenX = config.position.x * PTM_RATIO;
  float screenY = config.position.y * PTM_RATIO;
  _sprite.setPosition(screenX, screenY);
    
  std::cout << "Sprite created at position: " << screenX << ", " << screenY << std::endl;
}

void PhysicObject::update() {
	b2Vec2 position = b2Body_GetPosition(_body);
	float angle = b2Rot_GetAngle(b2Body_GetRotation(_body));
	_sprite.setPosition(position.x * PTM_RATIO, position.y * PTM_RATIO);
	_sprite.setRotation(angle * 180 / b2_pi);
}

void PhysicObject::draw(sf::RenderWindow& window) {
	window.draw(_sprite);

	// DEBUGGING
	// Create debug shape at the same position as sprite
	sf::CircleShape debugShape(10.f);
	debugShape.setFillColor(sf::Color::Red);
	sf::Vector2f spritePos = _sprite.getPosition();
	debugShape.setPosition(spritePos.x, spritePos.y);
	window.draw(debugShape);
}

sf::Sprite& PhysicObject::getSprite() {
	return _sprite;
}
