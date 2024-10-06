#pragma once

#include <vector>
#include <string>
#include "error.hpp"

namespace numengine
{
    struct sprite_image_data_block
    {
        int relative_x;
        int relative_y;
        int width;
        int height;
        EADK::Color colour;
    };
    
    class behaviour
    {
    public:
        char* name;
        virtual void execute() = 0;
    };

    class sprite
    {
    private:
        std::vector<sprite_image_data_block> image_data;
        std::vector<behaviour*> behaviours;
        
    public:
        sprite(std::vector<sprite_image_data_block> image_data);
        std::vector<sprite_image_data_block> get_image_data() { return image_data; };

        void add_behaviour(behaviour* b);
        void run_behaviour(char* name);
    };
}
