#pragma once

#include "constants.hpp"

const unsigned int SCREEN_WIDTH = 1366;
const unsigned int SCREEN_HEIGHT = 768;
const char* GAMENAME = "Little Game";
const float PTM_RATIO = 32.0f;
const float WORLD_WIDTH = (float)SCREEN_WIDTH / PTM_RATIO;
const float WORLD_HEIGHT = (float)SCREEN_HEIGHT / PTM_RATIO;
const float TIME_STEP = 1.0f / 60.0f;
extern const int SUB_STEP_COUNT = 4;
// const int VELOCITY_ITERATIONS = 8;
// const int POSITION_ITERATIONS = 3;
extern const float GRAVITY_X = 0.0f;
extern const float GRAVITY_Y = -9.8f;


const PhysicsWorldConfig DEFAULTPHYSCONFIG = {
	GRAVITY_X,
	GRAVITY_Y,
	TIME_STEP,
	SUB_STEP_COUNT
};


/**
 * Common game resolution
 * 16:9
 * 2560x1440
 * 1920x1080
 * 1366x768
 * 1280x720
 * 
 * 16:10
 * 1920x1200
 * 1680x1050
 * 1440x900
 * 1280x800
 * 
 * 4:3
 * 1024x768
 * 800x600
 * 640x480
 */