#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
using namespace std;

class FastagAccount {
private:
    string id, plate, holder, status = "UNREGISTERED";
    float bal = 0.0f;

public:
    void registerFastag();
    void checkBalance();
    bool validateFastag();
    bool matchesTag(const string& tag, const string& num) const;
    bool debit(float amount);
    void updateBalance(float amount);
    void blockFastag();
    void displayFastagDetails();
};

class FastagTransaction {
private:
    int txId = 0;
    string tag, plate, type, status = "NOT CREATED";
    float amount = 0.0f;
    time_t date = 0;

public:
    void createTransaction();
    void processTransaction();
    void verifyTransaction();
    void refundTransaction();
    void displayTransactionDetails();
};

class FastagController {
private:
    string tagId, vehicleNumber;
    float parkingCharge = 0.0f;
    bool isAuthenticated = false;
    FastagAccount* account = nullptr;

public:
    void setFastagAccount(FastagAccount& a);
    bool scanFastag();
    bool authenticateFastag();
    bool deductParkingFee();
    void processEntryPayment();
    void processExitPayment();
    void generateTransactionReceipt();
};

class Device {
protected:
    int deviceId = 0;
    string deviceName, deviceType, deviceStatus = "OFF", location;

public:
    void turnOn();
    void turnOff();
    void checkDeviceStatus();
    void updateDeviceStatus();
    void displayDeviceDetails();
};

class RFIDReader : public Device {
private:
    int readerId = 0;
    string readerLocation, lastScannedTag;
    bool isActive = false;

public:
    string scanTag();
    bool validateTag();
    void activateReader();
    void deactivateReader();
    void displayReaderStatus();
};

class BarrierGate : public Device {
private:
    int gateId = 0;
    string gateLocation, gateType;
    bool isOpen = false;

public:
    void openGate();
    void closeGate();
    bool checkGateStatus();
    void emergencyStop();
    void displayGateStatus();
};

class ParkingSensor : public Device {
private:
    int sensorId = 0, slotId = 0;
    bool isVehicleDetected = false;
    string sensorStatus = "INACTIVE";

public:
    bool detectVehicle();
    void updateSensorStatus();
    void activateSensor();
    void deactivateSensor();
    void displaySensorDetails();
};

class DeviceController {
private:
    int totalDevices = 0, activeDevices = 0, inactiveDevices = 0;
    string controllerStatus = "NOT INITIALIZED";

public:
    void initializeDevices();
    void manageDevices();
    void controlEntryGate();
    void controlExitGate();
    void monitorSensors();
    void handleDeviceFailure();
    void displayDeviceStatus();
};

void FastagAccount::registerFastag() {
    string x, y, z; float a;
    cout << "Enter FASTag ID: "; cin >> x;
    cout << "Enter vehicle number: "; cin >> y;
    cout << "Enter account holder name: "; cin >> ws; getline(cin, z);
    cout << "Enter initial balance: Rs. ";
    if (!(cin >> a) || !isfinite(a) || a < 0 || x.empty() || y.empty() || z.empty()) {
        cout << "Invalid registration details.\n";
        return;
    }
    id = x; plate = y; holder = z; bal = a; status = "ACTIVE";
    cout << "FASTag registered successfully.\n";
}

void FastagAccount::checkBalance() {
    cout << "FASTag balance: Rs. " << bal << endl;
}

bool FastagAccount::validateFastag() {
    return !id.empty() && !plate.empty() && status == "ACTIVE";
}

bool FastagAccount::matchesTag(const string& tag, const string& num) const {
    return status == "ACTIVE" && id == tag && plate == num;
}

bool FastagAccount::debit(float amount) {
    if (!validateFastag() || !isfinite(amount) || amount <= 0 || amount > bal) return false;
    bal -= amount;
    return true;
}

void FastagAccount::updateBalance(float amount) {
    if (!validateFastag()) {
        cout << "Cannot update an inactive or unregistered FASTag.\n";
        return;
    }
    if (!isfinite(amount) || amount == 0 || bal + amount < 0) {
        cout << "Invalid balance adjustment.\n";
        return;
    }
    bal += amount;
    cout << "Balance updated. New balance: Rs. " << bal << endl;
}

void FastagAccount::blockFastag() {
    if (id.empty()) {
        cout << "No registered FASTag to block.\n";
        return;
    }
    status = "BLOCKED";
    cout << "FASTag blocked successfully.\n";
}

void FastagAccount::displayFastagDetails() {
    cout << "\n--- FASTag Account Details ---\n";
    cout << "FASTag ID: " << id << endl;
    cout << "Vehicle Number: " << plate << endl;
    cout << "Account Holder: " << holder << endl;
    cout << "Balance: Rs. " << bal << endl;
    cout << "Status: " << status << endl;
}

