#pragma once
#include "eadk/eadk.hpp"
#include "numengine/numengine.hpp"

class Program
{
public:
    // Gets called once before start.
    void start();
    // Gets called once a frame.
    void update();
};
