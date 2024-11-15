
#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159265358979323846;

class Shape {
public:
    virtual void whoAmI() const = 0;
};

class TwoDimensionalShape : public Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};

class ThreeDimensionalShape : public Shape {
public:
    virtual double surfaceArea() const = 0;
    virtual double volume() const = 0;
};

class Square : public TwoDimensionalShape {
private:
    double side;
public:
    Square(double s) : side(s) {}
    void whoAmI() const override {
        cout << "I am Square. I am a two-dimensional shape.\n";
    }
    double area() const override {
        return side * side;
    }
    double perimeter() const override {
        return 4 * side;
    }
};

class Circle : public TwoDimensionalShape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    void whoAmI() const override {
        cout << "I am Circle. I am a two-dimensional shape.\n";
    }
    double area() const override {
        return PI * radius * radius;
    }
    double perimeter() const override {
        return 2 * PI * radius;
    }
};

class Cube : public ThreeDimensionalShape {
private:
    double side;
public:
    Cube(double s) : side(s) {}
    void whoAmI() const override {
        cout << "I am Cube. I am a three-dimensional shape.\n";
    }
    double surfaceArea() const override {
        return 6 * side * side;
    }
    double volume() const override {
        return side * side * side;
    }
};

class Sphere : public ThreeDimensionalShape {
private:
    double radius;
public:
    Sphere(double r) : radius(r) {}
    void whoAmI() const override {
        cout << "I am Sphere. I am a three-dimensional shape.\n";
    }
    double surfaceArea() const override {
        return 4 * PI * radius * radius;
    }
    double volume() const override {
        return (4.0 / 3.0) * PI * radius * radius * radius;
    }
};

int main() {
    Square square(5);
    Circle circle(3);

    square.whoAmI();
    cout << "Area: " << square.area() << endl;
    cout << "Perimeter: " << square.perimeter() << endl;

    cout << endl;

    circle.whoAmI();
    cout << "Area: " << circle.area() << endl;
    cout << "Perimeter: " << circle.perimeter() << endl;

    cout << endl;

    Cube cube(4);
    Sphere sphere(6);

    cube.whoAmI();
    cout << "Surface Area: " << cube.surfaceArea() << endl;
    cout << "Volume: " << cube.volume() << endl;

    cout << endl;

    sphere.whoAmI();
    cout << "Surface Area: " << sphere.surfaceArea() << endl;
    cout << "Volume: " << sphere.volume() << endl;

    return 0;
}