void FastagTransaction::createTransaction() {
    static int nextTx = 1;
    string a, b, t; float p;
    cout << "Enter FASTag ID: "; cin >> a;
    cout << "Enter vehicle number: "; cin >> b;
    cout << "Enter transaction amount: Rs. ";
    if (!(cin >> p) || !isfinite(p) || p <= 0) {
        cout << "Transaction amount must be greater than zero.\n";
        return;
    }
    cout << "Enter transaction type (ENTRY/EXIT): "; cin >> t;
    if (t != "ENTRY" && t != "EXIT") {
        cout << "Invalid transaction type.\n";
        return;
    }
    txId = nextTx++;
    tag = a; plate = b; amount = p; type = t; date = time(nullptr); status = "PENDING";
    cout << "Transaction " << txId << " created.\n";
}

void FastagTransaction::processTransaction() {
    if (status != "PENDING" || tag.empty() || plate.empty() || amount <= 0) {
        cout << "No valid pending transaction to process.\n";
        return;
    }
    status = "SUCCESS";
    cout << "Transaction processed successfully.\n";
}

void FastagTransaction::verifyTransaction() {
    bool ok = txId > 0 && !tag.empty() && !plate.empty() && amount > 0 &&
              (status == "PENDING" || status == "SUCCESS");
    cout << (ok ? "Transaction details are valid.\n" : "Transaction details are invalid or incomplete.\n");
}

void FastagTransaction::refundTransaction() {
    if (status != "SUCCESS") {
        cout << "Only a successful transaction can be refunded.\n";
        return;
    }
    status = "REFUNDED";
    cout << "Refund recorded for Rs. " << amount << ".\n";
}

void FastagTransaction::displayTransactionDetails() {
    cout << "\n--- FASTag Transaction ---\n";
    cout << "Transaction ID: " << txId << endl;
    cout << "FASTag ID: " << tag << endl;
    cout << "Vehicle Number: " << plate << endl;
    cout << "Amount: Rs. " << amount << endl;
    cout << "Date: " << (date == 0 ? "N/A" : ctime(&date));
    cout << "Type: " << type << endl;
    cout << "Status: " << status << endl;
}

bool FastagController::scanFastag() {
    isAuthenticated = false;
    parkingCharge = 0.0f;
    cout << "Scan or enter FASTag ID: ";
    if (!(cin >> tagId)) {
        cout << "Unable to read FASTag ID.\n";
        return false;
    }
    cout << "Enter vehicle number: ";
    if (!(cin >> vehicleNumber)) {
        cout << "Unable to read vehicle number.\n";
        return false;
    }
    return !tagId.empty() && !vehicleNumber.empty();
}

void FastagController::setFastagAccount(FastagAccount& a) {
    account = &a; isAuthenticated = false; parkingCharge = 0.0f;
}

bool FastagController::authenticateFastag() {
    isAuthenticated = account != nullptr && account->matchesTag(tagId, vehicleNumber);
    cout << (isAuthenticated ? "FASTag details accepted.\n" : "FASTag authentication failed.\n");
    return isAuthenticated;
}

bool FastagController::deductParkingFee() {
    if (!isAuthenticated) {
        cout << "Authenticate the FASTag before processing a fee.\n";
        return false;
    }
    if (parkingCharge > 0.0f) {
        cout << "A payment has already been completed for this scan.\n";
        return false;
    }
    cout << "Enter parking fee: Rs. ";
    if (!(cin >> parkingCharge) || !isfinite(parkingCharge) || parkingCharge <= 0) {
        cout << "Parking fee must be greater than zero.\n";
        parkingCharge = 0.0f;
        return false;
    }
    if (!account->debit(parkingCharge)) {
        cout << "Insufficient balance or inactive FASTag account.\n";
        parkingCharge = 0.0f;
        return false;
    }
    cout << "Parking fee of Rs. " << parkingCharge << " processed for " << vehicleNumber << ".\n";
    return true;
}

void FastagController::processEntryPayment() {
    if (scanFastag() && authenticateFastag() && deductParkingFee())
        cout << "Entry payment completed.\n";
}

void FastagController::processExitPayment() {
    if (scanFastag() && authenticateFastag() && deductParkingFee())
        cout << "Exit payment completed.\n";
}

void FastagController::generateTransactionReceipt() {
    if (!isAuthenticated || parkingCharge <= 0) {
        cout << "No completed payment is available for a receipt.\n";
        return;
    }
    cout << "\n--- Parking Payment Receipt ---\n";
    cout << "FASTag ID: " << tagId << endl;
    cout << "Vehicle Number: " << vehicleNumber << endl;
    cout << "Amount: Rs. " << parkingCharge << endl;
    cout << "Status: COMPLETED\n";
}

void Device::turnOn() {
    deviceStatus = "ON"; cout << deviceName << " turned on.\n";
}

void Device::turnOff() {
    deviceStatus = "OFF"; cout << deviceName << " turned off.\n";
}

void Device::checkDeviceStatus() {
    cout << deviceName << " status: " << deviceStatus << endl;
}

void Device::updateDeviceStatus() {
    string s;
    cout << "Enter new device status (ON/OFF/MAINTENANCE): "; cin >> s;
    if (s != "ON" && s != "OFF" && s != "MAINTENANCE") {
        cout << "Invalid device status.\n";
        return;
    }
    deviceStatus = s; cout << "Device status updated.\n";
}

