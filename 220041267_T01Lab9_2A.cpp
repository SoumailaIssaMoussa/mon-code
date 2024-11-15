#include <iostream>
#include <string>
using namespace std;

class SmartDevice {
protected:
    int deviceID;
   string brandName;
    float powerRating;

public:
    SmartDevice(int id, const std::string& brand, float power)
        : deviceID(id), brandName(brand), powerRating(power) {}

    virtual void diagnose() = 0;

    virtual ~SmartDevice() {}

    void displayDetails() const {
       cout << "Device ID: " << deviceID << "\n";
      cout << "Brand Name: " << brandName << "\n";
    cout << "Power Rating: " << powerRating << " watts\n";
    }
};

class SmartLight : public SmartDevice {
public:
    SmartLight(int id, const string& brand, float power)
        : SmartDevice(id, brand, power) {}

    void diagnose() override {
       cout << "Diagnosing Smart Light: Checking brightness and color settings.\n";
    }
};

class SmartThermostat : public SmartDevice {
public:
    SmartThermostat(int id, const string& brand, float power)
        : SmartDevice(id, brand, power) {}

    void diagnose() override {
      cout << "Diagnosing Smart Thermostat: Checking temperature sensors and connectivity.\n";
    }
};

int main() {
    SmartLight light1(101, "Philips", 10.5);
    SmartThermostat thermostat1(202, "Nest", 5.0);

   cout << "Smart Light Details:\n";
    light1.displayDetails();
    light1.diagnose();

 cout << "\nSmart Thermostat Details:\n";
    thermostat1.displayDetails();
    thermostat1.diagnose();

    return 0;
}
