#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

// Screen dimensions
extern const unsigned int SCREEN_WIDTH;
extern const unsigned int SCREEN_HEIGHT;
// Window title
extern const char* GAMENAME;
// Standard scale (32 pixels = 1 meter is common in Box2D)
extern const float PTM_RATIO;
// Calculate world dimensions in meters
extern const float WORLD_WIDTH;
extern const float WORLD_HEIGHT;
// Update bodies in the Box2D world
extern const float GRAVITY_X;
extern const float GRAVITY_Y;
extern const float TIME_STEP;
extern const int SUB_STEP_COUNT;
// extern const int VELOCITY_ITERATIONS;
// extern const int POSITION_ITERATIONS;

struct PhysicsWorldConfig {
  float gravityX;
  float gravityY;
	float timeStep;
	int		subStepCount;
};

struct PhysicsBodyConfig {
	sf::Texture texture;
	b2BodyType type;
	b2Vec2 position;
	float density;
	float friction;
	bool iscircle;
};

extern const PhysicsWorldConfig DEFAULTPHYSCONFIG;