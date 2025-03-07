#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <memory>


class SellerActions {
public:
    virtual void serveIceCream() = 0;
    virtual void promoteDeal() = 0;
    virtual void specialOffer() = 0;
    virtual void displayStats() const = 0;
    virtual ~SellerActions() {}
};

class BaseSeller : public SellerActions {
protected:
    std::string name;
    int stock;
    int sales;
    bool specialOfferReady;

public:
    BaseSeller(const std::string& sellerName, int initialStock)
        : name(sellerName), stock(initialStock), sales(0), specialOfferReady(false) {}

    virtual void serveIceCream() override {
        if (stock <= 0) {
            std::cout << name << " is out of stock!\n";
            return;
        }

        int salesIncrease = randomInRange(8, 30);
        stock--;
        sales += salesIncrease;
        std::cout << name << " served! Sales increased by " << salesIncrease
                  << ". Total Sales: " << sales << ", Stock: " << stock << "\n";

        if (sales % 3 == 0) {
            specialOfferReady = true;
        }
    }

    virtual void promoteDeal() override {
        std::cout << name << " promotes a deal! Temporary sales boost for two turns.\n";
    }

    virtual void specialOffer() override {
        std::cout << name << " used a special offer!\n";
    }

    virtual void displayStats() const override {
        std::cout << "Seller: " << name << ", Stock: " << stock
                  << ", Sales: " << sales
                  << ", Special Offer Ready: " << (specialOfferReady ? "Yes" : "No") << "\n";
    }

    bool isSpecialOfferReady() const {
        return specialOfferReady;
    }

    void resetSpecialOffer() {
        specialOfferReady = false;
    }

    int getSales() const { return sales; }

protected:
    static int randomInRange(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
};


class ConeMaster : public BaseSeller {
public:
    ConeMaster() : BaseSeller("Cone Master", 20) {}

    void ConeStackChallenge(int scoopsStacked) {
        int successRate = 100 - (scoopsStacked * 10);
        int randomChance = randomInRange(1, 100);

        if (randomChance <= successRate) {
            int bonusSales = scoopsStacked * randomInRange(8, 30);
            sales += bonusSales;
            stock -= scoopsStacked;
            std::cout << name << " succeeded in stacking " << scoopsStacked
                      << " scoops! Bonus Sales: " << bonusSales << "\n";
        } else {
            stock -= scoopsStacked;
            std::cout << name << "'s cone toppled! Stock wasted.\n";
        }
    }

    void specialOffer() override {
        if (!specialOfferReady) {
            std::cout << name << " tried to use special offer, but it's not ready!\n";
            return;
        }

        for (int i = 0; i < 3; ++i) {
            serveIceCream();
        }
        resetSpecialOffer();
    }
};


class SundaeWizard : public BaseSeller {
public:
    SundaeWizard() : BaseSeller("Sundae Wizard", 15) {}

    void LayeredSundaeBonus(int layers) {
        int bonus = layers * randomInRange(8, 30);
        sales += bonus;
        stock -= layers;
        std::cout << name << " served a layered sundae! Bonus Sales: " << bonus << "\n";
    }

    void specialOffer() override {
        if (!specialOfferReady) {
            std::cout << name << " tried to use special offer, but it's not ready!\n";
            return;
        }

        int doubleSales = sales * 2;
        std::cout << name << " used a special offer! Double Sales: " << doubleSales << "\n";
        resetSpecialOffer();
    }
};

class IceCreamTruckDriver : public BaseSeller {
public:
    IceCreamTruckDriver() : BaseSeller("Ice Cream Truck Driver", 30) {}

    void specialOffer() override {
        if (!specialOfferReady) {
            std::cout << name << " tried to use special offer, but it's not ready!\n";
            return;
        }

        stock += 10;
        std::cout << name << " used a special offer! Restocked 10 units. Stock: " << stock << "\n";
        resetSpecialOffer();
    }
};


class CustomerRush {
private:
    int patience;
    int salesGoal;

public:
    CustomerRush(int initialPatience, int salesTarget)
        : patience(initialPatience), salesGoal(salesTarget) {}

    void decreasePatience() {
        patience -= BaseSeller::randomInRange(20, 50);
        std::cout << "Customer patience decreased. Remaining patience: " << patience << "\n";
    }

    bool isSatisfied(int totalSales) const {
        return totalSales >= salesGoal;
    }

    bool isOutOfPatience() const {
        return patience <= 0;
    }
};




class SimulationEngine {
private:
    std::vector<std::shared_ptr<BaseSeller>> sellers;
    CustomerRush customerRush;
    int totalSales;

public:
    SimulationEngine() : customerRush(200, 300), totalSales(0) {}

    void addSeller(std::shared_ptr<BaseSeller> seller) {
        sellers.push_back(seller);
    }

    void runSimulation(int turns) {
        std::cout << "Game begins! Sellers vs. Customer Rush\n";

        for (int turn = 1; turn <= turns; ++turn) {
            std::cout << "Turn " << turn << ":\n";
            for (auto& seller : sellers) {
                seller->serveIceCream();
                totalSales += seller->getSales();

                if (seller->isSpecialOfferReady()) {
                    seller->specialOffer();
                }
            }

            customerRush.decreasePatience();

            if (customerRush.isSatisfied(totalSales)) {
                std::cout << "Customer Rush satisfied! Sellers win!\n";
                return;
            }

            if (customerRush.isOutOfPatience()) {
                std::cout << "Customer Rush lost patience. Sellers lose!\n";
                return;
            }
        }

        std::cout << "Game over. Sellers could not meet the sales goal.\n";
    }
};



int main() {
    SimulationEngine engine;

    engine.addSeller(std::make_shared<ConeMaster>());
    engine.addSeller(std::make_shared<SundaeWizard>());
    engine.addSeller(std::make_shared<IceCreamTruckDriver>());

    engine.runSimulation(10);
    return 0;
}



