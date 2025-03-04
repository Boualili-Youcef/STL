#pragma once

#include "Coordinates.hpp"

namespace factory
{

    class Cell : public Coordinates
    {
    public:
        int x;
        int y;
        ~Cell() = default;
    };

} // namespace factory