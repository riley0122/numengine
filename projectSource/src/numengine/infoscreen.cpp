#include "infoscreen.hpp"

void numengine::showInfoScreen() {
    EADK::Display::pushRectUniform(EADK::Screen::Rect, Indigo);
    
    int infoPoints = 0;
#ifndef numengine_version
    EADK::Display::drawString("Running unknown numengine version", EADK::Point(0, infoPoints*15), false, White, Indigo);
#else
    EADK::Display::drawString("Running numengine v" + numengine_version, EADK::Point(0, infoPoints*15), false, White, Indigo);
#endif
    ++infoPoints;

    EADK::Display::drawString("https://github.com/riley0122/numengine", EADK::Point(0, infoPoints*15), false, White, Indigo);
    ++infoPoints;

    EADK::Display::drawString("No further info.", EADK::Point(0, infoPoints*15), false, White, Indigo);
}