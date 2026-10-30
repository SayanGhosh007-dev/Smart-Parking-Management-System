#include <cctype>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Category {
private:
    int id;
    string name;
    float rate;
    float height;
    float width;

public:
    Category(int categoryId, const string& categoryName, float hourlyRate,
             float maxHeight, float maxWidth)
        : id(categoryId), name(categoryName), rate(hourlyRate),
          height(maxHeight), width(maxWidth) {}

    void display() const {
        cout << "ID: " << id << " | Name: " << name
             << " | Rate: " << rate
             << " | Height: " << height
             << " | Width: " << width << endl;
    }
};

class Vehicle {
private:
    string number;
    string type;
    string owner;
    string phone;
    string fastag;

public:
    Vehicle(const string& vehicleNumber, const string& vehicleType,
            const string& ownerName, const string& mobileNumber,
            const string& fastagId)
        : number(vehicleNumber), type(vehicleType), owner(ownerName),
          phone(mobileNumber), fastag(fastagId) {}

    const string& getNumber() const {
        return number;
    }

    void display() const {
        cout << "Number: " << number
             << " | Type: " << type
             << " | Owner: " << owner
             << " | Phone: " << phone
             << " | FASTag: " << fastag << endl;
    }
};

class Slot {
private:
    int id;
    int floor;
    string type;
    float size;
    bool occupied;
    bool reserved;

public:
    Slot(int slotId, int floorNumber, const string& slotType, float slotSize)
        : id(slotId), floor(floorNumber), type(slotType), size(slotSize),
          occupied(false), reserved(false) {}

    int getId() const {
        return id;
    }

    bool isAvailable() const {
        return !occupied && !reserved;
    }

    bool isOccupied() const {
        return occupied;
    }

    void occupy() {
        occupied = true;
    }

    void release() {
        occupied = false;
    }

    void display() const {
        cout << "ID: " << id << " | Floor: " << floor
             << " | Type: " << type << " | Size: " << size
             << " | Occupied: " << (occupied ? "Yes" : "No")
             << " | Reserved: " << (reserved ? "Yes" : "No") << endl;
    }
};

class Allocation {
private:
    int id;
    string vehicleNumber;
    int slotId;
    time_t entry;
    time_t exit;
    string status;

public:
    Allocation(int allocationId, const string& number, int allocatedSlotId)
        : id(allocationId), vehicleNumber(number), slotId(allocatedSlotId),
          entry(time(nullptr)), exit(0), status("ALLOCATED") {}

    int getId() const {
        return id;
    }

    int getSlotId() const {
        return slotId;
    }

    const string& getVehicleNumber() const {
        return vehicleNumber;
    }

    bool isActive() const {
        return status == "ALLOCATED";
    }

    void release() {
        exit = time(nullptr);
        status = "RELEASED";
    }
};

class ParkingSlotAndVehicleCategoryManagement {
private:
    vector<Category> categories;
    vector<Vehicle> vehicles;
    vector<Slot> slots;
    vector<Allocation> allocations;

    bool validNumber(const string& number) const {
        if (number.length() != 10) {
            return false;
        }

        for (size_t i = 0; i < number.length(); ++i) {
            if (i < 2 || (i >= 4 && i < 6)) {
                if (!isalpha(static_cast<unsigned char>(number[i]))) {
                    return false;
                }
            } else if (!isdigit(static_cast<unsigned char>(number[i]))) {
                return false;
            }
        }

        return true;
    }

    bool vehicleExists(const string& number) const {
        for (const auto& vehicle : vehicles) {
            if (vehicle.getNumber() == number) {
                return true;
            }
        }
        return false;
    }

    bool isAllocated(const string& number) const {
        for (const auto& allocation : allocations) {
            if (allocation.isActive() &&
                allocation.getVehicleNumber() == number) {
                return true;
            }
        }
        return false;
    }

public:
    void addCategory() {
        int id;
        string name;
        float rate;
        float height;
        float width;

        cout << "\nEnter category ID: ";
        cin >> id;
        cout << "Enter category name: ";
        cin >> name;
        cout << "Enter hourly rate: ";
        cin >> rate;
        cout << "Enter max vehicle height: ";
        cin >> height;
        cout << "Enter max vehicle width: ";
        cin >> width;

        if (rate <= 0 || height <= 0 || width <= 0) {
            cout << "Invalid category details.\n";
            return;
        }

        categories.emplace_back(id, name, rate, height, width);
        cout << "Category added successfully.\n";
    }

