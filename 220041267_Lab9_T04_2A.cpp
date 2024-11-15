#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

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
    virtual double getPowerRating() const { return powerRating; }
    virtual void displayInfo() const {
        cout << "Device ID: " << deviceID << "\n";
        cout << "Brand: " << brandName << "\n";
        cout << "Power consumption: " << powerRating << " watts\n";
    }

    virtual ~SmartDevice() {}
};

class ThermostatDevice : public SmartDevice {
protected:
    int minTemp;
    int maxTemp;
    string mode;

public:
    ThermostatDevice(int id, const string& brand, double power, int minTemp, int maxTemp, const string& mode)
        : SmartDevice(id, brand, power), minTemp(minTemp), maxTemp(maxTemp), mode(mode) {}

    void diagnose() override {
        cout << "Diagnosing the thermostat.\n";
    }

    virtual double calculatePowerConsumption(double hours) {
        return powerRating * hours;
    }
};

class SecurityCameraDevice : public SmartDevice {
protected:
    string resolution;
    double recordingHours;

public:
    SecurityCameraDevice(int id, const string& brand, double power, const string& resolution, double hours)
        : SmartDevice(id, brand, power), resolution(resolution), recordingHours(hours) {}

    void diagnose() override {
        cout << "Diagnosing the security camera.\n";
    }

    double calculateDataUsage(double days) {
        double dataRatePerHour = (resolution == "4K") ? 7.5 : 1.5;
        return dataRatePerHour * recordingHours * days;
    }
};

class SmartThermostat : public ThermostatDevice {
private:
    bool remoteControlEnabled;

public:
    SmartThermostat(int id, const string& brand, double power, int minTemp, int maxTemp, const string& mode, bool remoteControl)
        : ThermostatDevice(id, brand, power, minTemp, maxTemp, mode), remoteControlEnabled(remoteControl) {}

    void diagnose() override {
        cout << "Diagnosing the Smart Thermostat.\n";
    }

    double calculatePowerConsumption(double hours) override {
        double efficiencyFactor = remoteControlEnabled ? 0.9 : 1.0;
        return powerRating * hours * efficiencyFactor;
    }
};

class HybridThermostat : public ThermostatDevice, public SecurityCameraDevice {
private:
    double energySavingEfficiency;

public:
    HybridThermostat(int id, const string& brand, double power, int minTemp, int maxTemp, const string& mode, const string& resolution, double hours, double efficiency)
        : ThermostatDevice(id, brand, power, minTemp, maxTemp, mode),
          SecurityCameraDevice(id, brand, power, resolution, hours),
          energySavingEfficiency(efficiency) {}

    void diagnose() override {
        cout << "Diagnosing the Hybrid Thermostat.\n";
    }

    double calculatePowerConsumption(double hours) override {
        double efficiencyFactor = 1 - (energySavingEfficiency / 100.0);
        return  powerRating * hours * efficiencyFactor;
    }

    void displayInfo() const override {
        SmartDevice::displayInfo();
        cout << "Energy efficiency: " << energySavingEfficiency << "%\n";
    }
};

void sort_devices_by_power(SmartDevice** devices, int n) {
    sort(devices, devices + n, [](SmartDevice* a, SmartDevice* b) {
        return a->getPowerRating() > b->getPowerRating();
    });
}

int main() {
    SmartThermostat smartThermo(1, "SmartThermoBrand", 1500, 18, 30, "cooling", true);
    HybridThermostat hybridThermo(2, "HybridBrand", 2000, 16, 28, "heating", "4K", 6, 15);
    SecurityCameraDevice securityCam(3, "CamBrand", 500, "1080p", 8);

    SmartDevice* devices[] = { &smartThermo, &hybridThermo, &securityCam };
    int n = sizeof(devices) / sizeof(devices[0]);

    sort_devices_by_power(devices, n);

    cout << "Devices sorted by power consumption:\n";
    for (int i = 0; i < n; ++i) {
        devices[i]->displayInfo();
        cout << "-------------------\n";
    }

    cout << "\nSpecific information for HybridThermostat:\n";
    hybridThermo.displayInfo();

    return 0;
}
