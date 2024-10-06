#pragma once
#include <string>
#include <vector>

#include "eadk/eadk.hpp"
#include "numengine/sprite.hpp"

namespace numengine
{
    struct scene_sprite {
        sprite* sprite_;
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
        uint32_t bg_colour;
    public:
        scene(std::string name, uint32_t bg_colour, unsigned int id);

        std::vector<scene_sprite> sprites;
        unsigned short register_sprite(sprite* s);

        void render();
    };       
}
