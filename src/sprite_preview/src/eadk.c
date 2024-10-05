// This file is just to please the compiler
#pragma once

#include "eadk/eadk.h"

void eadk_display_push_rect_uniform(eadk_rect_t rect, eadk_color_t color){
    return;
}

void eadk_display_draw_string(const char *text, eadk_point_t point, bool large_font, eadk_color_t text_color, eadk_color_t background_color) {
    return;
}

eadk_keyboard_state_t eadk_keyboard_scan() {
    return 0;
}