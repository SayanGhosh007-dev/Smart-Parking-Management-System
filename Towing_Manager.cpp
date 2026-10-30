#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>

enum class ViolationType {
    OVERSTAY_LIMIT,
    UNAUTHORIZED_RESERVED_BAY,
    OBSTRUCTING_EMERGENCY_EXIT,
    NO_PARKING_ZONE
};

struct TowRecord {
    std::string vehiclePlate;
    std::string slotId;
    ViolationType violation;
    std::string timestamp;
    std::string towTruckId;
    double baseFine;
    double hourlyHoldingRate;
    int hoursInYard;
    bool isReleased;
};

class TowingManager {
private:
    std::vector<TowRecord> impoundedVehicles;

    std::string getTimestamp() const {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm* tm_info = std::localtime(&now_time);
        std::ostringstream oss;
        oss << std::put_time(tm_info, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    std::string violationToString(ViolationType v) const {
        switch (v) {
            case ViolationType::OVERSTAY_LIMIT: return "Overstay Exceeded Limit";
            case ViolationType::UNAUTHORIZED_RESERVED_BAY: return "Parked in Reserved Bay";
            case ViolationType::OBSTRUCTING_EMERGENCY_EXIT: return "Blocking Emergency Exit";
            case ViolationType::NO_PARKING_ZONE: return "Parked in No-Parking Zone";
            default: return "General Violation";
        }
    }

public:
    void dispatchTowTruck(const std::string& plate, const std::string& slotId, ViolationType violation) {
        TowRecord record;
        record.vehiclePlate = plate;
        record.slotId = slotId;
        record.violation = violation;
        record.timestamp = getTimestamp();
        record.towTruckId = "TOW-UNIT-" + std::to_string(101 + impoundedVehicles.size());
        record.hourlyHoldingRate = 50.0;
        record.hoursInYard = 1;
        record.isReleased = false;

        switch (violation) {
            case ViolationType::OBSTRUCTING_EMERGENCY_EXIT: record.baseFine = 1500.0; break;
            case ViolationType::UNAUTHORIZED_RESERVED_BAY:  record.baseFine = 800.0; break;
            case ViolationType::OVERSTAY_LIMIT:             record.baseFine = 500.0; break;
            case ViolationType::NO_PARKING_ZONE:            record.baseFine = 600.0; break;
        }

        impoundedVehicles.push_back(record);

        std::cout << "\n============================================\n";
        std::cout << "         TOWING DISPATCH ORDER ISSUED       \n";
        std::cout << "============================================\n";
        std::cout << "  Vehicle Plate  : " << record.vehiclePlate << "\n";
        std::cout << "  Location Bay   : " << record.slotId << "\n";
        std::cout << "  Violation      : " << violationToString(record.violation) << "\n";
        std::cout << "  Dispatched Unit: " << record.towTruckId << "\n";
        std::cout << "  Timestamp      : " << record.timestamp << "\n";
        std::cout << "  Status         : EN ROUTE TO IMPOUND YARD\n";
        std::cout << "============================================\n";
    }

    void viewImpoundedVehicles() const {
        std::cout << "\n-----------------------------------------------------------------------------------------\n";
        std::cout << "                               CURRENT IMPOUND YARD LOG                                  \n";
        std::cout << "-----------------------------------------------------------------------------------------\n";
        std::cout << std::left << std::setw(14) << "Plate"
                  << std::setw(10) << "Bay"
                  << std::setw(30) << "Reason"
                  << std::setw(15) << "Tow Truck"
                  << std::setw(12) << "Base Fine"
                  << std::setw(10) << "Status" << "\n";
        std::cout << "-----------------------------------------------------------------------------------------\n";

        if (impoundedVehicles.empty()) {
            std::cout << "  No vehicles currently impounded.\n";
        } else {
            for (const auto& v : impoundedVehicles) {
                std::cout << std::left << std::setw(14) << v.vehiclePlate
                          << std::setw(10) << v.slotId
                          << std::setw(30) << violationToString(v.violation)
                          << std::setw(15) << v.towTruckId
                          << "Rs " << std::setw(9) << v.baseFine
                          << (v.isReleased ? "RELEASED" : "IMPOUNDED") << "\n";
            }
        }
        std::cout << "-----------------------------------------------------------------------------------------\n";
    }

    void releaseVehicle(const std::string& plate, int hoursInYard) {
        for (auto& v : impoundedVehicles) {
            if (v.vehiclePlate == plate && !v.isReleased) {
                v.hoursInYard = hoursInYard;
                double totalPenalty = v.baseFine + (v.hoursInYard * v.hourlyHoldingRate);
                v.isReleased = true;

                std::cout << "\n============================================\n";
                std::cout << "       IMPOUND CLEARANCE & PENALTY BILL     \n";
                std::cout << "============================================\n";
                std::cout << "  Vehicle Plate : " << v.vehiclePlate << "\n";
                std::cout << "  Base Tow Fine : Rs " << v.baseFine << "\n";
                std::cout << "  Yard Period   : " << v.hoursInYard << " hrs @ Rs " << v.hourlyHoldingRate << "/hr\n";
                std::cout << "  Holding Fee   : Rs " << (v.hoursInYard * v.hourlyHoldingRate) << "\n";
                std::cout << "  TOTAL PAYABLE : Rs " << totalPenalty << "\n";
                std::cout << "  Status        : PAID & VEHICLE RELEASED\n";
                std::cout << "============================================\n";
                return;
            }
        }
        std::cout << "\n[!] Active impound record for plate '" << plate << "' not found.\n";
    }
};