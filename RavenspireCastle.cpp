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

    /* Setters — clamp values to 0 to prevent negative stats */
    void SetName(const string& new_name) {
        name_ = new_name;
    }

    void SetHealth(int value) {
        health_ = (value < 0) ? 0 : value;
    }

    void SetLives(int value) {
        lives_ = (value < 0) ? 0 : value;
    }

    void SetAttackPower(int value) {
        attack_power_ = (value < 0) ? 0 : value;
    }

    void SetDefense(int value) {
        defense_ = (value < 0) ? 0 : value;
    }

    void SetScore(int value) {
        score_ = (value < 0) ? 0 : value;
    }

    /* Getters */
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

    vector<string> GetInventory() const {
        return inventory_;
    }

    /* Applies a relative change to health using the clamping setter */
    void ChangeHealth(int amount) {
        SetHealth(health_ + amount);
    }

    /* Applies a relative change to attack power using the clamping setter */
    void ChangeAttackPower(int amount) {
        SetAttackPower(attack_power_ + amount);
    }

    /* Applies a relative change to defense using the clamping setter */
    void ChangeDefense(int amount) {
        SetDefense(defense_ + amount);
    }

    void AddScore(int amount) {
        SetScore(score_ + amount);
    }

    void LoseLife() {
        if (lives_ > 0) {
            lives_--;
        }
    }

    /* Restores health to full after losing a life */
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

    void ClearInventory() {
        inventory_.clear();
    }

    /* Adds a single item name to inventory without applying stat effects */
    void AddInventoryItem(const string& item_name) {
        inventory_.push_back(item_name);
    }

    /* Adds item to inventory and immediately applies all its stat bonuses */
    void AddItem(const string& item_name, int hp_delta, int atk_delta,
                 int def_delta, int score_delta) {
        inventory_.push_back(item_name);

        ChangeHealth(hp_delta);
        ChangeAttackPower(atk_delta);
        ChangeDefense(def_delta);
        AddScore(score_delta);

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

    /* const because it only reads inventory, never modifies it */
    bool HasItem(const string& item_name) const {
        bool found = false;

        for (const string& item : inventory_) {
            if (item == item_name) {
                found = true;
            }
        }

        return found;
    }

    void ShowInventory() const {
        cout << "\n--- Inventory ---\n";

        if (inventory_.empty()) {
            cout << "Inventory is empty.\n";
        } else {
            for (const string& item : inventory_) {
                cout << "- " << item << "\n";
            }
        }
    }

    void ShowStats() const {
        cout << "\n--- Player Stats ---\n";
        cout << "Name:         " << name_         << "\n";
        cout << "Health:       " << health_       << "\n";
        cout << "Lives:        " << lives_        << "\n";
        cout << "Attack Power: " << attack_power_ << "\n";
        cout << "Defense:      " << defense_      << "\n";
        cout << "Score:        " << score_        << "\n";
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

    /* Loops until the player enters a valid integer between min and max.
   Centralised here so all scene types share the same validation logic (DRY). */
    int GetValidChoice(int min, int max) {
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
            else if (choice < min || choice > max) {
                cout << "Invalid choice. Please enter " << min << " or " << max << ".\n";
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
        int next_scene_id;

        cout << "\n" << ReplacePlayerName(description_, player) << "\n";
        cout << "1. " << choice_1_ << "\n";
        cout << "2. " << choice_2_ << "\n";

        choice = GetValidChoice(1, 2);

        if (choice == 1) {
            next_scene_id = next_scene_1_;
        }
        else {
            next_scene_id = next_scene_2_;
        }

        return next_scene_id;
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

        choice = GetValidChoice(1, 2);

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
private:
    string choice_1_;
    string choice_2_;
    int next_scene_1_;
    int next_scene_2_;
    string enemy_name_;
    int enemy_power_;
    int enemy_damage_;

public:
    CombatScene(CombatSceneData data) : Scene(data.scene_id, data.description) {
        choice_1_ = data.choice_1;
        choice_2_ = data.choice_2;
        next_scene_1_ = data.next_scene_1;
        next_scene_2_ = data.next_scene_2;
        enemy_name_ = data.enemy_name;
        enemy_power_ = data.enemy_power;
        enemy_damage_ = data.enemy_damage;
    }

    int Play(Player* player) {
        int choice;
        int player_roll;
        int enemy_roll;
        int player_total;
        int enemy_total;
        int next_scene_id;

        cout << "\n--- Combat Scene ---\n";
        cout << ReplacePlayerName(description_, player) << "\n";
        cout << "Enemy: " << enemy_name_ << "\n";
        cout << "1. " << choice_1_ << "\n";
        cout << "2. " << choice_2_ << "\n";

        choice = GetValidChoice(1, 2);

        if (choice == 1) {
            cout << "You chose: " << choice_1_ << "\n";
        }
        else {
            cout << "You chose: " << choice_2_ << "\n";
        }

        player_roll = rand() % 6 + 1;
        enemy_roll = rand() % 6 + 1;

        player_total = player->GetAttackPower() + player->GetDefense() + player_roll;
        enemy_total = enemy_power_ + enemy_roll;

        cout << player->GetName() << " total: " << player_total << "\n";
        cout << enemy_name_ << " total: " << enemy_total << "\n";

        if (player_total >= enemy_total) {
            cout << "You defeated " << enemy_name_ << ".\n";
            player->AddScore(10);
            next_scene_id = next_scene_1_;
        }
        else {
            cout << "You were hit by " << enemy_name_ << ".\n";
            player->ChangeHealth(-enemy_damage_);
            next_scene_id = next_scene_2_;

            if (player->GetHealth() <= 0) {
                player->LoseLife();

                if (player->GetLives() <= 0) {
                    cout << "You have no lives left.\n";
                    next_scene_id = -1;
                }
                else {
                    cout << "You lost a life.\n";
                    player->ResetForNewLife();
                }
            }
        }

        return next_scene_id;
    }
};

class ItemScene : public Scene {
private:
    string choice_1_;
    string choice_2_;
    int next_scene_1_;
    int next_scene_2_;
    string item_name_;
    int health_bonus_;
    int attack_bonus_;
    int defense_bonus_;
    int score_bonus_;
    string unlock_tag_;

public:
    ItemScene(ItemSceneData data) : Scene(data.scene_id, data.description) {
        choice_1_ = data.choice_1;
        choice_2_ = data.choice_2;
        next_scene_1_ = data.next_scene_1;
        next_scene_2_ = data.next_scene_2;
        item_name_ = data.item_name;
        health_bonus_ = data.health_bonus;
        attack_bonus_ = data.attack_bonus;
        defense_bonus_ = data.defense_bonus;
        score_bonus_ = data.score_bonus;
        unlock_tag_ = data.unlock_tag;
    }

    int Play(Player* player) {
        int choice;
        int next_scene_id;

        cout << "\n--- Item Scene ---\n";

        // Check if the player carries the required item for this scene.
        // Reward them with bonus score for being prepared.
        if (unlock_tag_ != "" && player->HasItem(unlock_tag_)) {
            cout << "Your " << unlock_tag_ << " reacts to this place. Bonus score!\n";
            player->AddScore(5);
        }

        cout << ReplacePlayerName(description_, player) << "\n";
        cout << "1. " << choice_1_ << "\n";
        cout << "2. " << choice_2_ << "\n";

        choice = GetValidChoice(1, 2);

        if (choice == 1) {
            player->AddItem(item_name_, health_bonus_, attack_bonus_, defense_bonus_, score_bonus_);
            next_scene_id = next_scene_1_;
        }
        else {
            cout << "You left the item behind.\n";
            next_scene_id = next_scene_2_;
        }

        return next_scene_id;
    }
};

class Game {
private:
    Player player_;
    vector<StorySceneData> story_scenes_;
    vector<PuzzleSceneData> puzzle_scenes_;
    vector<CombatSceneData> combat_scenes_;
    vector<ItemSceneData> item_scenes_;
    SceneLoader scene_loader_;
    int current_scene_id_;
    int scene_counter_;

    //Loops until the player enters a valid integer between min and max.
    //Centralised here so all scene types share the same validation logic.
    int GetValidChoice(int min, int max) {
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
            else if (choice < min || choice > max) {
                cout << "Invalid choice. Please enter " << min << " or " << max << ".\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                valid_choice = true;
            }
        }

        return choice;
    }


    bool IsEndingScene(int scene_id) {
        bool is_ending = (scene_id == 41 || scene_id == 42 || scene_id == 43);
        return is_ending;
    }

    void LoadAllScenes() {
        story_scenes_ = scene_loader_.LoadStoryScenes("scenes.csv");
        puzzle_scenes_ = scene_loader_.LoadPuzzleScenes("puzzleScene.csv");
        combat_scenes_ = scene_loader_.LoadCombatScenes("combatScene.csv");
        item_scenes_ = scene_loader_.LoadItemScenes("itemScene.csv");
    }

    void SaveGame() {
        ofstream file("savegame.csv");
        vector<string> inventory;

        if (!file.is_open()) {
            cout << "Error: could not save the game.\n";
        }
        else {
            file << player_.GetName() << "\n";
            file << current_scene_id_ << "\n";
            file << player_.GetHealth() << ","
                 << player_.GetLives() << ","
                 << player_.GetAttackPower() << ","
                 << player_.GetDefense() << ","
                 << player_.GetScore() << "\n";

            inventory = player_.GetInventory();
            file << inventory.size() << "\n";

            for (int i = 0; i < inventory.size(); i++) {
                file << inventory[i] << "\n";
            }

            file.close();
            cout << "Game saved successfully.\n";
        }
    }

    bool LoadSaveFile() {
        ifstream file("savegame.csv");
        string line;
        vector<string> stats;
        int item_count;
        bool loaded = false;

        if (!file.is_open()) {
            cout << "Error: could not open savegame.csv\n";
        }
        else {
            getline(file, line);

            if (line == "") {
                cout << "Error: save file is empty.\n";
            }
            else {
                player_.ResetAll();
                player_.SetName(line);

                getline(file, line);
                current_scene_id_ = stoi(line);

                getline(file, line);
                stats = scene_loader_.SplitCsvLine(line);

                if (stats.size() != 5) {
                    cout << "Error: save file data is invalid.\n";
                }
                else {
                    player_.SetHealth(stoi(stats[0]));
                    player_.SetLives(stoi(stats[1]));
                    player_.SetAttackPower(stoi(stats[2]));
                    player_.SetDefense(stoi(stats[3]));
                    player_.SetScore(stoi(stats[4]));

                    getline(file, line);
                    item_count = stoi(line);
                    player_.ClearInventory();

                    for (int i = 0; i < item_count; i++) {
                        getline(file, line);
                        player_.AddInventoryItem(line);
                    }

                    loaded = true;
                }
            }

            file.close();
        }

        return loaded;
    }

    bool PlayCurrentScene() {
        StorySceneData story_data = scene_loader_.GetStorySceneById(story_scenes_, current_scene_id_);
        PuzzleSceneData puzzle_data = scene_loader_.GetPuzzleSceneById(puzzle_scenes_, current_scene_id_);
        CombatSceneData combat_data = scene_loader_.GetCombatSceneById(combat_scenes_, current_scene_id_);
        ItemSceneData item_data = scene_loader_.GetItemSceneById(item_scenes_, current_scene_id_);
        bool scene_found = true;

        if (story_data.scene_id != -1) {
            StoryScene scene(story_data);
            current_scene_id_ = scene.Play(&player_);
        }
        else if (puzzle_data.scene_id != -1) {
            PuzzleScene scene(puzzle_data);
            current_scene_id_ = scene.Play(&player_);
        }
        else if (combat_data.scene_id != -1) {
            CombatScene scene(combat_data);
            current_scene_id_ = scene.Play(&player_);
        }
        else if (item_data.scene_id != -1) {
            ItemScene scene(item_data);
            current_scene_id_ = scene.Play(&player_);
        }
        else {
            cout << "\nScene " << current_scene_id_ << " was not found.\n";
            scene_found = false;
        }

        return scene_found;
    }

    void ShowFinalScoreIfNeeded(int previous_scene_id) {
        if (IsEndingScene(previous_scene_id)) {
            cout << "\n--- Final Score ---\n";
            cout << player_.GetName() << ", your final score is: " << player_.GetScore() << "\n";
        }
    }

    bool AskToSave() {
        int choice;
        int next_choice;
        bool return_to_menu = false;

        cout << "\nDo you want to save the game?\n";
        cout << "1. Yes\n";
        cout << "2. No\n";

        choice = GetValidChoice(1, 2);

        if (choice == 1) {
            SaveGame();

            cout << "\nWhat do you want to do now?\n";
            cout << "1. Return to Main Menu\n";
            cout << "2. Continue Playing\n";

            next_choice = GetValidChoice(1, 2);

            if (next_choice == 1) {
                return_to_menu = true;
            }
        }

        return return_to_menu;
    }

    bool HandleSceneResult(int previous_scene_id) {
        bool keep_playing = true;

        if (current_scene_id_ == -1) {
            cout << "\nGame Over.\n";
            keep_playing = false;
        }
        else if (current_scene_id_ == 1 && IsEndingScene(previous_scene_id)) {
            string player_name = player_.GetName();

            player_.ResetAll();
            player_.SetName(player_name);
            current_scene_id_ = 1;
            scene_counter_ = 0;

            cout << "\nStarting a new game...\n";
            player_.ShowStats();
        }
        else {
            player_.ShowStats();

            if (scene_counter_ > 0 && scene_counter_ % 5 == 0) {
                if (AskToSave()) {
                    cout << "\nReturning to Main Menu...\n";
                    keep_playing = false;
                }
            }
        }

        return keep_playing;
    }

    void PlayGame() {
        int previous_scene_id;
        bool game_running = true;
        bool scene_played;

        while (game_running) {
            previous_scene_id = current_scene_id_;
            scene_played = PlayCurrentScene();

            if (!scene_played) {
                game_running = false;
            }
            else {
                scene_counter_++;
                ShowFinalScoreIfNeeded(previous_scene_id);
                game_running = HandleSceneResult(previous_scene_id);
            }
        }
    }
public:
    Game() {
        current_scene_id_ = 1;
        scene_counter_ = 0;
    }

    void StartGame() {
        string player_name;

        cout << "Enter your name: ";
        getline(cin, player_name);

        if (player_name == "") {
            player_name = "Player";
        }

        player_.ResetAll();
        player_.SetName(player_name);
        current_scene_id_ = 1;
        scene_counter_ = 0;

        LoadAllScenes();

        cout << "\nWelcome to Ravenspire Castle, " << player_.GetName() << "!\n";
        player_.ShowStats();

        PlayGame();
    }

    void LoadGame() {
        LoadAllScenes();

        if (LoadSaveFile()) {
            scene_counter_ = 0;

            cout << "\nGame loaded successfully.\n";
            cout << "Welcome back, " << player_.GetName() << "!\n";
            player_.ShowStats();

            PlayGame();
        }
    }

    void Run() {
        int choice;
        bool running = true;

        while (running) {
            cout << "\n--- RAVENSPIRE CASTLE ---\n";
            cout << "1. Start Game\n";
            cout << "2. Load Game\n";
            cout << "3. Exit\n";

            choice = GetValidChoice(1, 3);

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
                    running = false;
                    break;
            }
        }
    }
};

int main() {
    Game game;
    game.Run();
    return 0;
}