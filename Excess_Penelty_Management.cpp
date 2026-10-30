#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

string toLower(string value) {
    for (char &ch : value) ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    return value;
}

string readString(const string &message) {
    string value;
    cout << message;
    getline(cin, value);
    return value;
}

int readInt(const string &message) {
    int value;
    while (true) {
        cout << message;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again.\n";
    }
}

float readFloat(const string &message) {
    float value;
    while (true) {
        cout << message;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again.\n";
    }
}

bool isExcessType(const string &type) {
    const string loweredType = toLower(type);
    return loweredType.find("excess") != string::npos ||
           loweredType.find("overstay") != string::npos;
}

class Rule {
private:
    int id;
    string name;
    string type;
    float baseFee;
    float extraFee;
    int allowedMinutes;

public:
    Rule(int ruleId, const string &ruleName, const string &violationType,
         float ruleBaseFee, float ruleExtraFee, int ruleAllowedMinutes)
        : id(ruleId),
          name(ruleName),
          type(violationType),
          baseFee(ruleBaseFee),
          extraFee(ruleExtraFee),
          allowedMinutes(ruleAllowedMinutes) {}

    int getId() const { return id; }
    const string &getType() const { return type; }
    float getBaseFee() const { return baseFee; }

    bool matchesType(const string &violationType) const {
        return toLower(type) == toLower(violationType);
    }

    float calculatePenalty(int extraMinutes) const {
        if (extraMinutes <= allowedMinutes) return 0;
        return baseFee + (extraMinutes - allowedMinutes) * extraFee;
    }

    void display() const {
        cout << "\nRule ID: " << id
             << "\nName: " << name
             << "\nType: " << type
             << "\nBase: Rs. " << baseFee
             << "\nExtra: Rs. " << extraFee << " / min"
             << "\nAllowed: " << allowedMinutes << " min\n";
    }
};

class Penalty {
private:
    int id;
    string vehicleNo;
    string type;
    string reason;
    float amount;
    string status;

public:
    Penalty(int penaltyId, const string &vehicleNumber, const string &violationType,
            const string &penaltyReason, float penaltyAmount,
            const string &penaltyStatus = "PENDING")
        : id(penaltyId),
          vehicleNo(vehicleNumber),
          type(violationType),
          reason(penaltyReason),
          amount(penaltyAmount),
          status(penaltyStatus) {}

    int getId() const { return id; }
    const string &getVehicleNo() const { return vehicleNo; }
    const string &getType() const { return type; }
    float getAmount() const { return amount; }
    const string &getStatus() const { return status; }
    bool isPaid() const { return status == "PAID"; }

    void setPaid(bool paid) {
        status = paid ? "PAID" : "PENDING";
    }

    void display() const {
        cout << "\nID: " << id
             << "\nVehicle: " << vehicleNo
             << "\nType: " << type
             << "\nReason: " << reason
             << "\nAmount: Rs. " << amount
             << "\nStatus: " << status << "\n";
    }

    void displaySummary() const {
        cout << "\nPenalty found\n"
             << "Vehicle: " << vehicleNo << "\n"
             << "Type: " << type << "\n"
             << "Amount: Rs. " << amount << "\n"
             << "Status: " << status << "\n";
    }
};

class Payment {
private:
    int id;
    int penaltyId;
    string vehicleNo;
    float amount;
    string method;
    string status;

public:
    Payment(int paymentId, int relatedPenaltyId, const string &vehicleNumber,
            float paymentAmount, const string &paymentMethod,
            const string &paymentStatus = "COMPLETED")
        : id(paymentId),
          penaltyId(relatedPenaltyId),
          vehicleNo(vehicleNumber),
          amount(paymentAmount),
          method(paymentMethod),
          status(paymentStatus) {}

    int getId() const { return id; }

    void display() const {
        cout << "\nPayment ID: " << id
             << "\nPenalty ID: " << penaltyId
             << "\nVehicle: " << vehicleNo
             << "\nAmount: Rs. " << amount
             << "\nMethod: " << method
             << "\nStatus: " << status << "\n";
    }
};

class ExcessPenaltyManagement {
private:
    vector<Rule> rules;
    vector<Penalty> penalties;
    vector<Payment> payments;
    int nextRuleId;
    int nextPenaltyId;
    int nextPaymentId;

public:
    ExcessPenaltyManagement()
        : nextRuleId(1), nextPenaltyId(1), nextPaymentId(1) {}

