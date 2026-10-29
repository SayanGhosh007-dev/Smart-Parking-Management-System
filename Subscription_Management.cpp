#include <iostream>
#include <vector>
#include <string>
using namespace std;

class SubscriptionManagement {
private:
    string vehicleNumber;
    vector<string> selectedServices;
    int totalAmount;

public:
    explicit SubscriptionManagement(string number) {
        vehicleNumber = number;
        totalAmount = 0;
    }

    void displayServices() const {
        cout << "\n--- Available Services ---\n";
        cout << "1. EV Charging - Rs. 200\n";
        cout << "2. Extra Fuel - Rs. 500\n";
        cout << "3. Vehicle Cleaning - Rs. 150\n";
    }

    bool addService(int choice) {
        string service;
        int price;

        switch (choice) {
            case 1:
                service = "EV Charging";
                price = 200;
                break;

            case 2:
                service = "Extra Fuel";
                price = 500;
                break;

            case 3:
                service = "Vehicle Cleaning";
                price = 150;
                break;

            default:
                cout << "Invalid service choice.\n";
                return false;
        }

        for (const auto &existing : selectedServices) {
            if (existing == service) {
                cout << "Service already selected.\n";
                return false;
            }
        }

        selectedServices.push_back(service);
        totalAmount += price;

        cout << service << " added successfully.\n";
        cout << "Price: Rs. " << price << endl;

        return true;
    }

    void displayBill() const {
        cout << "\n--- Subscription Bill ---\n";
        cout << "Vehicle Number: " << vehicleNumber << endl;

        if (selectedServices.empty()) {
            cout << "No services selected.\n";
        } else {
            cout << "Selected Services:\n";

            for (const auto &service : selectedServices) {
                cout << "- " << service << endl;
            }
        }

        cout << "Total Amount: Rs. " << totalAmount << endl;
    }

    int getTotalAmount() const {
        return totalAmount;
    }
};