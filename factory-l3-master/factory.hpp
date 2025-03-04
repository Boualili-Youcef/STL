#pragma once

#include "Zone.hpp"

namespace factory {

class Factory {
public:
    std::string id;

    void addZone(std::shared_ptr<Zone> zone) {
        zones.push_back(zone);
    }

    void display() const {
        std::cout << "Factory avec zones:" << std::endl;
        for (const auto& zone : zones) {
            zone->display();
        }
    }


private:
    std::vector<std::shared_ptr<Zone>> zones;
};



} // namespace factory