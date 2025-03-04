#include <iostream>
#include "factory.hpp"

using namespace factory;

int main() {
    auto factory = std::make_shared<Factory>();

    auto zone1 = std::make_shared<Zone>();
    auto zone2 = std::make_shared<Zone>();

    auto subZone1 = std::make_shared<Zone>();
    auto subZone2 = std::make_shared<Zone>();

    auto machine1 = std::make_shared<Machine>();
    auto machine2 = std::make_shared<Machine>();

    zone1->addSubZone(subZone1);
    zone2->addSubZone(subZone2);

    subZone1->addMachine(machine1);
    subZone2->addMachine(machine2);

    factory->addZone(zone1);
    factory->addZone(zone2);

    factory->display();
    return 0;
}