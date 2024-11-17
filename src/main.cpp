#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#include "window.hpp"
#include "constants.hpp"

using json = nlohmann::json;

int main() {
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string RESET = "\033[0m";

    auto window = std::make_unique<GameCore::Window>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "JSON test");

    std::ifstream jsonFile("assets/test.json");
    if (!jsonFile.is_open()) {
        std::cerr << "Could not open 'assets/test.json' file." << std::endl;
        return -1;
    }

    json jsonConfig;
    try {
        jsonFile >> jsonConfig;
    } catch (const json::parse_error& er) {
        std::cerr << "JSON parser error: " << er.what() << std::endl;
        return -2;
    }

    jsonFile.close();
    
    sf::Sprite staticBackgroundSprite;
    sf::Texture staticBackgroundTexture;
    sf::Sprite staticItemSprite;
    sf::Texture staticItemTexture;
    sf::Sprite staticGroundSprite;
    sf::Texture staticGroundTexture;
    if (jsonConfig.contains("level 1")) {

        // STATIC OBJECTS >>>
        json data = jsonConfig["level 1"]["static"];
        std::cout << "Data to load: " << data[0].dump(4) << "\n ... " << std::endl;

        for (const auto& el : data) {
            if (el.contains("name") && el["name"] == "background") {
                if (el.contains("texture_path") && el.contains("width") && el.contains("height")) {
                    if(!staticBackgroundTexture.loadFromFile(el["texture_path"])) {
                        std::cerr << "Loading from '" << el["texture_path"] << "' " << RED << "fails." << RESET << std::endl;
                        return -3;
                    }
                    staticBackgroundSprite.setTexture(staticBackgroundTexture); // ? check if setting texture fails ?
                    int width = el["width"].get<int>();
                    int height = el["height"].get<int>();
                    float scaleX = static_cast<float>(SCREEN_WIDTH) / width;
                    float scaleY = static_cast<float>(SCREEN_HEIGHT) / height;
                    float scale = std::max(scaleX, scaleY);
                    staticBackgroundSprite.setScale(scale, scale);
                    staticBackgroundSprite.setPosition((SCREEN_WIDTH - width * scale) / 2, (SCREEN_HEIGHT - height * scale) / 2);
                    std::cout << "\t- " << GREEN << "DONE:" << RESET << " " << el["name"] << " is downloaded (" << el["texture_path"] << ")." << std::endl;
                }
            } else if (el.contains("name") && el["name"] == "item") {
                if (el.contains("texture_path") && el.contains("width") && el.contains("height")) {
                    if (!staticItemTexture.loadFromFile(el["texture_path"])) {
                        std::cerr << "Loading from '" << el["texture_path"] << "' " << RED << "fails." << RESET << std::endl;
                        return -4;
                    }
                    staticItemSprite.setTexture(staticItemTexture);
                    int x = el["x"].get<int>();
                    int y = el["y"].get<int>();
                    staticItemSprite.setPosition(x, y);
                    std::cout << "\t- " << GREEN << "DONE:" << RESET << " " << el["name"] << " is downloaded (" << el["texture_path"] << ")." << std::endl;
                }
            } else if (el.contains("name") && el["name"] == "ground") {
                if (el.contains("texture_path") && el.contains("width") && el.contains("height")) {
                    if (!staticGroundTexture.loadFromFile(el["texture_path"])) {
                        std::cerr << "Loading from '" << el["texture_path"] << "' " << RED << "fails." << RESET << std::endl;
                        return -4;
                    }
                    int sizeGround = el["width"].get<int>();
                    staticGroundTexture.setRepeated(true);
                    staticGroundSprite.setTexture(staticGroundTexture);
                    staticGroundSprite.setTextureRect(sf::IntRect(0, 0, SCREEN_WIDTH, sizeGround));
                    staticGroundSprite.setPosition(0, SCREEN_HEIGHT - sizeGround);
                    std::cout << "\t- " << GREEN << "DONE:" << RESET << " " << el["name"] << " is downloaded (" << el["texture_path"] << ")." << std::endl;
                }
            } else {
                std::cerr << "\t- " << RED << "ERROR:" << RESET << " " << el["name"] << " isn't downloaded: missing required fields." << std::endl;
            }
            // STATIC OBJECTS <<<
        }
    }

    sf::Event event;
    while (window->getStatus())
    {
        while (window->getRenderWindow().pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window->setStatus(false);
                    break;

                default:
                    break;
            }
        }

        window->startDraw();
        window->draw(staticBackgroundSprite);
        window->draw(staticItemSprite);
        window->draw(staticGroundSprite);
        window->endDraw();
    }

    return 0;
}
