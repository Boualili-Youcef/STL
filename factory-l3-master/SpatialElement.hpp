#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Geometry.hpp"
#include <iostream>

namespace factory
{
    class SpatialElement
    {
    public:
        SpatialElement(const std::string &id) : id(id) {}
        void setGeometry(std::unique_ptr<Geometry> geom) // pas de const & car on veut le deplacer
        {
            geometry = std::move(geom);
        }
        virtual ~SpatialElement() = default;

    private:
        std::string id;
        std::unique_ptr<Geometry> geometry; // car la spatial element peut avoir 0 ou 1 seul geometry d'ou le unique_ptr
    };
} // namespace factory