#pragma once
#include <string>

#include "eadk/eadk.hpp"
#include "numengine/sprite.hpp"

namespace numengine
{
    struct scene_sprite {
        sprite* sprite;
        unsigned int x;
        unsigned int y;
        float scale;
        bool visible;
    };

    class scene
    {
    private:
        std::string name;
        unsigned int id;
        EADK::Color bg_colour;
    public:
        scene(std::string name, EADK::Color bg_colour, unsigned int id);

        std::vector<scene_sprite> sprites;
        unsigned short register_sprite(sprite* s);

        void render();
    };       
}
