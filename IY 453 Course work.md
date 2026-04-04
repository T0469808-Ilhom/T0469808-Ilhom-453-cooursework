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

## Contents

- [Introduction](#introduction)
- [Analysis and Design](#analysis-and-design)
  - [Program Specification](#program-specification)
  - [IPO Table](#ipo-table)
  - [Algorithms](#algorithms)
  - [Flowcharts](#flowcharts)
  - [Class Diagram](#class-diagram)
- [References](#references)

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

5.  Version Control: All code and documentation is
   managed on GitHub with a consistent commit history demonstrating the
   progression of the project across all four development stages.

## IPO Table

| Feature                      | Inputs                                       | Processing                                                                                                         | Outputs                                                                           |
| ---------------------------- | -------------------------------------------- | ------------------------------------------------------------------------------------------------------------------ | --------------------------------------------------------------------------------- |
| Show start menu & get choice | User menu choice (1–3)                       | Display start menu, read input, validate range; if invalid show error and re-prompt.                               | A valid menu option selected (1–3).                                               |
| Choice 1: Start new game     | User menu choice = 1, player name (string)   | Ask for player name, validate not empty, initialise starting stats/score/inventory, set starting scene.            | Welcome message using player name + first scene displayed.                        |
| Choice 2: Load game          | User menu choice = 2, filename/slot (string) | Validate file exists, read saved state, validate format, restore player stats/score/inventory and current scene.   | Load success message + resumed scene OR load error message.                       |
| Choice 3: Exit game          | User menu choice = 3                         | End the program cleanly.                                                                                           | Goodbye message.                                                                  |
| Play a scene (binary choice) | Scene choice (1 or 2)                        | Display scene narrative + 2 options, validate input, apply consequences, move to next scene.                       | Next scene displayed + consequence message (and score/stats updated if relevant). |
| Puzzle scenario              | Puzzle answer (string/number)                | Ask puzzle question, validate input, check answer, apply reward/penalty and decide next route.                     | Correct/incorrect feedback + updated score/stats + next scene.                    |
| Combat scenario              | Combat choice (e.g., 1 = Fight, 2 = Run)     | Validate input, calculate combat using stats + randomness, apply HP/score changes, decide next route or Game Over. | Combat outcome message + updated HP/score + next scene OR Game Over.              |
| View inventory               | Inventory request (Y/N)                      | If requested, display inventory list and return to gameplay.                                                       | Inventory list OR “inventory empty” message.                                      |
| Use item                     | Item selection (item number)                 | Validate selection, apply item effect (heal/buff/unlock), remove item if consumable.                               | Confirmation message + updated stats/route access.                                |
| Save game                    | Save choice (Y/N), filename/slot (string)    | Validate filename/slot, write game state to file, handle errors safely.                                            | Save success message OR save error message.                                       |

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
