#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_PERLIN_IMPLEMENTATION

#include <stb_image.h>
#include <stb_perlin.h>

#include "game.h"

int main() {
    Game& game = Game::getInstance();

    while (game.shouldGameRun()) {
        game.update();
        game.draw();
    }

    return 0;
}