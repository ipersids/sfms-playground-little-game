#include "physic-world.hpp"
#include "constants.hpp"

using namespace GameCore;

PhysicsWorld::~PhysicsWorld() {
	if (b2World_IsValid(_world)) {
		b2DestroyWorld(_world);
	}
}

PhysicsWorld::PhysicsWorld(const PhysicsWorldConfig& config) : _world({0}), _config(config) {
	createWorld(_config.gravityX, _config.gravityY);
}

// This is a method of the PhysicsWorld class that takes two parameters 
// to define gravity direction and strength. This setup creates a standard 
// 2D physics simulation environment with realistic gravity 
// and common optimizations enabled.
void PhysicsWorld::createWorld(float gravityX=0, float gravityY=-9.8) {
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = (b2Vec2){gravityX, gravityY};
	worldDef.enableSleep = true;
	worldDef.enableContinuous = true;
	_world = b2CreateWorld(&worldDef);
	if (!b2World_IsValid(_world)) {
		throw std::runtime_error("Failed to create physics world");
	}
}

void PhysicsWorld::step() {
	b2World_Step(_world, _config.timeStep, _config.subStepCount);
}

const b2WorldId* PhysicsWorld::getWorldId() const {
	return &(_world);
}

const PhysicsWorldConfig* PhysicsWorld::getPhysicsWorldConfig() const {
	return &(_config);
}
