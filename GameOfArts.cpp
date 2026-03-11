#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <limits>
using namespace std;

class Player {
private:
    string name;
    int health;
    int lives;
    int attack_power;
    int score;
    vector<string> inventory;

public:
    Player() {
        name = "Player";
        health = 10;
        lives = 3;
        attack_power = 4;
        score = 0;
    }

    void SetName(const string& newName) {
        name = newName;
    }

    string GetName() const {
        return name;
    }

    int GetHealth() const {
        return health;
    }

    int GetLives() const {
        return lives;
    }

    int GetAttackPower() const {
        return attack_power;
    }

    int GetScore() const {
        return score;
    }

    void AddScore(int amount) {
        score += amount;
    }

    void ChangeHealth(int amount) {
        health += amount;
    }

    void ChangeAttackPower(int amount) {
        attack_power += amount;
    }

    void LoseLife() {
        lives--;
    }

    void ResetForNewLife() {
        health = 10;
    }

    void ResetAll() {
        health = 10;
        lives = 3;
        attack_power = 4;
        score = 0;
        inventory.clear();
    }

    void AddItem(const string& itemName, int hpDelta, int atkDelta, int scoreDelta) {
        inventory.push_back(itemName);
        health += hpDelta;
        attack_power += atkDelta;
        score += scoreDelta;

        cout << "You obtained: " << itemName << "\n";
        if (hpDelta != 0) {
            cout << "HP " << (hpDelta > 0 ? "+" : "") << hpDelta << "\n";
        }
        if (atkDelta != 0) {
            cout << "ATK " << (atkDelta > 0 ? "+" : "") << atkDelta << "\n";
        }
        if (scoreDelta != 0) {
            cout << "Score " << (scoreDelta > 0 ? "+" : "") << scoreDelta << "\n";
        }
    }
};

class Scene { };

class PuzzleScene {
public:
};

class CombatScene { };

class ItemScene { };


int main() {

        int choice;

        do {
            cout << "\n--- RAVENSPIRE CASTLE ---\n";
            cout << "1. Start Game\n";
            cout << "2. Load Game\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = 0;
                cout << "Invalid input. Please enter a number.\n";
            }
            else if (choice < 1 || choice > 3) {
                cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            }

        } while (choice < 1 || choice > 3);

        switch (choice) {
            case 1:
                cout << "Start Game selected.\n";
                break;

            case 2:
                cout << "Load Game selected.\n";
                break;

            case 3:
                cout << "Exiting game...\n";
                break;
        }

        return 0;
    }

