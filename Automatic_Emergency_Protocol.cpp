#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

class AutomaticEmergencyProtocol {
private:
    struct Emergency {
        int id;
        string type;
        string location;
        string details;
        string status;
    };

    vector<Emergency> emergencies;
    int nextID = 1;

    string toLowerCase(string text) const {
        transform(
            text.begin(),
            text.end(),
            text.begin(),
            [](unsigned char c) {
                return static_cast<char>(tolower(c));
            }
        );

        return text;
    }

public:
    int reportEmergency(
        string type,
        string location,
        string details
    ) {
        int id = nextID++;

        emergencies.push_back({
            id, type, location, details, "ACTIVE"
        });

        cout << "\n!!! EMERGENCY ALERT !!!\n";
        cout << "Emergency ID: " << id << endl;
        cout << "Type: " << type << endl;
        cout << "Location: " << location << endl;
        cout << "Details: " << details << endl;
        cout << "Status: ACTIVE\n";

        string normalizedType = toLowerCase(type);

        if (normalizedType == "fire") {
            cout << "Action: Alert security and contact fire services.\n";
        } else if (normalizedType == "medical") {
            cout << "Action: Contact emergency medical services.\n";
        } else if (normalizedType == "accident") {
            cout << "Action: Alert security and request assistance.\n";
        } else if (normalizedType == "security") {
            cout << "Action: Notify the security team.\n";
        } else {
            cout << "Action: Notify the parking administrator.\n";
        }

        return id;
    }

    void displayEmergencies() const {
        cout << "\n--- Emergency Records ---\n";

        if (emergencies.empty()) {
            cout << "No emergency records found.\n";
            return;
        }

        for (const auto &emergency : emergencies) {
            cout << "\nEmergency ID: " << emergency.id << endl;
            cout << "Type: " << emergency.type << endl;
            cout << "Location: " << emergency.location << endl;
            cout << "Details: " << emergency.details << endl;
            cout << "Status: " << emergency.status << endl;
        }
    }

    bool resolveEmergency(int id) {
        for (auto &emergency : emergencies) {
            if (emergency.id == id &&
                emergency.status == "ACTIVE") {

                emergency.status = "RESOLVED";

                cout << "Emergency resolved successfully.\n";
                return true;
            }
        }

        cout << "Active emergency not found.\n";
        return false;
    }
};