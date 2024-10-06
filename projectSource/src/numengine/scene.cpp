#include "scene.hpp"

using namespace numengine;

scene::scene(std::string name, uint32_t bg_colour, unsigned int id) {
    this->name = name;
    this->bg_colour = bg_colour;
    this->id = id;
}

unsigned short scene::register_sprite(sprite* s) {
    unsigned short id = static_cast<unsigned short>(this->sprites.size());
    scene_sprite data = {
        s,
        0, 0,
        1.0f,
        false,
    };
    this->sprites.push_back(data);
    return id;
}

void scene::render() {
    EADK::Display::pushRectUniform(EADK::Screen::Rect, this->bg_colour);

    for (scene_sprite spr : this->sprites) {
        sprite* s = spr.sprite_;
        if (!spr.visible) continue;
        for (sprite_image_data_block block : s->get_image_data()) {
            EADK::Rect rect = EADK::Rect(
                spr.x + block.relative_x,
                spr.y + block.relative_y,
                block.width, block.height
            );
            EADK::Display::pushRectUniform(rect, block.colour);
        }
    }
}
