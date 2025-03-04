#pragma once

#include "Coordinates.hpp"

namespace factory
{

    class Point : public Coordinates
    {
    public:
        int x;
        int y;
        ~Point() = default;
    };

} // namespace factory