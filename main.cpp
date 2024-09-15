#include<iostream>
#include "Game.h"

using namespace std;

int main() {

    try {
        Game game; // Create the game object
        game.run(); // Start the game loop
    }
    catch (const std::exception& e) {
        // Handle any exceptions thrown during game initialization or execution
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Return an error code
    }


    return 0;
}
