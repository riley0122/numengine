#include "error.hpp"

using namespace numengine;

void numengine::error(char* error) {
    EADK::Display::pushRectUniform(EADK::Screen::Rect, Red);
    EADK::Display::drawString("An error occurred!", EADK::Point(0,0), true, White, Red);
    EADK::Display::drawString(error, EADK::Point(0,30), false, White, Red);
    EADK::Display::drawString("Press 'ok' to exit", EADK::Point(0,EADK::Screen::Height - 20), false, White, Red);
    bool hang = true;
    while (hang)
    {
        EADK::Keyboard::State kbdState = EADK::Keyboard::scan();
        hang = !kbdState.keyDown(EADK::Keyboard::Key::OK);
    }
}
