#include <iostream>
#include <memory>

#include <iostream>
#include <memory>
#include "factory.hpp"
#include "Polygon.hpp"
#include "Cellular.hpp"

using namespace factory;

int main() {
    // 1. Create a Factory
    auto factory = std::make_shared<Factory>();

    // 2. Create Zones
    auto zone1 = std::make_shared<Zone>("Zone1"); // Provide an ID
    auto zone2 = std::make_shared<Zone>("Zone2"); // Provide an ID

    // 3. Create Subzones
    auto subZone1 = std::make_shared<Zone>("SubZone1"); // Provide an ID
    auto subZone2 = std::make_shared<Zone>("SubZone2"); // Provide an ID

    // 4. Create Machines
    auto machine1 = std::make_shared<Machine>("Machine1"); // Provide an ID
    auto machine2 = std::make_shared<Machine>("Machine2"); // Provide an ID

    // 5. Create Geometries
    auto polygon1 = std::make_unique<Polygon>();
    auto cellular1 = std::make_unique<Cellular>();

    // 6. Set Geometries for Zones
    zone1->setGeometry(std::move(polygon1));   // Zone1 has a Polygon geometry
    subZone2->setGeometry(std::move(cellular1)); // SubZone2 has a Cellular geometry

    // 7. Build the Factory Structure
    zone1->addSubZone(subZone1);
    zone2->addSubZone(subZone2);

    subZone1->addMachine(machine1);
    subZone2->addMachine(machine2);

    factory->addZone(zone1);
    factory->addZone(zone2);

    factory->display();

    return 0;
}