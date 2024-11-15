
#include <iostream>
#include <string>

using namespace std;

class SmartDevice {
protected:
    int deviceID;
    string brandName;
    double powerRating;

public:
    SmartDevice(int id, const string& brand, double power)
        : deviceID(id), brandName(brand), powerRating(power) {}

    virtual void diagnose() = 0;

    virtual ~SmartDevice() {}
};

class ThermostatDevice : public SmartDevice {
private:
    int minTemperature;
    int maxTemperature;
    string mode;

public:
    ThermostatDevice(int id, const string& brand, double power, int minTemp, int maxTemp, const string& mode)
        : SmartDevice(id, brand, power), minTemperature(minTemp), maxTemperature(maxTemp), mode(mode) {}

    double calculatePowerConsumption(double hours) {
        return powerRating * hours;
    }

    void diagnose() override {
        cout << "Thermostat diagnosis:\n";
        cout << "Device ID: " << deviceID << "\n";
        cout << "Brand: " << brandName << "\n";
        cout << "Mode: " << mode << "\n";
        cout << "Temperature range: " << minTemperature << "C - " << maxTemperature << "C\n";
        cout << "Power rating: " << powerRating << " watts\n";
    }
};

class SecurityCameraDevice : public SmartDevice {
private:
    string resolution;
    double recordingHours;

public:
    SecurityCameraDevice(int id, const string& brand, double power, const string& resolution, double hours)
        : SmartDevice(id, brand, power), resolution(resolution), recordingHours(hours) {}

    double calculateDataUsage(double days) {
        double dataRatePerHour;
        if (resolution == "1080p") {
            dataRatePerHour = 1.5;
        } else if (resolution == "4K") {
            dataRatePerHour = 7.5;
        } else {
            dataRatePerHour = 1.0;
        }
        return dataRatePerHour * recordingHours * days;
    }

    void diagnose() override {
        cout << "Security camera diagnosis:\n";
        cout << "Device ID: " << deviceID << "\n";
        cout << "Brand: " << brandName << "\n";
        cout << "Resolution: " << resolution << "\n";
        cout << "Recording hours per day: " << recordingHours << "\n";
        cout << "Power rating: " << powerRating << " watts\n";
    }
};

int main() {
    ThermostatDevice thermostat(1, "ThermoBrand", 1500, 18, 30, "cooling");
    cout << "Thermostat power consumption for 5 hours: "
         << thermostat.calculatePowerConsumption(5) << " watt-hours\n";
    thermostat.diagnose();

    cout << "\n";

    SecurityCameraDevice camera(2, "SecureCam", 20, "4K", 8);
    cout << "Data usage for 3 days: "
         << camera.calculateDataUsage(3) << " GB\n";
    camera.diagnose();

    return 0;
}
