#include <iostream>
#include <vector>
#include <string>
#include <random>



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


class Scene {

};


class PuzzleScene {
    public:

};


class CombatScene {

};

class ItemScene {

};