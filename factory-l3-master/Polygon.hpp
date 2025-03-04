#pragma once

#include "Geometry.hpp"

namespace factory
{
    class Polygon : public Geometry
    {
        void addPoint(const std::shared_ptr<Geometry> &point)
        {
            points.push_back(point);
        }
        ~Polygon() = default;

    private:
        std::vector<std::shared_ptr<Geometry>> points;
    };
} // namespace factory