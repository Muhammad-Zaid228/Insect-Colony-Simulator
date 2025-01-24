#include <iostream>
using namespace std;


class AntFarm;
class Meadow;


class Meadow {
private:
    static Meadow* instance;
    AntFarm* antFarm1;
    AntFarm* antFarm2;

    Meadow() : antFarm1(NULL), antFarm2(NULL) {} 

public:
    static Meadow* getInstance() {
        if (instance==NULL)
        instance = new Meadow();
        return instance;
    }

    void spawnAntFarms();
    void giveResources(int id, const string& resource, int amount);
    void tick(int ticks);
    void summary(int id);
};

Meadow* Meadow::instance = NULL;

class Ant {
protected:
    string type;
    int strength;
    int foodConsumption;

public:
    Ant(const string& t, int s, int f) : type(t), strength(s), foodConsumption(f) {}
    int getStrength() const { 
        return strength; 
    }
    int getFoodConsumption() const { 
    return foodConsumption; 
    }
    string getType() const { 
    return type; 
    }
};


class AntFarm {
private:
    string species;
    int workers;
    int warriors;
    int food;

public:
    AntFarm(const string& species) : species(species), workers(0), warriors(0), food(0) {}

    void addResources(const string& resource, int amount) {
        if (resource == "Food") {
            food += amount;
        } else if (resource == "Worker") {
            workers += amount;
        } else if (resource == "Warrior") {
            warriors += amount;
        }
    }

    void tick() {
        int totalFoodConsumption = (workers * 1) + (warriors * 2);
        food -= totalFoodConsumption;
        if (food < 0) {
            cout << "AntFarm " << species << " is starving."<<endl;
            food = 0;
        }
    }

    void printSummary(int id) const {
        cout << "AntFarm ID: " << id << endl;
        cout << "Species: " << species << endl;
        cout << "Food: " << food << endl;
        cout << "Workers: " << workers << endl;
        cout << "Warriors: " << warriors << endl;
    }
};

void Meadow::spawnAntFarms() {
    antFarm1 = new AntFarm("Killer");
    antFarm2 = new AntFarm("Pansy");
    cout << "Spawned AntFarms: Killer and Pansy"<<endl;
}

void Meadow::giveResources(int id, const string& resource, int amount) {
    if (id == 1 && antFarm1) {
        antFarm1->addResources(resource, amount);
        cout << "Gave " << amount << " " << resource << " to AntFarm 1."<<endl;
    } 
    else if (id == 2 && antFarm2) {
        antFarm2->addResources(resource, amount);
        cout << "Gave " << amount << " " << resource << " to AntFarm 2."<<endl;
    } 
    else {
        cout << "Invalid AntFarm ID."<<endl;
    }
}

void Meadow::tick(int ticks) {
    for (int t = 0; t < ticks; ++t) {
        cout << "Tick: " << t + 1 << endl;
        if (antFarm1) antFarm1->tick();
        if (antFarm2) antFarm2->tick();
    }
}

void Meadow::summary(int id) {
    if (id == 1 && antFarm1) {
        antFarm1->printSummary(id);
    } 
    else if (id == 2 && antFarm2) {
        antFarm2->printSummary(id);
    } 
    else {
        cout << "Invalid AntFarm ID."<<endl;
    }
}

int main() {
    Meadow* meadow = Meadow::getInstance();
    meadow->spawnAntFarms();

    meadow->giveResources(1, "Food", 100);
    meadow->giveResources(1, "Worker", 30);
    meadow->giveResources(1, "Warrior", 15);

    meadow->giveResources(2, "Food", 50);
    meadow->giveResources(2, "Worker", 20);

    meadow->tick(3);

    meadow->summary(1);
    meadow->summary(2);

    return 0;
}
