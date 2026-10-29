#include <iostream>
#include <vector>
#include <string>
using namespace std;

class AutomaticSlotAllocation {
private:
    struct Slot {
        int slotNumber;
        string vehicleType;
        string vehicleNumber;
        bool occupied;

        Slot(int number, string type)
            : slotNumber(number),
              vehicleType(type),
              vehicleNumber(""),
              occupied(false) {}
    };

    vector<Slot> slots;

public:
    AutomaticSlotAllocation() {
        slots.emplace_back(1, "Car");
        slots.emplace_back(2, "Car");
        slots.emplace_back(3, "Bike");
        slots.emplace_back(4, "Bike");
        slots.emplace_back(5, "EV");
    }

    bool allocateSlot(string vehicleNumber, string vehicleType) {
        for (auto &slot : slots) {
            if (!slot.occupied &&
                slot.vehicleType == vehicleType) {

                slot.occupied = true;
                slot.vehicleNumber = vehicleNumber;

                cout << "\nSlot allocated successfully!\n";
                cout << "Vehicle Number: " << vehicleNumber << endl;
                cout << "Slot Number: " << slot.slotNumber << endl;
                cout << "Vehicle Type: " << vehicleType << endl;

                return true;
            }
        }

        cout << "\nNo available slot for " << vehicleType << ".\n";
        return false;
    }

    bool releaseSlot(string vehicleNumber) {
        for (auto &slot : slots) {
            if (slot.occupied &&
                slot.vehicleNumber == vehicleNumber) {

                slot.occupied = false;
                slot.vehicleNumber = "";

                cout << "Parking slot released successfully.\n";
                return true;
            }
        }

        cout << "Vehicle not found.\n";
        return false;
    }

    void displaySlots() const {
        cout << "\n--- Parking Slot Status ---\n";

        for (const auto &slot : slots) {
            cout << "Slot " << slot.slotNumber
                 << " (" << slot.vehicleType << "): "
                 << (slot.occupied ? "Occupied" : "Available")
                 << endl;
        }
    }
};
