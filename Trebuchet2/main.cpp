#include <iostream>
#include <list>

#include "game.h"

/* ========================= MUST be done before running! =========================
 * Set working directory: Run -> Edit Configurations... -> set "working directory:" to projects current directory, e.g. "C:\Users\*USERNAME*\trebuchet2\Trebuchet2"
 * Configure SFML (https://goo.gl/1Zmgb2)
 * Configure JSONCPP (https://goo.gl/G9LikB)
 * ========================= Should be done =========================
 * Skim through "sfml_tiled" found here: https://goo.gl/dN8u6b (required login)
 * Skim through "Basic Game Engine" from the SFML devs, found here: https://goo.gl/vbxt5Z
*/

int main() {
    Game game;

    if (!game.init())
    {
        std::cout << "Failed to initialize the game. Quitting." << std::endl;
        return -1;
    }

    game.run();

    return 0;
}