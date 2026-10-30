#include <iostream>
#include <string>
using namespace std;

class VehicleEntryExit
{
private:
    string vehicleNumber;
    string vehicleType;
    string ownerName;
    string entryTime;
    string exitTime;
    string status;

public:
    VehicleEntryExit()
    {
        vehicleNumber = "";
        vehicleType = "";
        ownerName = "";
        entryTime = "";
        exitTime = "";
        status = "Not Parked";
    }

    void registerVehicle();
    void recordEntry();
    void recordExit();
    void updateStatus();
    void displayVehicleDetails();
};

void VehicleEntryExit::registerVehicle()
{
    cout << "\nREGISTER VEHICLE\n";

    cout << "Enter Vehicle Number : ";
    cin >> vehicleNumber;

    cout << "Enter Vehicle Type : ";
    cin >> vehicleType;

    cout << "Enter Owner Name : ";
    cin >> ownerName;

    cout << "\nVEHICLE REGISTERED SUCCESSFULLY.....\n";
}

void VehicleEntryExit::recordEntry()
{
    cout << "\nADD ENTRY DETAILS\n";

    cout << "Enter Vehicle Number : ";
    cin >> vehicleNumber;

    cout << "Enter Entry Time : ";
    cin >> entryTime;

    cout << "Enter Status : ";
    cin >> status;

    cout << "\nEntry recorded successfully!......\n";
}

void VehicleEntryExit::recordExit()
{
    cout << "\nENTER EXIT DETAILS\n";

    cout << "Enter Vehicle Number : ";
    cin >> vehicleNumber;

    cout << "Enter Exit Time : ";
    cin >> exitTime;

    cout << "Enter Status : ";
    cin >> status;

    cout << "\nExit recorded successfully!......\n";
}

void VehicleEntryExit::updateStatus()
{
    cout << "\nUPDATE STATUS\n";

    cout << "Enter New Status : ";
    cin >> status;

    cout << "Status updated successfully!\n";
}

void VehicleEntryExit::displayVehicleDetails()
{
    cout << "\nVEHICLE DETAILS\n";

    cout << "Vehicle Number : " << vehicleNumber << endl;
    cout << "Vehicle Type   : " << vehicleType << endl;
    cout << "Owner Name     : " << ownerName << endl;
    cout << "Entry Time     : " << entryTime << endl;
    cout << "Exit Time      : " << exitTime << endl;
    cout << "Status         : " << status << endl;
}