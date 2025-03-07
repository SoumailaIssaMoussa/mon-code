#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Creature {
protected:
    string name, species;
    int id;
public:
    Creature(int _id, string _name, string _species) : id(_id), name(_name), species(_species) {}
    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Species: " << species << endl;
    }
    int getID() const { return id; }
    string getName() const { return name; }
    virtual void saveToFile(ofstream &file) const {
        file << id << " " << name << " " << species << endl;
    }
};

class ActiveCreature : public Creature {
    string healthStatus;
    vector<string> dailyActivities;
public:
    ActiveCreature(int _id, string _name, string _species, string _health)
        : Creature(_id, _name, _species), healthStatus(_health) {}
    void performActivity(string activity) {
        dailyActivities.push_back(activity);
        if (dailyActivities.size() > 3 && healthStatus == "Healthy")
            healthStatus = "Tired";
    }
    void display() const override {
        Creature::display();
        cout << "Health: " << healthStatus << " Activities: ";
        for (const auto &a : dailyActivities) cout << a << " ";
        cout << endl;
    }
    string getHealthStatus() const { return healthStatus; }
    void saveToFile(ofstream &file) const override {
        file << id << " " << name << " " << species << " " << healthStatus << endl;
    }
};

class RecoveringCreature : public Creature {
    set<string> recoveryStatus;
public:
    RecoveringCreature(int _id, string _name, string _species)
        : Creature(_id, _name, _species) {
        recoveryStatus.insert("Resting");
    }
    void updateRecoveryStatus(string status) { recoveryStatus.insert(status); }
    void display() const override {
        Creature::display();
        cout << "Recovery Status: ";
        for (const auto &r : recoveryStatus) cout << r << " ";
        cout << endl;
    }
    void saveToFile(ofstream &file) const override {
        file << id << " " << name << " " << species << " Recovery ";
        for (const auto &r : recoveryStatus) file << r << " ";
        file << endl;
    }
};

map<int, Creature*> creatures;

void addCreature() {
    int id;
    string name, species, health;
    cout << "Enter ID, Name, Species, and Health Status: ";
    cin >> id >> name >> species >> health;
    creatures[id] = new ActiveCreature(id, name, species, health);
}

void sendToRecovery(int id) {
    if (creatures.find(id) != creatures.end()) {
        ActiveCreature *ac = dynamic_cast<ActiveCreature*>(creatures[id]);
        if (ac && ac->getHealthStatus() != "Healthy") {
            creatures[id] = new RecoveringCreature(id, ac->getName(), ac->getName());
            delete ac;
        }
    }
}

void saveData() {
    ofstream activeFile("active_creatures.txt"), recoveryFile("recovery_creatures.txt");
    for (const auto &pair : creatures) {
        ActiveCreature *ac = dynamic_cast<ActiveCreature*>(pair.second);
        if (ac) ac->saveToFile(activeFile);
        else pair.second->saveToFile(recoveryFile);
    }
}

void loadData() {
    ifstream activeFile("active_creatures.txt"), recoveryFile("recovery_creatures.txt");
    int id;
    string name, species, health;
    while (activeFile >> id >> name >> species >> health)
        creatures[id] = new ActiveCreature(id, name, species, health);
    while (recoveryFile >> id >> name >> species)
        creatures[id] = new RecoveringCreature(id, name, species);
}

int main() {
    addCreature();
    saveData();
    loadData();
    for (const auto &pair : creatures) pair.second->display();
    return 0;
}
