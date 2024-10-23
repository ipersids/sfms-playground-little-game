#include "../include/window.hpp"
#include "../include/game.hpp"

int main()
{
    Game game;
    const float targetFrameTime = 1.0f / 50.0f;
    
    while (!game.GetWindow()->isDone()) {
        game.HandleInput();
        game.RestartClock();
        if (game.GetElapsed().asSeconds() < targetFrameTime) {
            sf::sleep(sf::seconds(targetFrameTime - game.GetElapsed().asSeconds()));
        }
        game.Update();
        game.Render();
    }

    return 0;
}
