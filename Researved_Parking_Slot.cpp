#include <iostream>
#include <vector>
#include <string>
using namespace std;

class ReservedParkingSlot {
private:
    struct Reservation {
        int slotNumber;
        string vehicleNumber;
    };

    vector<Reservation> reservations;

    bool isValidSlot(int slotNumber) const {
        return slotNumber >= 1 && slotNumber <= 5;
    }

public:
    bool reserveSlot(int slotNumber, string vehicleNumber) {
        if (!isValidSlot(slotNumber)) {
            cout << "Invalid slot number.\n";
            return false;
        }

        for (const auto &reservation : reservations) {
            if (reservation.slotNumber == slotNumber) {
                cout << "Slot is already reserved.\n";
                return false;
            }
        }

        reservations.push_back({slotNumber, vehicleNumber});

        cout << "\nReservation successful!\n";
        cout << "Vehicle Number: " << vehicleNumber << endl;
        cout << "Reserved Slot: " << slotNumber << endl;

        return true;
    }

    bool cancelReservation(int slotNumber) {
        for (auto it = reservations.begin();
             it != reservations.end(); ++it) {

            if (it->slotNumber == slotNumber) {
                reservations.erase(it);

                cout << "Reservation cancelled successfully.\n";
                return true;
            }
        }

        cout << "Reservation not found.\n";
        return false;
    }

    void displayReservations() const {
        cout << "\n--- Reserved Parking Slots ---\n";

        if (reservations.empty()) {
            cout << "No active reservations.\n";
            return;
        }

        for (const auto &reservation : reservations) {
            cout << "Slot Number: "
                 << reservation.slotNumber << endl;

            cout << "Vehicle Number: "
                 << reservation.vehicleNumber << endl;

            cout << "------------------------\n";
        }
    }
};
