#include "Engine.h"

int main()
{
   // Init Engine
   Engine engine;

    while (engine.isRunning()) {
        // Update
        engine.update();
        // Render
        engine.render();
    }
}