void Device::displayDeviceDetails() {
    cout << "\n--- Device Details ---\n";
    cout << "Device ID: " << deviceId << endl;
    cout << "Name: " << deviceName << endl;
    cout << "Type: " << deviceType << endl;
    cout << "Status: " << deviceStatus << endl;
    cout << "Location: " << location << endl;
}

string RFIDReader::scanTag() {
    if (!isActive) {
        cout << "RFID reader is inactive.\n";
        return "";
    }
    cout << "Scan or enter tag ID: "; cin >> lastScannedTag;
    return lastScannedTag;
}

bool RFIDReader::validateTag() {
    bool ok = isActive && !lastScannedTag.empty();
    cout << (ok ? "Tag is valid.\n" : "Tag is invalid or reader is inactive.\n");
    return ok;
}

void RFIDReader::activateReader() {
    isActive = true; cout << "RFID reader activated.\n";
}

void RFIDReader::deactivateReader() {
    isActive = false; cout << "RFID reader deactivated.\n";
}

void RFIDReader::displayReaderStatus() {
    cout << "\n--- RFID Reader Status ---\n";
    cout << "Reader ID: " << readerId << endl;
    cout << "Location: " << readerLocation << endl;
    cout << "Status: " << (isActive ? "ACTIVE" : "INACTIVE") << endl;
    cout << "Last Scanned Tag: " << (lastScannedTag.empty() ? "None" : lastScannedTag) << endl;
}

void BarrierGate::openGate() {
    if (gateType == "EMERGENCY_STOP") {
        cout << "Gate cannot open while emergency stop is active.\n";
        return;
    }
    isOpen = true; turnOn(); cout << "Barrier gate opened.\n";
}

void BarrierGate::closeGate() {
    isOpen = false; cout << "Barrier gate closed.\n";
}

bool BarrierGate::checkGateStatus() {
    cout << "Gate status: " << (isOpen ? "OPEN" : "CLOSED") << endl;
    return isOpen;
}

void BarrierGate::emergencyStop() {
    isOpen = false; gateType = "EMERGENCY_STOP"; turnOff();
    cout << "Emergency stop activated. Gate closed.\n";
}

void BarrierGate::displayGateStatus() {
    cout << "\n--- Barrier Gate Status ---\n";
    cout << "Gate ID: " << gateId << endl;
    cout << "Location: " << gateLocation << endl;
    cout << "Gate Type: " << gateType << endl;
    cout << "Status: " << (isOpen ? "OPEN" : "CLOSED") << endl;
}

bool ParkingSensor::detectVehicle() {
    if (sensorStatus != "ACTIVE") {
        cout << "Parking sensor is inactive.\n";
        return false;
    }
    char c; cout << "Is a vehicle detected? (y/n): "; cin >> c;
    isVehicleDetected = (c == 'y' || c == 'Y');
    return isVehicleDetected;
}

void ParkingSensor::updateSensorStatus() {
    cout << "Sensor status: " << sensorStatus << endl;
}

void ParkingSensor::activateSensor() {
    sensorStatus = "ACTIVE"; cout << "Parking sensor activated.\n";
}

void ParkingSensor::deactivateSensor() {
    sensorStatus = "INACTIVE"; isVehicleDetected = false; cout << "Parking sensor deactivated.\n";
}

void ParkingSensor::displaySensorDetails() {
    cout << "\n--- Parking Sensor Details ---\n";
    cout << "Sensor ID: " << sensorId << endl;
    cout << "Slot ID: " << slotId << endl;
    cout << "Status: " << sensorStatus << endl;
    cout << "Vehicle Detected: " << (isVehicleDetected ? "Yes" : "No") << endl;
}

void DeviceController::initializeDevices() {
    totalDevices = 3; activeDevices = totalDevices; inactiveDevices = 0; controllerStatus = "ACTIVE";
    cout << "Device controller initialized for " << totalDevices << " devices.\n";
}

void DeviceController::manageDevices() {
    if (controllerStatus == "NOT INITIALIZED") initializeDevices();
    displayDeviceStatus();
}

void DeviceController::controlEntryGate() {
    BarrierGate gate; gate.openGate();
}

void DeviceController::controlExitGate() {
    BarrierGate gate; gate.openGate();
}

void DeviceController::monitorSensors() {
    ParkingSensor sensor; sensor.activateSensor();
    cout << (sensor.detectVehicle() ? "Sensor reports an occupied slot.\n" : "Sensor reports an available slot.\n");
}

void DeviceController::handleDeviceFailure() {
    if (activeDevices <= 0) {
        cout << "No active devices remain to report as failed.\n";
        return;
    }
    --activeDevices; ++inactiveDevices;
    if (activeDevices == 0) controllerStatus = "DEGRADED";
    cout << "Device failure recorded.\n";
}

void DeviceController::displayDeviceStatus() {
    cout << "\n--- Device Controller Status ---\n";
    cout << "Controller: " << controllerStatus << endl;
    cout << "Total Devices: " << totalDevices << endl;
    cout << "Active Devices: " << activeDevices << endl;
    cout << "Inactive Devices: " << inactiveDevices << endl;
}