#include "eadk/eadk.hpp"
#include "meta/display.h"
#include "meta/eadk_vars.hpp"
#include "palette.hpp"

int main(int argc, char *argv[]) {
    EADK::Display::pushRectUniform(EADK::Screen::Rect, Indigo);

    EADK::Display::drawString("Started succesfully!", EADK::Point(0,0), true, White, Indigo);
    EADK::Display::drawString("However there is no active scene.", EADK::Point(0, 20), false, White, Indigo);

    int running = 1;

    do {
        EADK::Keyboard::State kbdState = EADK::Keyboard::scan();
        running = !kbdState.keyDown(EADK::Keyboard::Key::Home);
    } while (running);
}