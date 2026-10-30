#include <iostream>
#include <string>
using namespace std;

class Reservation {
    private:
        int reservationId;
        int slotNumber;
        string vehicleNumber;
        string ownerName;
        string reservationDate;
        string reservationTime;
        string reservationStatus;
    public:
        Reservation();

        void makeReservation();
        void cancelReservation();
        void updateReservation();
        void checkReservation();
        void displayReservation();
};
void Reservation ::setParkingDetails(){
    cout<<"\nPARKING DETAILS\n";

    cout<<"Enter Vehicle Number : ";
    cin>>vehicleNumber;
    cin.ignore();

    cout<<"Enter Entry time : ";
    cin>>entryTime;
    cin.ignore();

    cout<<"Enter Exit time : ";
    cin>>exitTime;
    cin.ignore();

    cout<<"Enter Parking Duration(hours) :";
    cin>>parkingDuration;
    cin.ignore();

    cout<<"Enter Hourly Rate :";
    cin>>hourlyRate;
    cin.ignore();
}
void ParkingFee::calculateDuration(){
    cout<<"\nPARKING DURATION\n";

    cout<<"Parking Duration :"<<parkingDuration<<"hours"<<endl;

}
void ParkingFee :: calculateFee(){
    cout<<"\nFEE DEATILS\n";

    cout<<
}

