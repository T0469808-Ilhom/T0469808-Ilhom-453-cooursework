# IY 453 Course work

| Assessment Details | Please Complete All Details              |
| ------------------ | ---------------------------------------- |
| Group              | B                                        |
| Module Title       | IY453 Software Design and Implementation |
| Assessment Type    | Cousrse work                             |
| Module Tutor Name  | Jonathan Shore                           |
| Student ID Number  | P469808                                  |
| Date of Submission | 30.01.2026                               |
| Word Count         |                                          |



- [x] *I confirm that this assignment is my own work. Where I have referred to academic sources, I have provided in-text citations and included the sources in
  the final reference list.*

- [x] *Where I have used AI, I have cited and referenced appropriately.





## Introduction:

This report documents the design, development and testing of a text-based adventure game created as part of the IY453 Software Design and Implementation module. The game is called Ravenspire and is written in C++.

The idea behind a text-based adventure game is simple: the player reads a description of a situation and chooses between two options. Each choice leads somewhere different, and those decisions shape the outcome of the game. There are no graphics or animations just text, decisions and consequences. 

Ravenspire puts the player in the role of a prisoner waking up in a cell beneath a castle with no memory of how they got there. The goal is to escape. Along the way the player encounters puzzles, combat, items to collect and traps to survive. There are three possible endings depending on the choices made and the items collected throughout the game.

The program was built using object-oriented programming principles. Game data such as scenes, items and combat encounters are stored in CSV files and loaded at runtime, which keeps the code flexible and the story easy to update without changing the program itself.

## Analysis and Design

### **Functional requirements:**

1. Player Name: The program captures the
   player's name at the start and uses it throughout the all game.

2. Binary Choices: Every scene presents exactly
   two choices. The player must enter a valid option to proceed.

3. Lives System: The player begins with three
   lives. Reaching a game over scene costs one life. Losing all three ends the
   game permanently.

4. Scene Structure: The game contains 46 scenes
   across four types: navigation, combat, puzzle and item. All scene data is
   loaded from CSV files at runtime.

5. Inventory System: The player can collect
   items that affect health, attack power and defence. Some items unlock specific
   story paths that cannot be accessed without them.

6. Combat System: Combat scenes pitting the
   player against an enemy. The outcome is determined by comparing the player's
   attack power against the enemy's power with a random element applied to both.

7. Puzzle System: Puzzle scenes present riddles,
   anagrams or mathematical challenges. Incorrect answers cost health, trigger
   traps or end the game depending on the puzzle.

8. Save and Load: The player can save their
   current state at any point. The save file stores name, current scene,
   inventory, health, attack power, defence, score and remaining lives.

9. Score System: Points are awarded for
   defeating enemies, solving puzzles and collecting key items. The score is
   displayed throughout and shown in full on the final screen.

10. Error Handling: All invalid inputs are
    caught and handled without crashing. File loading errors are reported cleanly
    without terminating the program.

### **Non-functional requirements:**

1. Code Quality: The program follows
   object-oriented programming principles using a base Scene class with
   CombatScene, PuzzleScene and ItemScene derived through inheritance.
   Polymorphism is applied through virtual functions to handle each scene type.

2. Compatibility: The program compiles and runs
   using the C++17 standard or later in the CLion IDE and is compatible with
   Windows, macOS and Linux where possible.

3. Performance: All file reading, input handling
   and game logic executes without noticeable delay in response to player input.

4. Documentation: All classes, methods and key
   sections of code are clearly commented on throughout the program.

5. Version Control: All code and documentation is
   managed on GitHub with a consistent commit history demonstrating the
   progression of the project across all four development stages.

## Inputs, Processes and Outputs (IPO Table)

