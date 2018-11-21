#include <iostream>
#include <list>

#include "game.h"

/* ============================== MUST be Done before Running! ==============================
 * Configure SFML (https://goo.gl/1Zmgb2)
 * Configure JSONCPP (https://goo.gl/G9LikB)
 * * Set working directory: Run -> Edit Configurations... -> set "working directory:" to projects current directory, e.g. "C:\Users\*USERNAME*\trebuchet2\Trebuchet2"
 *
 * ============================== Should be Done Before Running ==============================
 * Skim through "sfml_tiled" found here: https://goo.gl/dN8u6b (login required)
 * Skim through "Basic Game Engine" from the SFML devs, found here: https://goo.gl/vbxt5Z
 *
 * ============================== Documentation and Help ==============================
 * https://github.com/SFML/SFML (Wiki)
 * https://www.sfml-dev.org/
 * https://github.com/open-source-parsers/jsoncpp
 *
 *
 * PROJECT TREBUCHET 2: TITLE IN PROGRESS
 * CREATED BY:
 * Hassan Mohammed Ali
 * Håvard Friborg
 * Aleksander Lingstad
 * Vebjørn Meinseth
 * Abdelraouf Tria
 */

int main() {
    Game game;

    if (!game.init()) {
        std::cout << "Failed to initialize the game. Quitting." << std::endl;
        return -1;
    }

    game.run();

    return 0;
}