
#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;

public:

    Person(string name) : name(name) {}

    virtual void display() {
        cout << "Name: " << name << endl;
    }
};

class Employee : public Person {
private:
    int employeeID;
protected:
    float salary;

public:
    Employee(string name, int employeeID, float salary)
        : Person(name), employeeID(employeeID), salary(salary) {}

    void display() override {
        Person::display();
        cout << "Employee ID: " << employeeID << endl;
        cout << "Salary: " << salary << endl;
    }
};

class Intern : public Employee {
private:
    string schoolName;

public:

    Intern(string name, int employeeID, float salary, string schoolName)
        : Employee(name, employeeID, salary), schoolName(schoolName) {}

    void display() override {
        Employee::display();
        cout << "School Name: " << schoolName << endl;
    }
};

class Manager : protected Employee {
private:
    string department;

public:
    Manager(string name, int employeeID, float salary, string department)
        : Employee(name, employeeID, salary), department(department) {}

    void display() override {
        Employee::display();
        cout << "Department: " << department << endl;
    }
};

class Director : public Manager {
private:
    float bonus;

public:
    Director(string name, int employeeID, float salary, string department, float bonus)
        : Manager(name, employeeID, salary, department), bonus(bonus) {}

    void display() override {
        Manager::display();
        cout << "Bonus: " << bonus << endl;
    }
};

int main() {
    Person person1("Ali");
    Employee employee("Bob", 1001, 50000.0);
    Intern intern("Moussa", 1002, 30000.0, "University of XYZ");
    Manager manager("David", 1003, 70000.0, "Sales");
    Director director("Razak", 1004, 90000.0, "Marketing", 10000.0);
    cout << "Person Details:" << endl;
    person1.display();
    cout << endl;

    cout << "Employee Details:" << endl;
    employee.display();
    cout << endl;

    cout << "Intern Details:" << endl;
    intern.display();
    cout << endl;

    cout << "Manager Details:" << endl;
    manager.display();
    cout << endl;

    cout << "Director Details:" << endl;
    director.display();
    cout << endl;

    return 0;
}
