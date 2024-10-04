#include "eadk/eadk.hpp"
#include "meta/display.h"
#include "meta/eadk_vars.hpp"
#include "palette.hpp"
#include "game/code.hpp"

int main(int argc, char *argv[]) {
    EADK::Display::pushRectUniform(EADK::Screen::Rect, Indigo);

    EADK::Display::drawString("Started succesfully!", EADK::Point(0,0), true, White, Indigo);
    EADK::Display::drawString("However there is no active scene.", EADK::Point(0, 20), false, White, Indigo);

    bool running = true;
    bool homePressed = false;

    Program game = Program();

    game.start();

    const int frameDuration = 1000 / 30;

    while (running) {
        game.update();
        EADK::Keyboard::State kbdState = EADK::Keyboard::scan();

        if (kbdState.keyDown(EADK::Keyboard::Key::Home)) {
            homePressed = true;
        } else if (homePressed) {
            running = false;
        }

        game.update();
        // TODO: re-render.

        EADK::Timing::msleep(frameDuration);
    }

    return 0;
}