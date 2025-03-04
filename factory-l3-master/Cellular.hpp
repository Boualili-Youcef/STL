#pragma once

#include "Geometry.hpp"

namespace factory
{

    class Cellular : public Geometry
    {
    public:
        int width;
        int height;
        void addCell(const std::shared_ptr<Geometry>& cell)
        {
            cells.push_back(cell);
        }
        ~Cellular() = default;	
    private:
        std::vector<std::shared_ptr<Geometry>> cells;
    };
} // namespace factory