| Feature                | Inputs                                                                 | Processing                                                                                                                                                                            | Outputs                                                                                    |
| ---------------------- | ---------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| Start program          | Program launch                                                         | Create the Game object and open the main menu loop.                                                                                                                                   | Main menu displayed.                                                                       |
| Display main menu      | User menu choice (1–3)                                                 | Show the options Start Game, Load Game, and Exit, then validate the input so only allowed values are accepted.                                                                        | Selected menu option opened or error message shown.                                        |
| Start new game         | Player name                                                            | Reset player data to default values, store the player name, set the first scene ID, load all scene files, and begin the game loop.                                                    | Welcome message, starting stats, and first scene displayed.                                |
| Load saved game        | Save file (savegame.txt)                                               | Open the save file, read saved values, restore player name, current scene, stats, score, and inventory, then continue the game from that point.                                       | Saved game loaded or error message shown.                                                  |
| Load story scene data  | scenes.csv                                                             | Read the CSV file, skip the header row, split each line into fields, convert values to the correct data types, and store the scenes in a vector.                                      | Story scenes loaded into memory or file error shown.                                       |
| Load puzzle scene data | puzzleScene.csv                                                        | Read and validate puzzle scene data from the CSV file and store it in a vector for later access.                                                                                      | Puzzle scenes loaded into memory or file error shown.                                      |
| Load combat scene data | combatScene.csv                                                        | Read and validate combat scene data from the CSV file and store it in a vector for later access.                                                                                      | Combat scenes loaded into memory or file error shown.                                      |
| Load item scene data   | itemScene.csv                                                          | Read and validate item scene data from the CSV file and store it in a vector for later access.                                                                                        | Item scenes loaded into memory or file error shown.                                        |
| Find current scene     | Current scene ID                                                       | Search the loaded scene collections and identify whether the current scene is a story, puzzle, combat, or item scene.                                                                 | Correct scene object created and played, or scene not found message shown.                 |
| Play story scene       | Current scene data, player choice (1 or 2)                             | Show the scene description and two choices, replace {player_name} with the real player name, validate the input, and move to the next linked scene.                                   | Next scene ID selected or save/exit signal returned.                                       |
| Play puzzle scene      | Puzzle scene data, player choice (1 or 2)                              | Show the puzzle text and choices, validate the answer, reward score if correct, or reduce health if wrong, then move to the linked next scene.                                        | Updated score or health, next scene ID, or game over if lives reach zero.                  |
| Play combat scene      | Combat scene data, player choice (1 or 2), player stats, random values | Show the enemy and choices, calculate player and enemy totals using attack power plus a random roll, compare results, apply score reward or health damage, and decide the next scene. | Combat result shown, stats updated, next scene selected, or game over if lives reach zero. |
| Play item scene        | Item scene data, player choice (1 or 2)                                | Show the item scene, allow the player to take or leave the item, update inventory and player stats if collected, then move to the linked next scene.                                  | Item collected or left behind, updated inventory/stats, next scene selected.               |
| Add item to inventory  | Item name, health bonus, attack bonus, score bonus                     | Add the item name to the inventory vector and apply all related stat changes through the player methods.                                                                              | Item added message and updated player stats shown.                                         |
| Show inventory         | Current inventory data                                                 | Check whether the inventory is empty and display either the stored items or an empty inventory message.                                                                               | Inventory list or inventory is empty message shown.                                        |
| Show player stats      | Player name, health, lives, attack power, score                        | Read the current player values and format them clearly for display.                                                                                                                   | Current player stats shown.                                                                |
| Validate menu input    | User keyboard input                                                    | Check whether the input is numeric and within the valid range. If not, clear the error state and ask again.                                                                           | Valid menu choice accepted or error message shown.                                         |
| Validate scene input   | User keyboard input (1, 2, S, E)                                       | Check whether the entered value is one of the allowed options for scene play. If invalid, re-prompt until a valid option is entered.                                                  | Valid scene choice accepted or error message shown.                                        |
| Save game              | Current player data, current scene ID, inventory                       | Open the save file, write player name, scene, stats, score, and inventory contents in text format, then close the file safely.                                                        | Save confirmation or save error message shown.                                             |
| Handle life loss       | Player health, player lives                                            | If health drops to zero, reduce lives by one. If lives remain, restore health for the new life; otherwise end the game.                                                               | Life lost message, health reset, or final game over message shown.                         |
| Handle ending scene    | Current scene progression, final score                                 | Detect whether the player has reached one of the final scenes and display the final score before resetting or ending.                                                                 | Final score screen shown.                                                                  |
| Exit to main menu      | Player input S during scene                                            | Save the game state, restore the previous scene ID so progress is preserved correctly, and return to the main menu.                                                                   | Save confirmation and main menu shown.                                                     |
| Exit program           | User menu choice or E during scene                                     | End the menu loop or terminate the program safely.                                                                                                                                    | Goodbye message and program closed.                                                        |

## Algorithm:

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_1.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_2.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_3.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_4.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_5.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_6.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_7.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_8.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_9.png)

## Class Diagram:
