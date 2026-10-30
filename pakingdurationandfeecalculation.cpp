#include <iostream>
#include <string>
using namespace std;

class ParkingFee{
    private:
        string vehicleNumber;
        string entryTime;
        string exitTime;
        double parkingDuration;
        double hourlyRate;
        double totalFee;
    public:
        ParkingFee();

        void setParkingDetails();
        void calculateDuration();
        void calculateFee();
        void displayFeeDetails();
};
void ParkingFee::setParkingDetails(){
    cout<<"\nPARKING DETAILS\n"

    cout<<"Enter Vehicle Number : ";
    cin>>vehicleNumber;
    cin.ignore();

    cout<<"Enter Entry time : ";
    cin>>entryTime;
    cin.ignore();

    cout<<"Enter Exit time : ";
    cin>>exitTime;
    cin.ignore();

    cout<<"Enter Parking Duration :";
    cin>>parkingDuration;
    cin.ignore();

    cout<<"Enter Hourly Rate :";
    cin>>hourlyRate;
    cin.ignore();
}
void PaekingFee::calculateDuration(){
    
}

