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
protected:
    int minTemperature;
    int maxTemperature;
    string mode;

public:
    ThermostatDevice(int id, const string& brand, double power, int minTemp, int maxTemp, const string& mode)
        : SmartDevice(id, brand, power), minTemperature(minTemp), maxTemperature(maxTemp), mode(mode) {}

    virtual double calculatePowerConsumption(double hours) {
        return powerRating * hours;
    }

    void diagnose() override {
        cout << "Thermostat Diagnosis:\n";
        cout << "Device ID: " << deviceID << "\n";
        cout << "Brand: " << brandName << "\n";
        cout << "Mode: " << mode << "\n";
        cout << "Temperature Range: " << minTemperature << "C - " << maxTemperature << "C\n";
    }
};

class SecurityCameraDevice : public SmartDevice {
protected:
    string resolution;
    double recordingHours;

public:
    SecurityCameraDevice(int id, const string& brand, double power, const string& resolution, double hours)
        : SmartDevice(id, brand, power), resolution(resolution), recordingHours(hours) {}

    double calculateDataUsage(double days) {
        double dataRatePerHour = (resolution == "4K") ? 7.5 : 1.5;
        return dataRatePerHour * recordingHours * days;
    }

    void diagnose() override {
        cout << "Security Camera Diagnosis:\n";
        cout << "Device ID: " << deviceID << "\n";
        cout << "Brand: " << brandName << "\n";
        cout << "Resolution: " << resolution << "\n";
        cout << "Recording Hours per Day: " << recordingHours << "\n";
    }
};

class SmartThermostat : public ThermostatDevice {
private:
    bool remoteControlEnabled;

public:
    SmartThermostat(int id, const string& brand, double power, int minTemp, int maxTemp, const string& mode, bool remoteControl)
        : ThermostatDevice(id, brand, power, minTemp, maxTemp, mode), remoteControlEnabled(remoteControl) {}

    double calculatePowerConsumption(double hours) override {
        double efficiencyFactor = remoteControlEnabled ? 0.9 : 1.0;
        return powerRating * hours * efficiencyFactor;
    }

    void diagnose() override {
        cout << "Smart Thermostat Diagnosis:\n";
        cout << "Device ID: " << deviceID << "\n";
        cout << "Brand: " << brandName << "\n";
        cout << "Mode: " << mode << "\n";
        cout << "Temperature Range: " << minTemperature << "C - " << maxTemperature << "C\n";
        cout << "Remote Control Enabled: " << (remoteControlEnabled ? "Yes" : "No") << "\n";
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

    double calculatePowerConsumption(double hours) override {
        double efficiencyFactor = 1 - (energySavingEfficiency / 100.0);
        return powerRating * hours * efficiencyFactor;
    }

    double calculateDataUsage(double days) {
        double dataUsageForCamera = SecurityCameraDevice::calculateDataUsage(days);
        double dataUsageForThermostatControl = days * 0.1;
        return dataUsageForCamera + dataUsageForThermostatControl;
    }

    void diagnose() override {
        cout << "Hybrid Thermostat Diagnosis:\n";
        cout << "Device ID: " << deviceID << "\n";
        cout << "Brand: " << brandName << "\n";
        cout << "Mode: " << mode << "\n";
        cout << "Temperature Range: " << minTemperature << "C - " << maxTemperature << "C\n";
        cout << "Camera Resolution: " << resolution << "\n";
        cout << "Recording Hours per Day: " << recordingHours << "\n";
        cout << "Energy Efficiency: " << energySavingEfficiency << "%\n";
    }
};

int main() {
    SmartThermostat smartThermo(1, "SmartThermoBrand", 1500, 18, 30, "cooling", true);
    cout << "Power Consumption of SmartThermostat for 5 hours: " << smartThermo.calculatePowerConsumption(5) << " watt-hours\n";
    smartThermo.diagnose();

    cout << "\n";

    HybridThermostat hybridThermo(2, "HybridBrand", 1500, 16, 28, "heating", "4K", 6, 15);
    cout << "Power Consumption of HybridThermostat for 5 hours: " << hybridThermo.calculatePowerConsumption(5) << " watt-hours\n";
    cout << "Data Usage for 3 days: " << hybridThermo.calculateDataUsage(3) << " GB\n";
    hybridThermo.diagnose();

    return 0;
}
