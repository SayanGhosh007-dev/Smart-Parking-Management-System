#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>

struct CameraNode {
    std::string cameraId;
    int floor;
    std::string coveredAisles;
    std::string streamStatus;
    std::string latestEvent;
};

class LiveMonitoringSystem {
private:
    std::vector<CameraNode> cameras;

    std::string getTimestamp() const {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm* tm_info = std::localtime(&now_time);
        std::ostringstream oss;
        oss << std::put_time(tm_info, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

public:
    LiveMonitoringSystem() {
        cameras.push_back({"CAM-F0-01", 0, "Aisle 0, 1", "ONLINE", "Normal Traffic"});
        cameras.push_back({"CAM-F0-02", 0, "Emergency Ramp", "ONLINE", "Clear"});
        cameras.push_back({"CAM-F1-01", 1, "Aisle 0, 1", "ONLINE", "Slot L1-01 Occupied"});
        cameras.push_back({"CAM-F1-02", 1, "Aisle 2", "SENSOR_TRIGGERED", "Motion detected near Bay 4"});
        cameras.push_back({"CAM-F2-01", 2, "Aisle 0, 1, 2", "ONLINE", "Normal Traffic"});
    }

    void displayUserLiveFeed(const std::string& vehiclePlate, int floor, int aisle, int bay) const {
        std::cout << "\n=======================================================\n";
        std::cout << "       PARKSMART USER PORTAL - LIVE TELEMETRY FEED      \n";
        std::cout << "=======================================================\n";
        std::cout << "  Target Vehicle : " << vehiclePlate << "\n";
        std::cout << "  Assigned Spot  : Floor " << floor << ", Aisle " << aisle << ", Bay " << bay << "\n";
        std::cout << "  Feed Timestamp : " << getTimestamp() << "\n";
        std::cout << "-------------------------------------------------------\n";

        bool foundCam = false;
        for (const auto& cam : cameras) {
            if (cam.floor == floor) {
                std::cout << "  Linked Camera : [" << cam.cameraId << "] Covering " << cam.coveredAisles << "\n";
                std::cout << "  Status        : " << cam.streamStatus << "\n";
                std::cout << "  Live Stream   : [CONNECTED - 1080p RTSP Stream Simulation]\n";
                std::cout << "  Sensor Status : Vehicle detected stationary inside perimeter.\n";
                std::cout << "  Security Alert: None (No unauthorized movement).\n";
                foundCam = true;
                break;
            }
        }
        if (!foundCam) {
            std::cout << "  Linked Camera : [CAM-GENERIC] Feed available via central hub.\n";
        }
        std::cout << "=======================================================\n";
    }

    void displaySecurityControlCenter() const {
        std::cout << "\n----------------------------------------------------------------------------------\n";
        std::cout << "                      CENTRAL CCTV & SENSOR MONITORING HUB                         \n";
        std::cout << "----------------------------------------------------------------------------------\n";
        std::cout << std::left << std::setw(12) << "Camera ID"
                  << std::setw(8) << "Floor"
                  << std::setw(20) << "Coverage Area"
                  << std::setw(18) << "Stream Status"
                  << "Latest Event Telemetry\n";
        std::cout << "----------------------------------------------------------------------------------\n";
        for (const auto& cam : cameras) {
            std::cout << std::left << std::setw(12) << cam.cameraId
                      << std::setw(8) << cam.floor
                      << std::setw(20) << cam.coveredAisles
                      << std::setw(18) << cam.streamStatus
                      << cam.latestEvent << "\n";
        }
        std::cout << "----------------------------------------------------------------------------------\n";
    }

    void triggerSecuritySensor(const std::string& camId, const std::string& alertMessage) {
        for (auto& cam : cameras) {
            if (cam.cameraId == camId) {
                cam.streamStatus = "ALERT_ACTIVE";
                cam.latestEvent = alertMessage;
                std::cout << "\n[!] BROADCAST: Camera " << camId << " triggered alert: " << alertMessage << "\n";
                return;
            }
        }
    }
};