#include<iostream>
using namespace std;
class ParkingReport{
    private:
    int totalSlots;
    int occupiedSlots;
    int availableSlots;
    int totalVehicles;
    double totalRevenue;
    double occupancyPercentage;

public:
    ParkingReport()
        void calculateOccupancy();
        void calculateRevenue();
        void generateOccupancyReport();
        void generateRevenueReport();
        void displayReport();
};
void ParkingReport