    void addRule() {
        const int ruleId = nextRuleId++;
        const string name = readString("Rule name: ");
        const string type = readString("Violation type: ");
        const float baseFee = readFloat("Base penalty: ");
        const float extraFee = readFloat("Extra penalty per minute: ");
        const int allowedMinutes = readInt("Allowed extra minutes: ");

        if (baseFee < 0 || extraFee < 0 || allowedMinutes < 0) {
            cout << "Values cannot be negative.\n";
            return;
        }

        rules.push_back(Rule(ruleId, name, type, baseFee, extraFee, allowedMinutes));
        cout << "Rule added successfully.\n";
    }

    void showRules() const {
        if (rules.empty()) {
            cout << "No rules available.\n";
            return;
        }

        for (const Rule &rule : rules) rule.display();
    }

    void issuePenalty() {
        const int penaltyId = nextPenaltyId++;
        const string vehicleNo = readString("Vehicle number: ");
        const string type = readString("Violation type: ");
        const string reason = readString("Reason: ");

        float amount = 0;
        const Rule *matchedRule = nullptr;
        for (const Rule &rule : rules) {
            if (rule.matchesType(type)) {
                matchedRule = &rule;
                break;
            }
        }

        if (isExcessType(type) && matchedRule != nullptr) {
            const int extraMinutes = readInt("Excess minutes: ");
            amount = matchedRule->calculatePenalty(extraMinutes);
        } else if (matchedRule != nullptr) {
            amount = matchedRule->getBaseFee();
        } else {
            amount = readFloat("Penalty amount: ");
            if (amount < 0) {
                cout << "Penalty cannot be negative.\n";
                return;
            }
        }

        penalties.push_back(Penalty(penaltyId, vehicleNo, type, reason, amount));
        cout << "Penalty issued. ID: " << penaltyId
             << ", Amount: Rs. " << amount << "\n";
    }

    void showPenalties() const {
        if (penalties.empty()) {
            cout << "No penalties found.\n";
            return;
        }

        for (const Penalty &penalty : penalties) penalty.display();
    }

    void searchPenalty() const {
        const int id = readInt("Enter penalty ID: ");
        for (const Penalty &penalty : penalties) {
            if (penalty.getId() == id) {
                penalty.displaySummary();
                return;
            }
        }
        cout << "Penalty not found.\n";
    }

    void updatePenaltyStatus() {
        const int id = readInt("Enter penalty ID: ");
        for (Penalty &penalty : penalties) {
            if (penalty.getId() == id) {
                cout << "1. Mark paid\n2. Mark pending\n";
                const int choice = readInt("Choose option: ");
                if (choice == 1) penalty.setPaid(true);
                else if (choice == 2) penalty.setPaid(false);
                else {
                    cout << "Invalid choice.\n";
                    return;
                }
                cout << "Status updated.\n";
                return;
            }
        }
        cout << "Penalty not found.\n";
    }

    void makePayment() {
        const int id = readInt("Enter penalty ID to pay: ");

        for (Penalty &penalty : penalties) {
            if (penalty.getId() == id) {
                if (penalty.isPaid()) {
                    cout << "Penalty already paid.\n";
                    return;
                }

                const string method = readString("Payment method (Cash/Card/UPI): ");
                const int paymentId = nextPaymentId++;
                payments.push_back(Payment(paymentId, penalty.getId(),
                                           penalty.getVehicleNo(), penalty.getAmount(),
                                           method));
                penalty.setPaid(true);
                cout << "Payment successful. Payment ID: " << paymentId << "\n";
                return;
            }
        }

        cout << "Penalty not found.\n";
    }

    void showPayments() const {
        if (payments.empty()) {
            cout << "No payment records.\n";
            return;
        }

        for (const Payment &payment : payments) payment.display();
    }

    void report() const {
        float total = 0;
        float paid = 0;
        float pending = 0;
        for (const Penalty &penalty : penalties) {
            total += penalty.getAmount();
            if (penalty.isPaid()) paid += penalty.getAmount();
            else pending += penalty.getAmount();
        }

        cout << "\n--- REPORT ---\n"
             << "Total penalties: " << penalties.size() << "\n"
             << "Total amount: Rs. " << total << "\n"
             << "Collected: Rs. " << paid << "\n"
             << "Pending: Rs. " << pending << "\n";
    }
};
