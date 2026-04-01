#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <cstdlib>

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

    void SetName(string new_name) {
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

    void AddItem(string item_name, int hp_delta, int atk_delta, int def_delta, int score_delta) {
        inventory_.push_back(item_name);

        health_ += hp_delta;
        attack_power_ += atk_delta;
        defense_ += def_delta;
        score_ += score_delta;

        if (health_ < 0) {
            health_ = 0;
        }

        if (attack_power_ < 0) {
            attack_power_ = 0;
        }

        if (defense_ < 0) {
            defense_ = 0;
        }

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

    bool HasItem(string item_name) {
        bool found = false;

        for (int i = 0; i < inventory_.size(); i++) {
            if (inventory_[i] == item_name) {
                found = true;
            }
        }

        return found;
    }

    void ShowInventory() const {
        cout << "\n--- Inventory ---\n";

        if (inventory_.empty()) {
            cout << "Inventory is empty.\n";
        }
        else {
            for (int i = 0; i < inventory_.size(); i++) {
                cout << "- " << inventory_[i] << "\n";
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

struct StorySceneData {
    int scene_id;
    string description;
    string choice_1;
    string choice_2;
    int next_scene_1;
    int next_scene_2;
};

struct PuzzleSceneData {
    int scene_id;
    string sub_type;
    string description;
    string choice_1;
    string choice_2;
    int next_scene_1;
    int next_scene_2;
    int correct_choice;
    int damage_if_wrong;
    int score_reward;
};

struct CombatSceneData {
    int scene_id;
    string description;
    string choice_1;
    string choice_2;
    int next_scene_1;
    int next_scene_2;
    string enemy_name;
    int enemy_power;
    int enemy_damage;
};

struct ItemSceneData {
    int scene_id;
    string description;
    string choice_1;
    string choice_2;
    int next_scene_1;
    int next_scene_2;
    string item_name;
    int health_bonus;
    int attack_bonus;
    int defense_bonus;
    int score_bonus;
    string unlock_tag;
};

class SceneLoader {
public:
    vector<string> SplitCsvLine(string line) {
        vector<string> fields;
        string current_field;
        bool inside_quotes = false;

        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '"') {
                inside_quotes = !inside_quotes;
            }
            else if (line[i] == ',' && inside_quotes == false) {
                fields.push_back(current_field);
                current_field = "";
            }
            else {
                current_field = current_field + line[i];
            }
        }

        fields.push_back(current_field);
        return fields;
    }

    vector<StorySceneData> LoadStoryScenes(string file_name) {
        vector<StorySceneData> story_scenes;
        ifstream file(file_name);
        string line;

        if (!file.is_open()) {
            cout << "Error: could not open " << file_name << "\n";
        }
        else {
            getline(file, line);

            while (getline(file, line)) {
                vector<string> fields = SplitCsvLine(line);

                if (fields.size() == 6) {
                    StorySceneData scene;
                    scene.scene_id = stoi(fields[0]);
                    scene.description = fields[1];
                    scene.choice_1 = fields[2];
                    scene.choice_2 = fields[3];
                    scene.next_scene_1 = stoi(fields[4]);
                    scene.next_scene_2 = stoi(fields[5]);

                    story_scenes.push_back(scene);
                }
            }

            file.close();
        }

        return story_scenes;
    }

    vector<PuzzleSceneData> LoadPuzzleScenes(string file_name) {
        vector<PuzzleSceneData> puzzle_scenes;
        ifstream file(file_name);
        string line;

        if (!file.is_open()) {
            cout << "Error: could not open " << file_name << "\n";
        }
        else {
            getline(file, line);

            while (getline(file, line)) {
                vector<string> fields = SplitCsvLine(line);

                if (fields.size() == 10) {
                    PuzzleSceneData scene;
                    scene.scene_id = stoi(fields[0]);
                    scene.sub_type = fields[1];
                    scene.description = fields[2];
                    scene.choice_1 = fields[3];
                    scene.choice_2 = fields[4];
                    scene.next_scene_1 = stoi(fields[5]);
                    scene.next_scene_2 = stoi(fields[6]);
                    scene.correct_choice = stoi(fields[7]);
                    scene.damage_if_wrong = stoi(fields[8]);
                    scene.score_reward = stoi(fields[9]);

                    puzzle_scenes.push_back(scene);
                }
            }

            file.close();
        }

        return puzzle_scenes;
    }

    vector<CombatSceneData> LoadCombatScenes(string file_name) {
        vector<CombatSceneData> combat_scenes;
        ifstream file(file_name);
        string line;

        if (!file.is_open()) {
            cout << "Error: could not open " << file_name << "\n";
        }
        else {
            getline(file, line);

            while (getline(file, line)) {
                vector<string> fields = SplitCsvLine(line);

                if (fields.size() == 9) {
                    CombatSceneData scene;
                    scene.scene_id = stoi(fields[0]);
                    scene.description = fields[1];
                    scene.choice_1 = fields[2];
                    scene.choice_2 = fields[3];
                    scene.next_scene_1 = stoi(fields[4]);
                    scene.next_scene_2 = stoi(fields[5]);
                    scene.enemy_name = fields[6];
                    scene.enemy_power = stoi(fields[7]);
                    scene.enemy_damage = stoi(fields[8]);

                    combat_scenes.push_back(scene);
                }
            }

            file.close();
        }

        return combat_scenes;
    }

    vector<ItemSceneData> LoadItemScenes(string file_name) {
        vector<ItemSceneData> item_scenes;
        ifstream file(file_name);
        string line;

        if (!file.is_open()) {
            cout << "Error: could not open " << file_name << "\n";
        }
        else {
            getline(file, line);

            while (getline(file, line)) {
                vector<string> fields = SplitCsvLine(line);

                if (fields.size() == 12) {
                    ItemSceneData scene;
                    scene.scene_id = stoi(fields[0]);
                    scene.description = fields[1];
                    scene.choice_1 = fields[2];
                    scene.choice_2 = fields[3];
                    scene.next_scene_1 = stoi(fields[4]);
                    scene.next_scene_2 = stoi(fields[5]);
                    scene.item_name = fields[6];
                    scene.health_bonus = stoi(fields[7]);
                    scene.attack_bonus = stoi(fields[8]);
                    scene.defense_bonus = stoi(fields[9]);
                    scene.score_bonus = stoi(fields[10]);
                    scene.unlock_tag = fields[11];

                    item_scenes.push_back(scene);
                }
            }

            file.close();
        }

        return item_scenes;
    }

    StorySceneData GetStorySceneById(vector<StorySceneData> story_scenes, int scene_id) {
        StorySceneData found_scene;
        found_scene.scene_id = -1;

        for (int i = 0; i < story_scenes.size(); i++) {
            if (story_scenes[i].scene_id == scene_id) {
                found_scene = story_scenes[i];
            }
        }

        return found_scene;
    }

    PuzzleSceneData GetPuzzleSceneById(vector<PuzzleSceneData> puzzle_scenes, int scene_id) {
        PuzzleSceneData found_scene;
        found_scene.scene_id = -1;

        for (int i = 0; i < puzzle_scenes.size(); i++) {
            if (puzzle_scenes[i].scene_id == scene_id) {
                found_scene = puzzle_scenes[i];
            }
        }

        return found_scene;
    }

    CombatSceneData GetCombatSceneById(vector<CombatSceneData> combat_scenes, int scene_id) {
        CombatSceneData found_scene;
        found_scene.scene_id = -1;

        for (int i = 0; i < combat_scenes.size(); i++) {
            if (combat_scenes[i].scene_id == scene_id) {
                found_scene = combat_scenes[i];
            }
        }

        return found_scene;
    }

    ItemSceneData GetItemSceneById(vector<ItemSceneData> item_scenes, int scene_id) {
        ItemSceneData found_scene;
        found_scene.scene_id = -1;

        for (int i = 0; i < item_scenes.size(); i++) {
            if (item_scenes[i].scene_id == scene_id) {
                found_scene = item_scenes[i];
            }
        }

        return found_scene;
    }
};

class Scene {
protected:
    int scene_id_;
    string description_;

    int GetValidChoice() {
        int choice;
        bool valid_choice = false;

        while (!valid_choice) {
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (choice < 1 || choice > 2) {
                cout << "Invalid choice. Please enter 1 or 2.\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                valid_choice = true;
            }
        }

        return choice;
    }

    string ReplacePlayerName(string text, Player* player) {
        size_t position = text.find("{player_name}");

        if (position != string::npos) {
            text.replace(position, 13, player->GetName());
        }

        return text;
    }

public:
    Scene(int scene_id, string description) {
        scene_id_ = scene_id;
        description_ = description;
    }

    int GetSceneId() const {
        return scene_id_;
    }

    string GetDescription() const {
        return description_;
    }

    virtual int Play(Player* player) = 0;
};

class StoryScene : public Scene {
private:
    string choice_1_;
    string choice_2_;
    int next_scene_1_;
    int next_scene_2_;

public:
    StoryScene(StorySceneData data) : Scene(data.scene_id, data.description) {
        choice_1_ = data.choice_1;
        choice_2_ = data.choice_2;
        next_scene_1_ = data.next_scene_1;
        next_scene_2_ = data.next_scene_2;
    }

    int Play(Player* player) {
        int choice;

        cout << "\n" << ReplacePlayerName(description_, player) << "\n";
        cout << "1. " << choice_1_ << "\n";
        cout << "2. " << choice_2_ << "\n";

        choice = GetValidChoice();

        if (choice == 1) {
            return next_scene_1_;
        }
        else {
            return next_scene_2_;
        }
    }
};

class PuzzleScene : public Scene {
private:
    string sub_type_;
    string choice_1_;
    string choice_2_;
    int next_scene_1_;
    int next_scene_2_;
    int correct_choice_;
    int damage_if_wrong_;
    int score_reward_;

public:
    PuzzleScene(PuzzleSceneData data) : Scene(data.scene_id, data.description) {
        sub_type_ = data.sub_type;
        choice_1_ = data.choice_1;
        choice_2_ = data.choice_2;
        next_scene_1_ = data.next_scene_1;
        next_scene_2_ = data.next_scene_2;
        correct_choice_ = data.correct_choice;
        damage_if_wrong_ = data.damage_if_wrong;
        score_reward_ = data.score_reward;
    }

    int Play(Player* player) {
        int choice;
        int next_scene_id;

        cout << "\n--- Puzzle Scene ---\n";
        cout << "Type: " << sub_type_ << "\n";
        cout << ReplacePlayerName(description_, player) << "\n";
        cout << "1. " << choice_1_ << "\n";
        cout << "2. " << choice_2_ << "\n";

        choice = GetValidChoice();

        if (choice == correct_choice_) {
            cout << "Correct answer.\n";
            player->AddScore(score_reward_);
        }
        else {
            cout << "Wrong answer. You lose " << damage_if_wrong_ << " health.\n";
            player->ChangeHealth(-damage_if_wrong_);
        }

        if (choice == 1) {
            next_scene_id = next_scene_1_;
        }
        else {
            next_scene_id = next_scene_2_;
        }

        return next_scene_id;
    }
};

class CombatScene : public Scene {

};

class ItemScene : public Scene {

};

class Game {
private:
    Player player_;
    vector<StorySceneData> story_scenes_;
    vector<PuzzleSceneData> puzzle_scenes_;
    vector<CombatSceneData> combat_scenes_;
    vector<ItemSceneData> item_scenes_;
    SceneLoader scene_loader_;

    int GetValidMenuChoice() {
        int choice;
        bool valid_choice = false;

        while (!valid_choice) {
            cout << "\n--- RAVENSPIRE CASTLE ---\n";
            cout << "1. Start Game\n";
            cout << "2. Load Game\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (choice < 1 || choice > 3) {
                cout << "Invalid choice. Please enter 1, 2, or 3.\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                valid_choice = true;
            }
        }

        return choice;
    }

public:
    void StartGame() {
        string player_name;
        StorySceneData first_scene;

        cout << "Enter your name: ";
        getline(cin, player_name);

        if (player_name == "") {
            player_name = "Player";
        }

        player_.ResetAll();
        player_.SetName(player_name);

        story_scenes_ = scene_loader_.LoadStoryScenes("scenes.csv");
        puzzle_scenes_ = scene_loader_.LoadPuzzleScenes("puzzleScene.csv");
        combat_scenes_ = scene_loader_.LoadCombatScenes("combatScene.csv");
        item_scenes_ = scene_loader_.LoadItemScenes("itemScene.csv");

        cout << "\nWelcome to Ravenspire Castle, " << player_.GetName() << "!\n";
        player_.ShowStats();

        first_scene = scene_loader_.GetStorySceneById(story_scenes_, 1);

        if (first_scene.scene_id == -1) {
            cout << "Error: first scene not found.\n";
        }
        else {
            StoryScene story_scene(first_scene);
            int next_scene_id = story_scene.Play(&player_);

            cout << "Next scene id: " << next_scene_id << "\n";
        }
    }

    void LoadGame() {
        cout << "Load Game selected.\n";
    }

    void Run() {
        int choice = GetValidMenuChoice();

        switch (choice) {
            case 1:
                cout << "Start Game selected.\n";
                StartGame();
                break;

            case 2:
                LoadGame();
                break;

            case 3:
                cout << "Exiting game...\n";
                break;
        }
    }
};

int main() {
    Game game;
    game.Run();
    return 0;
}