    void showCategories() const {
        if (categories.empty()) {
            cout << "No categories available.\n";
            return;
        }

        for (const auto& category : categories) {
            category.display();
        }
    }

    void addVehicle() {
        string number;
        string type;
        string owner;
        string phone;
        string fastag;

        cout << "\nEnter vehicle number: ";
        cin >> number;
        cout << "Enter vehicle type: ";
        cin >> type;
        cout << "Enter owner name: ";
        cin >> owner;
        cout << "Enter mobile number: ";
        cin >> phone;
        cout << "Enter FASTag ID: ";
        cin >> fastag;

        if (!validNumber(number)) {
            cout << "Invalid vehicle number.\n";
            return;
        }

        if (vehicleExists(number)) {
            cout << "Vehicle already exists.\n";
            return;
        }

        vehicles.emplace_back(number, type, owner, phone, fastag);
        cout << "Vehicle registered successfully.\n";
    }

    void showVehicles() const {
        if (vehicles.empty()) {
            cout << "No vehicles registered.\n";
            return;
        }

        for (const auto& vehicle : vehicles) {
            vehicle.display();
        }
    }

    void addSlot() {
        int id;
        int floor;
        string type;
        float size;

        cout << "\nEnter slot ID: ";
        cin >> id;
        cout << "Enter floor number: ";
        cin >> floor;
        cout << "Enter slot type: ";
        cin >> type;
        cout << "Enter slot size: ";
        cin >> size;

        if (id <= 0 || floor <= 0 || type.empty() || size <= 0) {
            cout << "Invalid slot details.\n";
            return;
        }

        for (const auto& existingSlot : slots) {
            if (existingSlot.getId() == id) {
                cout << "Slot ID already exists.\n";
                return;
            }
        }

        slots.emplace_back(id, floor, type, size);
        cout << "Slot added successfully.\n";
    }

    void showSlots() const {
        if (slots.empty()) {
            cout << "No slots available.\n";
            return;
        }

        for (const auto& slot : slots) {
            slot.display();
        }
    }

    void allocateSlot() {
        string number;
        cout << "\nEnter vehicle number: ";
        cin >> number;

        if (!vehicleExists(number)) {
            cout << "Register vehicle first.\n";
            return;
        }

        if (isAllocated(number)) {
            cout << "Vehicle already assigned a slot.\n";
            return;
        }

        for (auto& slot : slots) {
            if (slot.isAvailable()) {
                const int allocationId = allocations.empty()
                    ? 1
                    : allocations.back().getId() + 1;
                allocations.emplace_back(allocationId, number, slot.getId());
                slot.occupy();

                cout << "Slot assigned successfully.\n";
                cout << "Allocation ID: " << allocationId
                     << " | Slot ID: " << slot.getId() << endl;
                return;
            }
        }

        cout << "No slot available.\n";
    }

    void releaseSlot() {
        string number;
        cout << "\nEnter vehicle number to release: ";
        cin >> number;

        for (auto& allocation : allocations) {
            if (allocation.getVehicleNumber() == number &&
                allocation.isActive()) {
                for (auto& slot : slots) {
                    if (slot.getId() == allocation.getSlotId()) {
                        slot.release();
                        break;
                    }
                }

                allocation.release();
                cout << "Slot released successfully.\n";
                return;
            }
        }

        cout << "No active allocation found.\n";
    }

    void showStatus() const {
        cout << "\nParking Status\n";
        cout << "Total Vehicles: " << vehicles.size() << endl;
        cout << "Total Slots: " << slots.size() << endl;

        size_t occupied = 0;
        size_t available = 0;

        for (const auto& slot : slots) {
            if (slot.isOccupied()) {
                ++occupied;
            }
            if (slot.isAvailable()) {
                ++available;
            }
        }

        cout << "Occupied: " << occupied << endl;
        cout << "Available: " << available << endl;
    }
};
