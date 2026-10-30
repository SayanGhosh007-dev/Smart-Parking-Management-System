#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

// 3D Spatial Representation: (Z = Floor, X = Aisle, Y = Bay/Slot)
struct Coordinate3D {
    int floor;
    int aisle;
    int bay;
};

class Navigation3D {
private:
    const int TOTAL_FLOORS = 3;
    const int AISLES_PER_FLOOR = 3;
    const int SLOTS_PER_AISLE = 6;

public:
    void renderFloorMap(const Coordinate3D& target) const {
        std::cout << "\n============================================\n";
        std::cout << "       3D NAVIGATION - FLOOR " << target.floor << " MAP       \n";
        std::cout << "============================================\n";
        std::cout << "  [RAMP / ELEVATOR ACCESS: (0, 0)]\n\n";

        for (int a = 0; a < AISLES_PER_FLOOR; ++a) {
            std::cout << "  Aisle " << a << " | ";
            for (int s = 0; s < SLOTS_PER_AISLE; ++s) {
                if (a == target.aisle && s == target.bay) {
                    std::cout << "[TARGET] ";
                } else {
                    std::cout << "[ P-" << a << s << " ] ";
                }
            }
            std::cout << "\n";
        }
        std::cout << "============================================\n";
    }

    void generateTurnByTurnDirections(const Coordinate3D& start, const Coordinate3D& destination) const {
        std::cout << "\n[3D NAVIGATOR] Route: Entry -> Level " 
                  << destination.floor << ", Aisle " << destination.aisle 
                  << ", Slot " << destination.bay << "\n";

        int step = 1;
        std::cout << "  Step " << step++ << ": Enter via Main Gate at Level " << start.floor << ".\n";

        if (destination.floor > start.floor) {
            std::cout << "  Step " << step++ << ": Drive forward 20m and take Ramp UP to Level " 
                      << destination.floor << ".\n";
        } else if (destination.floor < start.floor) {
            std::cout << "  Step " << step++ << ": Drive forward 20m and take Ramp DOWN to Level " 
                      << destination.floor << ".\n";
        } else {
            std::cout << "  Step " << step++ << ": Stay on current Level " << destination.floor << ".\n";
        }

        std::cout << "  Step " << step++ << ": Turn into Lane / Aisle " << destination.aisle << ".\n";
        std::cout << "  Step " << step++ << ": Proceed " << (destination.bay * 5) + 5 << " meters.\n";
        std::cout << "  Step " << step++ << ": Spot is on your " 
                  << ((destination.bay % 2 == 0) ? "LEFT" : "RIGHT") << " [Slot #" << destination.bay << "].\n";

        // Weighted Euclidean 3D calculation
        double euclideanDist = std::sqrt(
            std::pow((destination.floor - start.floor) * 4.0, 2) +
            std::pow((destination.aisle - start.aisle) * 8.0, 2) +
            std::pow((destination.bay - start.bay) * 5.0, 2)
        );

        std::cout << "  Distance: " << std::fixed << std::setprecision(1) << euclideanDist 
                  << "m | Est. Drive Time: " << static_cast<int>(euclideanDist / 1.5) << "s.\n";

        renderFloorMap(destination);
    }
};