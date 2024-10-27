# SFML and Box2D playground
## Little Game
This repository is my space to explore the features of [SFML (Simple and Fast Multimedia Library)](https://www.sfml-dev.org/index.php), a library used for the development of games and multimedia applications, and [Box2D physics engine for games](https://box2d.org/documentation/index.html).


## Project Structure
Below is an overview of the project's directory structure. The project is currently ongoing, and this information will be updated as development progresses.  

```css
sfml-playground/
│
├── build/                      # Build output dir will be created via CMake
│   ├── _deps/                  # External dependencies: SFML, Box2D
│   ├── ...                     # Any build-related files
│   └── bin/main                # Compiled executable
│
├── include/                    # Header files
│   ├── game.hpp 
│   ├── ... 
│   └── window.hpp          
│
├── src/                        # Source files
│   ├── core/ 
│   │    ├── game.cpp
│   │    ├── physic-world.cpp
│   │    ├── physic-object.cpp
│   │    └── window.cpp
│   ├── constants.cpp
│   └── main.cpp 
│
├── assets/                     # Images
├── CMakeLists.txt              # CMake configuration file for building the project
├── LICENSE.md
├── README.md
├── .gitignore
│
├── .github/workflows/          # CI/CD configuration for GitHub Actions
│   └── ci.yml
│
├── .vscode/                    # VS Code configuration files
│   ├── c_cpp_properties.json   # VS Code settings for C/C++ compilers
│   ├── launch.json             # Debugger configuration for VS Code
│   └── tasks.json              # Task automation for build/run commands
└── little-game.code-workspace  # VS Code workspace configuration file

```

## Where to start
### Installation
1. **Clone the repository:**
```bash
git clone https://github.com/ipersids/sfms-playground-little-game.git
```
2. **Build the project:**
    - Make sure you have `CMake` and a C++ compiler installed.
    - Cmake will fetch dependencies: SFML and Box2D libraries.
    - Configure the build:

    ```bash
    cmake -S . -B build
    ``` 
    - Compile the code:
    ```bash
    cmake --build build
    ```
    <details>
    <summary>Workspace Setup</summary>

    The repository includes a pre-configured [VS Code workspace](https://code.visualstudio.com/docs/editor/workspaces):  

    - *Compiler settings for C++ project* `c_cpp_properties.json`.   

    - *Build automation:* `tasks.json`.  
    `VS Code -> Terminal -> Run Task.. -> <list of tasks>`

    - *Debugging setup:* `launch.json`.  
    `VS Code -> Run and Debug -> (lldb)/(gdb) Launch -> Start Debugging`  
    <p></p>  
    <b>To get started with the workspace:</b>

    - Open the `.code-workspace` file in VS Code.
    - Ensure you have installed the necessary extensions for C++ development (C/C++, CMake Tools).
    - Use the integrated terminal and task runner for building and debugging.

    </details>  
<p></p>

3. **The resulting executable** will be placed in the `build/bin/` directory.

### Architecture

<details>  

<summary><b>Game Core Module</b></summary>

```mermaid
classDiagram
direction 
direction RL
namespace GameCore {
    class Game {
        +Game()
        +Game(std::unique_ptr<Window> window, std::unique_ptr<PhysicsWorld> world)
        +~Game()
        +loadObject(const PhysicsBodyConfig& config) void 
        +loadObject(std::unique_ptr<PhysicObject> object) void 
        +run() void 
        +getWorldId() const std::unique_ptr<PhysicsWorld> 

        -std::unique_ptr<Window> _window
		-std::unique_ptr<PhysicsWorld> _physicsWorld
		-std::vector<std::unique_ptr<PhysicObject>> _characters

		-update() void 
		-render() void 
		-processEvents() void 
    }
    class Window {
        +Window(...)
        +~Window()
        +startDraw() void
		+draw(sf::Drawable& drawable) void
		+endDraw() void
		+closeWindow() void
        +getStatus() bool 
		+setStatus(bool isopen) void 
		+GetWindowSize() sf::Vector2u 
		+getRenderWindow() sf::RenderWindow& 

        -sf::RenderWindow _window
		-bool _isOpen
    }
    class PhysicObject {
        +PhysicObject(const b2WorldId& world, const PhysicsBodyConfig& config)
		+~PhysicObject()
		+update() void 
		+draw(sf::RenderWindow& window) void 
		+getSprite() sf::Sprite&
        
		-b2BodyId _body
		-sf::Sprite _sprite
		-sf::Texture _texture
    }
    class PhysicsWorld {
        +PhysicsWorld(const PhysicsWorldConfig& config = DEFAULTPHYSCONFIG)
		+~PhysicsWorld()
		+step() void
		+getWorldId() const b2WorldId* 
		+getPhysicsWorldConfig() const PhysicsWorldConfig* 

        -b2WorldId _world
		-PhysicsWorldConfig _config
		-createWorld(float gravityX, float gravityY) void 
    }
}
```

</details>

____
Made by Julia Persidskaia  
[LinkedIn](https://www.linkedin.com/in/iuliia-persidskaia/)