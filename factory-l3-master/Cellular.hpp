#pragma once

#include "Geometry.hpp"

namespace factory
{

    class Cellular : public Geometry
    {
    private:
        int width;
        int height;
    };
} // namespace factory