#include<iostream>
using namespace std;
class QRAccess{
    private:
        int slotNumber;
        string qrCode;
        string vehicleNumber;
        string issueTime;
        string expiryTime;
        string accessStatus;
    public:
        QRAccess();

        void generateQRCode();
        void scanQRCode();
        void validateQRCode();
        void grantAccess();
        void denyAccess();
        void displayQRDetails();
};
void QRAccess::generateQRCode(){

    cout<<"Enter Vehicle Number : ";
    cin>>vehicleNumber;
    cin.ignore();

    cout<<"Enter Parking Slot : ";
    cin>>slotNumber;
    cin.ignore();

    qrCode = "QR_" + vehicleNumber;

    accessStatus = "Generated";

    cout<<"QR Code Generated :"<<qrCode<<endl;

}
void QRAccess::scanQRCode(){
    string scannedCode;

    cout<<"Enter scanned Code : ";

    cin>>scannedCode;
    if (scannedCode == qrCode){
        cout <<"QR Code Scanned Sucessfully..";
        accessStatus = "VALID";
    }
    else{
        cout<<"Invalid QR Code..";
        accessStatus = "Invalid";
    }

}
void QRAccess :: validateQRCode(){
   if(accessStatus == "Valid"){
    cout<<"QR Code is valid";
   }
   else{
    cout<<"QR code is Invalid .......";
   }

}
void QRAccess :: grantAccess(){
    if(accessStatus == "Valid"){
        cout<<"Access Granted....";
    }
    else{
        cout<<"Access Denied";
    }
}
void QRAccess :: denyAccess(){
    accessStatus = "Access Denied...."
    cout<<"Access Denied";
}
void QRAccess :: displayQRDetails(){
    cout<<"\n====QR ACCESS DETAILS====";

    cout<<"QR Code : "<<qrCode<<endl;

    cout<<"Vehicle Number : "<<vehicleNumber<<endl;

    cout<<" : "<<qrCode<<endl;
    
}





