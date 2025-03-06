#pragma once

#include "SpatialElement.hpp"

namespace factory
{
    class Machine : public SpatialElement
    {
    public:
        Machine(const std::string &id) : SpatialElement(id) {} // Add constructor
        int setup_time;
        int process_time;
        void display() const 
        {
            std::cout << "Machinfe" << std::endl;
        }
        ~Machine() = default;
    };

} // namespace factory
