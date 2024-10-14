#include <iostream>
using namespace std;

class Temperature {
private:
    int temperature;
    int incrementStep;

public:
    Temperature() {
        temperature = 4;
        incrementStep = 0;
    }

    void setIncrementStep(int step) {
        incrementStep = step;
    }

    int getTemperature() {
        return temperature;
    }

    void increment() {
        temperature += incrementStep;
    }

    void resetTemperature() {
        temperature = 0;
    }
};

int main() {
    Temperature temp;

    temp.setIncrementStep(2);
    cout << temp.getTemperature() << endl;

    temp.increment();
    cout << temp.getTemperature() << endl;

    temp.resetTemperature();
    cout << temp.getTemperature() << endl;

    return 0;
}
