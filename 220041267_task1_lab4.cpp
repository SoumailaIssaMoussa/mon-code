
#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    string name;
    int product_id;
    double price;
    int quantity;
    int max_quantity;

    static double total_inventory_value;

public:

Product(string name, int id, double price, int quantity, int max_quantity) {
    this->name = name;
    this->product_id = id;
    this->price = price;
    this->quantity = quantity;
    this->max_quantity = max_quantity;

    total_inventory_value += this->quantity * this->price;
    }

    void addToInventory(int addedQuantity) {
    if (quantity + addedQuantity <= max_quantity) {
        quantity += addedQuantity;
        total_inventory_value += addedQuantity * price;
        } else {
            cout << "it not possible to add\n" << endl;
        }
    }

    bool isAvailable() {
        return quantity > 0;
    }

    void purchase(int purchasedQuantity) {

        if (isAvailable() && quantity >= purchasedQuantity) {
            quantity -= purchasedQuantity;
            total_inventory_value -= purchasedQuantity * price;
        } else {

cout << "it's not possible to complet the baying. only " << quantity << " product avalable" << endl;
        }
    }

    void updatePrice(int discountPercent) {
        double discount = price * (discountPercent / 100.0);
        price -= discount;
        total_inventory_value -= quantity * discount;
    }

    void displayInventoryValue() {
        double inventory_value = quantity * price;
        cout << "the value of inventory" << name << ":" << inventory_value << " BDT" << endl;
    }

    void displayDetails() {
        string availability = isAvailable()? "Available" : "Not Available ";
        cout << "ID of product: " << product_id << endl;
        cout << "Name: " << name << endl;
        cout << "Price: " << price << " BDT" << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Availability: " << availability << endl;
    }
     static void displayTotalInventoryValue() {
 cout << "total value of inventory product: " << total_inventory_value << " BDT" << endl;
    }
};

double Product::total_inventory_value = 0;

int main() {
    Product product1(" Macbook pro", 101, 50000.0, 20, 50);
    product1.addToInventory(6);
    product1.purchase(3);
    product1.updatePrice(5);
    product1.displayInventoryValue();
    product1.displayDetails();

    Product product2("phone", 102, 500.0, 20, 100);
    Product product3("Tablet", 103, 300.0, 15, 80);

    Product::displayTotalInventoryValue();

    return 0;
}















