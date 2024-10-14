#include <iostream>


int main() {
    int a1, b1, a2, b2;
    char factor;

    std::cout << "Enter first fraction (format a/b): ";
    std::cin >> a1 >> factor >> b1;

    std::cout << "Enter second fraction (format c/d): ";
    std::cin >> a2 >>  factor >> b2;

    int numerator = a1 * b2 + a2 * b1;
    int denominator = b1 * b2;

    std::cout << "Sum = " << numerator << "/" << denominator << "\n";

    return 0;
}
