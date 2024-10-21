#include "../include/window.hpp"

int main()
{
    // init window
    Window window;
    
    while (!window.isDone()) {
        // clear the frame
        window.Clear();
        // handle events: 'F5', 'esc' and 'close'
        window.Update();
        // display the window
        window.Display();
    }
}
