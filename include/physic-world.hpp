#pragma once

#include "constants.hpp"

namespace GameCore {

class PhysicsWorld {
	public:
		explicit PhysicsWorld(const PhysicsWorldConfig& config = DEFAULTPHYSCONFIG);
		~PhysicsWorld();

		// Prevent accidental copying
		PhysicsWorld(const PhysicsWorld&) = delete;
		PhysicsWorld& operator=(const PhysicsWorld&) = delete;

		void step();
		const b2WorldId* getWorldId() const;
		const PhysicsWorldConfig* getPhysicsWorldConfig() const;

	private:
		b2WorldId _world;
		PhysicsWorldConfig _config;
		void createWorld(float gravityX, float gravityY);
};

} // namespace GameCore
