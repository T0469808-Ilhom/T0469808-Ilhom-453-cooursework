#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <limits>
using namespace std;

class Player {
private:
    string name_;
    int health_;
    int lives_;
    int attack_power_;
    int defense_;
    int score_;
    vector<string> inventory_;

public:
    Player() {
        name_ = "Player";
        health_ = 10;
        lives_ = 3;
        attack_power_ = 4;
        defense_ = 0;
        score_ = 0;
    }

    void SetName(const string& new_name) {
        name_ = new_name;
    }

    string GetName() const {
        return name_;
    }

    int GetHealth() const {
        return health_;
    }

    int GetLives() const {
        return lives_;
    }

    int GetAttackPower() const {
        return attack_power_;
    }

    int GetDefense() const {
        return defense_;
    }

    int GetScore() const {
        return score_;
    }

    void AddScore(int amount) {
        score_ += amount;
    }

    void ChangeHealth(int amount) {
        health_ += amount;

        if (health_ < 0) {
            health_ = 0;
        }
    }

    void ChangeAttackPower(int amount) {
        attack_power_ += amount;

        if (attack_power_ < 0) {
            attack_power_ = 0;
        }
    }

    void ChangeDefense(int amount) {
        defense_ += amount;

        if (defense_ < 0) {
            defense_ = 0;
        }
    }

    void LoseLife() {
        if (lives_ > 0) {
            lives_--;
        }
    }

    void ResetForNewLife() {
        health_ = 10;
    }

    void ResetAll() {
        name_ = "Player";
        health_ = 10;
        lives_ = 3;
        attack_power_ = 4;
        defense_ = 0;
        score_ = 0;
        inventory_.clear();
    }

    void AddItem(const string& item_name, int hp_delta, int atk_delta, int def_delta, int score_delta) {
        inventory_.push_back(item_name);
        health_ += hp_delta;
        attack_power_ += atk_delta;
        defense_ += def_delta;
        score_ += score_delta;

        cout << "You obtained: " << item_name << "\n";

        if (hp_delta != 0) {
            cout << "HP " << (hp_delta > 0 ? "+" : "") << hp_delta << "\n";
        }

        if (atk_delta != 0) {
            cout << "ATK " << (atk_delta > 0 ? "+" : "") << atk_delta << "\n";
        }

        if (def_delta != 0) {
            cout << "DEF " << (def_delta > 0 ? "+" : "") << def_delta << "\n";
        }

        if (score_delta != 0) {
            cout << "Score " << (score_delta > 0 ? "+" : "") << score_delta << "\n";
        }
    }

    bool HasItem(const string& item_name) const {
        for (const string& item : inventory_) {
            if (item == item_name) {
                return true;
            }
        }

        return false;
    }

    void ShowInventory() const {
        cout << "\n--- Inventory ---\n";

        if (inventory_.empty()) {
            cout << "Inventory is empty.\n";
        }
        else {
            for (const string& item : inventory_) {
                cout << "- " << item << "\n";
            }
        }
    }

    void ShowStats() const {
        cout << "\n--- Player Stats ---\n";
        cout << "Name: " << name_ << "\n";
        cout << "Health: " << health_ << "\n";
        cout << "Lives: " << lives_ << "\n";
        cout << "Attack Power: " << attack_power_ << "\n";
        cout << "Defense: " << defense_ << "\n";
        cout << "Score: " << score_ << "\n";
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
    Player player;

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
        case 1: {
            cout << "Start Game selected.\n";

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string player_name;
            cout << "Enter your name: ";
            getline(cin, player_name);

            player.SetName(player_name);

            cout << "\nWelcome to Ravenspire Castle, " << player.GetName() << "!\n";
            player.ShowStats();
            break;
        }

        case 2:
            cout << "Load Game selected.\n";
            break;

        case 3:
            cout << "Exiting game...\n";
            break;
    }

    return 0;
}