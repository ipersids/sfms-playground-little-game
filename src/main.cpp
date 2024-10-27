#include "window.hpp"
#include "game.hpp"
#include "physic-world.hpp"
#include "physic-object.hpp"
#include "constants.hpp"

int main() {
    PhysicsWorldConfig worldConfig = {
        0.0f,
        9.8f,
        1.0f/60.0f,
        8
    };

    auto window = std::make_unique<GameCore::Window>(sf::VideoMode(1366, 768), "Physics Test");
    auto world = std::make_unique<GameCore::PhysicsWorld>(worldConfig);

    GameCore::Game game(std::move(window), std::move(world));

    std::string circleTexture = "assets/circle.png";
    std::string groundTexture = "assets/test-ground.png";
    
    // static body - positioned near bottom of screen
    game.loadObject({
        groundTexture,
        b2_staticBody,
        {700 / PTM_RATIO, 763 / PTM_RATIO},
        1.0f,
        0.3f,
        false
    });

    // dynamic body - starting from top-center
    game.loadObject({
        circleTexture,
        b2_dynamicBody,
        {683.0f / PTM_RATIO, 100.0f / PTM_RATIO}, // Centered horizontally, near top
        1.0f,
        0.3f,
        true 
    });

    // dynamic body - starting from top-left
    game.loadObject({
        circleTexture,
        b2_dynamicBody,
        {400.0f / PTM_RATIO, 50.0f / PTM_RATIO},
        1.0f,
        0.3f,
        true
    });

    // dynamic body - starting from top-right
    game.loadObject({
        circleTexture,
        b2_dynamicBody,
        {966.0f / PTM_RATIO, 50.0f / PTM_RATIO},
        1.0f,
        0.3f,
        true
    });

    game.run();
    return 0;
}
