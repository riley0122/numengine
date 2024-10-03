#pragma once
#include <string>

namespace numengine
{
    class scene
    {
    private:
        std::string name;
        unsigned int id;
    public:
        scene(std::string name, unsigned int id);
    };       
}
