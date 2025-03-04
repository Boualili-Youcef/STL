#include <iostream>
#include <vector>
#include <memory>

namespace factory {

class Machine {
public:
    void display() const {
        std::cout << "Machine" << std::endl;
    }
};

class Zone {
public:
    void addSubZone(std::shared_ptr<Zone> subZone) {
        subZones.push_back(subZone);
    }

    void addMachine(std::shared_ptr<Machine> machine) {
        machines.push_back(machine);
    }

    void display() const {
        if (subZones.empty()) {
            std::cout << "Zone with machines:" << std::endl;
            for (const auto& machine : machines) {
                machine->display();
            }
        } else {
            std::cout << "Zone with sub-zones:" << std::endl;
            for (const auto& subZone : subZones) {
                subZone->display();
            }
        }
    }

private:
    std::vector<std::shared_ptr<Zone>> subZones;
    std::vector<std::shared_ptr<Machine>> machines;
};

class Factory {
public:
    void addZone(std::shared_ptr<Zone> zone) {
        zones.push_back(zone);
    }

    void display() const {
        std::cout << "Factory with zones:" << std::endl;
        for (const auto& zone : zones) {
            zone->display();
        }
    }

private:
    std::vector<std::shared_ptr<Zone>> zones;
};

std::ostream& operator<<(std::ostream& os, const Factory& factory) {
    factory.display();
    return os;
}

} // namespace factory