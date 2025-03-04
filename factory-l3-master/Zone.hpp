#pragma once

#include <memory>
#include <vector>

#include "Machine.hpp"
#include "SpatialElement.hpp"

namespace factory
{
    class Zone : public SpatialElement
    {
    public:
        Zone(const std::string &id) : SpatialElement(id) {}
        void addSubZone(std::shared_ptr<Zone> subZone)
        {
            subZones.push_back(subZone);
        }

        void addMachine(std::shared_ptr<Machine> machine)
        {
            machines.push_back(machine);
        }

        void display() const
        {
            if (subZones.empty())
            {
                std::cout << "Zone avec machines:" << std::endl;
                for (const auto &machine : machines)
                {
                    machine->display();
                }
            }
            else
            {
                std::cout << "Zone avec sub-zones:" << std::endl;
                for (const auto &subZone : subZones)
                {
                    subZone->display();
                }
            }
        }

    private:
        std::vector<std::shared_ptr<Zone>> subZones;
        std::vector<std::shared_ptr<Machine>> machines;
    };
} // namespace factory