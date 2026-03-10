# IY 453 Course work stage 1

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

The aim of this program is to create an interactive text-based “choose your own adventure” game in C++ that delivers a structured story with branching paths based on the player’s choices. The player progresses through scenes by selecting between two options, with consequences that may lead to success, new routes, item collection, or game over. To enhance gameplay and replayability, the program includes player name personalisation, inventory management with meaningful item effects, puzzle and combat encounters, a scoring system, and save/load features, while applying strong input validation to prevent crashes and handle invalid inputs reliably.

## Analysis and Design

#### **Game flow**

- Display an introduction/start menu (New Game / Load Game / Exit).

- Start a new game by asking for the player’s name.

- Present scenes that always provide two options (Option 1 / Option 2).

- Move to the next scene based on the selected option.

- Detect and display Game Over and allow the player to restart.

- Detect and display a win ending and show the final score.

#### **Input validation**

- Validate all user choices so only valid options are accepted (e.g., 1–2).

- Validate puzzle answers (not empty, correct format if numeric).

- Validate save/load actions (file exists, file format is valid).

- Print clear error messages and re-prompt the user when input is invalid.

#### **Inventory system**

- Allow the player to collect items during the game.

- Allow the player to view inventory at appropriate times.

- Allow the player to use items (where relevant).

- Items must affect gameplay by:
  
  - modifying health / attack / defense, and/or
  
  - unlocking routes (e.g., “key required” checks).

#### **Player stats**

- Store and update player stats such as:
  
  - Health (HP)
  
  - Attack (ATK)
  
  - Defense (DEF)

- Ensure stats influence gameplay outcomes (especially combat).

#### **Puzzle scenarios**

- Include at least 2 puzzle scenarios (one riddle/anagram + one math puzzle) to ensure variety.

- Check the user’s answer and apply consequences:
  
  - reward (score increase, item, route unlock), or
  
  - penalty (HP loss, lower score, harder route).

#### **Combat scenarios**

- Include at least one combat scenario influenced by player stats and inventory.

- Combat outcome must be determined by a fair rule (stats + randomness).

- Combat must result in either:
  
  - win (score reward, possible item), or
  
  - loss (HP reduction or Game Over).

#### **Scoring system**

- Track score throughout the game.

- Increase score for completing puzzles, winning combat, or making good decisions.

- Display score at key moments and show a final score at the end.

#### **Save and load**

- Provide the ability to save and resume the game later.

- Saved data must include:
  
  - player name
  
  - current scene ID (progress point)
  
  - player stats (HP/ATK/DEF)
  
  - score
  
  - inventory contents

- Loading must restore the game to the exact saved state.

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


