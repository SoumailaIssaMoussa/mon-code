#include <iostream>
using namespace std;

class RationalNumber {
private:
    int numerator;
    int denominator;

public:
 RationalNumber() {
int  numerator;
int denominator;
}

    void assign(int numerator,int denominator) {
        if (denominator == 0) {
            cout << "You can not assign 0 as denominator" << endl;
        } else {
            numerator = numerator;
            denominator = denominator;
        }
    }

    double convert() {
        return static_cast<double>(numerator) / denominator;
    }

    void invert() {
        if (numerator == 0) {
            cout << "You can not assign 0 as denominatorInversion Failed " << '\r'<< endl;
        } else {
            int temp = numerator;
            numerator = denominator;
            denominator = temp;
        }
    }

    void print() {
        cout << "the rational number: " << numerator << "/" << denominator << endl;
    }
};

int main() {
    RationalNumber num;
    num.assign(2, 3);
    num.print();

    cout << "decimal equivalent: " << num.convert() << endl;

    num.invert();

cout <<'\r'<< endl;

    num.print();


    return 0;
}
