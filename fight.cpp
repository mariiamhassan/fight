#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Weapon {
private:
    string name;
    int damage;
    int accuracy;
public:
    Weapon(string n, int d, int a) : name(n), damage(d), accuracy(a) {}

    string getName() { return name; }
    int getDamage() { return damage; }

    bool hit() {
        int chance = rand() % 100 + 1;
        return (chance <= accuracy);
    }
};

class Character {
protected:
    string name;
    int health;
    vector<Weapon> weapons;
public:
    Character(string n) : name(n), health(100) {}
    virtual void chooseWeaponAndAttack(Character &target, int choice) = 0;

    bool isAlive() { return health > 0; }
    void takeDamage(int dmg) { health -= dmg; if (health < 0) health = 0; }
    int getHealth() { return health; }
    string getName() { return name; }
};

class OptimusPrime : public Character {
public:
    OptimusPrime() : Character("Optimus Prime") {
        weapons.push_back(Weapon("Ion Rifle", 6, 100));
        weapons.push_back(Weapon("Energon Swords", 12, 80));
        weapons.push_back(Weapon("Shoulder Cannon", 45, 25));
    }

    void chooseWeaponAndAttack(Character &target, int choice) override {
        Weapon w = weapons[choice];
        cout << name << " attacks with " << w.getName();
        if (w.hit()) {
            cout << " and hits! Damage: " << w.getDamage() << endl;
            target.takeDamage(w.getDamage());
        } else {
            cout << " but misses!" << endl;
        }
        cout << target.getName() << " health: " << target.getHealth() << "\n\n";
    }

    void showWeapons() {
        cout << "Choose your weapon:\n";
        for (int i = 0; i < weapons.size(); i++) {
            cout << i << ". " << weapons[i].getName() << " (Damage: " 
                 << weapons[i].getDamage() << ")\n";
        }
    }
};

class Megatron : public Character {
public:
    Megatron() : Character("Megatron") {
        weapons.push_back(Weapon("Fusion Cannon", 10, 95));
        weapons.push_back(Weapon("Dark Saber", 18, 70));
        weapons.push_back(Weapon("Rocket Launcher", 50, 20));
    }

    void chooseWeaponAndAttack(Character &target, int choice) override {
        Weapon w = weapons[choice];
        cout << name << " attacks with " << w.getName();
        if (w.hit()) {
            cout << " and hits! Damage: " << w.getDamage() << endl;
            target.takeDamage(w.getDamage());
        } else {
            cout << " but misses!" << endl;
        }
        cout << target.getName() << " health: " << target.getHealth() << "\n\n";
    }

    int randomChoice() {
        return rand() % weapons.size();
    }
};

int main() {
    srand(time(0));
    int choice;
    cout << "Choose your character:\n1. Optimus Prime\n2. Megatron\n";
    cin >> choice;

    OptimusPrime optimus;
    Megatron megatron;

    Character *player, *computer;

    if (choice == 1) {
        player = &optimus;
        computer = &megatron;
    } else {
        player = &megatron;
        computer = &optimus;
    }

    cout << "\nBattle Begins!\n\n";

    while (player->isAlive() && computer->isAlive()) {
        cout << player->getName() << "'s turn:\n";
        if (player->getName() == "Optimus Prime") {
            dynamic_cast<OptimusPrime*>(player)->showWeapons();
        } else {
            cout << "Choose your weapon:\n1. Fusion Cannon\n2. Dark Saber\n3. Rocket Launcher\n";
        }
        int wChoice;
        cin >> wChoice;
        player->chooseWeaponAndAttack(*computer, wChoice);

        if (!computer->isAlive()) break;

        cout << computer->getName() << "'s turn:\n";
        int cChoice;
        if (computer->getName() == "Megatron") {
            cChoice = dynamic_cast<Megatron*>(computer)->randomChoice();
        } else {
            cChoice = rand() % 3;
        }
        computer->chooseWeaponAndAttack(*player, cChoice);
    }

    cout << "\n=== Battle Over ===\n";
    if (player->isAlive()) {
        cout << player->getName() << " WINS!\n";
    } else {
        cout << computer->getName() << " WINS!\n";
    }

    return 0;
}
