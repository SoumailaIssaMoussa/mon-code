#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <fstream>
using namespace std;

// 1. Creature Class
class Creature {
private:
    string name;
    string species;
    string healthStatus;
    int age;

public:
    // Constructor
    Creature(string n, string s, string h, int a) : name(n), species(s), healthStatus(h), age(a) {}
    
    // Getters
    string getName() const { return name; }
    string getSpecies() const { return species; }
    string getHealthStatus() const { return healthStatus; }
    int getAge() const { return age; }
    
    // Setter for health status
    void setHealthStatus(string h) { healthStatus = h; }
    
    // Display creature details
    void display() const {
        cout << "Name: " << name << ", Species: " << species << ", Health: " << healthStatus << ", Age: " << age << endl;
    }

    // Save creature details to file
    void saveToFile(ofstream &file) const {
        file << name << " " << species << " " << healthStatus << " " << age << endl;
    }
};

// 2. Sanctuary Class
class Sanctuary {
private:
    vector<Creature> inhabitants;
    deque<Creature> recoveryZone;
    list<Creature> releasedCreatures;

public:
    // Add creature to sanctuary
    void addCreature(const Creature &c) {
        inhabitants.push_back(c);
    }
    
    // 4. Managing Creature Status
    void sendToRecovery(string name) {
        for (auto it = inhabitants.begin(); it != inhabitants.end(); ++it) {
            if (it->getName() == name && (it->getHealthStatus() == "Injured" || it->getHealthStatus() == "Resting")) {
                recoveryZone.push_back(*it);
                inhabitants.erase(it);
                cout << name << " has been moved to recovery.\n";
                return;
            }
        }
        cout << "Creature not found or already healthy.\n";
    }
    
    void returnFromRecovery() {
        if (!recoveryZone.empty()) {
            Creature c = recoveryZone.front();
            c.setHealthStatus("Healthy");
            inhabitants.push_back(c);
            recoveryZone.pop_front();
            cout << c.getName() << " has returned to the sanctuary and is now Healthy.\n";
        } else {
            cout << "No creatures in recovery.\n";
        }
    }
    
    void releaseCreature(string name) {
        for (auto it = inhabitants.begin(); it != inhabitants.end(); ++it) {
            if (it->getName() == name && it->getHealthStatus() == "Healthy") {
                releasedCreatures.push_back(*it);
                inhabitants.erase(it);
                cout << name << " has been released to the wild.\n";
                return;
            }
        }
        cout << "Creature not found or not healthy enough to be released.\n";
    }

    // 5. File Operations
    void saveData() {
        ofstream inhabitantFile("inhabitants.txt");
        for (const auto &c : inhabitants) c.saveToFile(inhabitantFile);
        inhabitantFile.close();

        ofstream recoveryFile("recovery.txt");
        for (const auto &c : recoveryZone) c.saveToFile(recoveryFile);
        recoveryFile.close();

        ofstream releasedFile("released.txt");
        for (const auto &c : releasedCreatures) c.saveToFile(releasedFile);
        releasedFile.close();
    }

    void loadData() {
        ifstream inhabitantFile("inhabitants.txt");
        string name, species, healthStatus;
        int age;
        while (inhabitantFile >> name >> species >> healthStatus >> age) {
            inhabitants.emplace_back(name, species, healthStatus, age);
        }
        inhabitantFile.close();
    }
    
    void displayAll() {
        cout << "\nSanctuary Creatures:\n";
        for (const auto &c : inhabitants) c.display();

        cout << "\nRecovery Zone:\n";
        for (const auto &c : recoveryZone) c.display();

        cout << "\nReleased Creatures:\n";
        for (const auto &c : releasedCreatures) c.display();
    }
};

void addCreature(Sanctuary &sanctuary) {
    string name, species, health;
    int age;
    cout << "Enter creature name: "; cin >> name;
    cout << "Enter species: "; cin >> species;
    cout << "Enter health status (Healthy/Injured/Resting): "; cin >> health;
    cout << "Enter age: "; cin >> age;
    Creature newCreature(name, species, health, age);
    sanctuary.addCreature(newCreature);
    cout << name << " has been added to the sanctuary.\n";
}

int main() {
    Sanctuary sanctuary;
    int choice;
    string name;

    do {
        cout << "\nFantasy Creature Sanctuary\n";
        cout << "1. Add Creature\n";
        cout << "2. Send to Recovery\n";
        cout << "3. Return from Recovery\n";
        cout << "4. Release Creature\n";
        cout << "5. Save Data\n";
        cout << "6. Load Data\n";
        cout << "7. Display All\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addCreature(sanctuary);
                break;
            case 2:
                cout << "Enter creature name to send to recovery: ";
                cin >> name;
                sanctuary.sendToRecovery(name);
                break;
            case 3:
                sanctuary.returnFromRecovery();
                break;
            case 4:
                cout << "Enter creature name to release: ";
                cin >> name;
                sanctuary.releaseCreature(name);
                break;
            case 5:
                sanctuary.saveData();
                break;
            case 6:
                sanctuary.loadData();
                break;
            case 7:
                sanctuary.displayAll();
                break;
            case 8:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 8);

    return 0;
}
