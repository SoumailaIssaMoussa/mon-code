
#include <iostream>
using namespace std;

class Celsius;

class Fahrenheit {
    double temp;
public:
    Fahrenheit() : temp(0) {}
    Fahrenheit(double f) {
        assign(f);
    }

    void assign(double f) {
        if (f >= -459.67)
            temp = f;
        else
            cout << "Temperature can't be below absolute zero!" << endl;
    }

    void display() const {
        cout << "The temperature is " << temp << " Fahrenheit." << endl;
    }

    operator Celsius();
};

class Kelvin {
    double temp;
public:
    Kelvin() : temp(0) {}
    Kelvin(double k) {
        assign(k);
    }

    void assign(double k) {
        if (k >= 0)
            temp = k;
        else
            cout << "Temperature can't be below absolute zero!" << endl;
    }

    void display() const {
        cout << "The temperature is " << temp << " Kelvin." << endl;
    }

    operator Celsius();
};

class Celsius {
    double temp;
public:
    Celsius() : temp(0) {}
    Celsius(double c) {
        assign(c);
    }

    void assign(double c) {
        if (c >= -273.15)
            temp = c;
        else
            cout << "Temperature can't be below absolute zero!" << endl;
    }

    void display() const {
        cout << "The temperature is " << temp << " Celsius." << endl;
    }

    operator Fahrenheit() {
        return Fahrenheit(temp * 9 / 5 + 32);
    }

    operator Kelvin() {
        return Kelvin(temp + 273.15);
    }
};

Fahrenheit::operator Celsius() {
    return Celsius((temp - 32) * 5 / 9);
}

Kelvin::operator Celsius() {
    return Celsius(temp - 273.15);
}

int main() {
    double value;
    int choice;
    cout << "Choose the temperature scale to input:\n";
    cout << "1. Celsius\n";
    cout << "2. Fahrenheit\n";
    cout << "3. Kelvin\n";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter the temperature in Celsius: ";
        cin >> value;
        Celsius cTemp(value);
        cTemp.display();


        Fahrenheit fTemp = cTemp;
        Kelvin kTemp = cTemp;
        fTemp.display();
        kTemp.display();
    }
    else if (choice == 2) {
        cout << "Enter the temperature in Fahrenheit: ";
        cin >> value;
        Fahrenheit fTemp(value);
        fTemp.display();


        Celsius cTemp = fTemp;
        Kelvin kTemp = cTemp;
        cTemp.display();
        kTemp.display();
    }
    else if (choice == 3) {
        cout << "Enter the temperature in Kelvin: ";
        cin >> value;
        Kelvin kTemp(value);
        kTemp.display();


        Celsius cTemp = kTemp;
        Fahrenheit fTemp = cTemp;
        cTemp.display();
        fTemp.display();
    }
    else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
