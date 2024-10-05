#include "sprite.hpp"

using namespace numengine;

numengine::sprite::sprite(std::vector<sprite_image_data_block> image_data)
{

}

void numengine::sprite::run_behaviour(char *name)
{
    for (auto* b : behaviours)
    {
        if (b->name == name) {
            b->execute();
            return;
        }
    }
    char *buffer = (char*)malloc(sizeof(char) * 26 + sizeof(name));
    sprintf(buffer, "Behaviour '%s' doesn't exist", name);
    error(buffer);
}
