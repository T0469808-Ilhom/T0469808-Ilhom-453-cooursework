# IY 453 Course work stage 1

| Assessment Details | Please Complete All Details              |
| ------------------ | ---------------------------------------- |
| Group              | B                                        |
| Module Title       | IY453 Software Design and Implementation |
| Assessment Type    | Cousrse work                             |
| Module Tutor Name  | Jonathan Shore                           |
| Student ID Number  | P469808                                  |
| Date of Submission | 30.01.2026                               |
| Word Count         | 2000                                     |

- [x] *I confirm that this assignment is my own work. Where I have referred to academic sources, I have provided in-text citations and included the sources in
  the final reference list.*

- [x] *Where I have used AI, I have cited and referenced appropriately.





## Introduction:



The aim of this program is to create an interactive text-based “choose your own adventure” game in C++ that delivers a structured story with branching paths based on the player’s choices. The player progresses through scenes by selecting between two options, with consequences that may lead to success, new routes, item collection, or game over. To enhance gameplay and replayability, the program includes player name personalisation, inventory management with meaningful item effects, puzzle and combat encounters, a scoring system, and save/load features, while applying strong input validation to prevent crashes and handle invalid inputs reliably. 







## Analysis and Design



**Game flow**

- Display an introduction/start menu (New Game / Load Game / Exit).

- Start a new game by asking for the player’s name.

- Present scenes that always provide two options (Option 1 / Option 2).

- Move to the next scene based on the selected option.

- Detect and display Game Over and allow the player to restart.

- Detect and display a win ending and show the final score.

**Input validation**

- Validate all user choices so only valid options are accepted (e.g., 1–2).

- Validate puzzle answers (not empty, correct format if numeric).

- Validate save/load actions (file exists, file format is valid).

- Print clear error messages and re-prompt the user when input is invalid.

**Inventory system**

- Allow the player to collect items during the game.

- Allow the player to view inventory at appropriate times.

- Allow the player to use items (where relevant).

- Items must affect gameplay by:
  
  - modifying health / attack / defense, and/or
  
  - unlocking routes (e.g., “key required” checks).

**Player stats**

- Store and update player stats such as:
  
  - Health (HP)
  
  - Attack (ATK)
  
  - Defense (DEF)

- Ensure stats influence gameplay outcomes (especially combat).

**Puzzle scenarios**

- Include at least one puzzle scenario (e.g., riddle/anagram/math).

- Check the user’s answer and apply consequences:
  
  - reward (score increase, item, route unlock), or
  
  - penalty (HP loss, lower score, harder route).

**Combat scenarios**

- Include at least one combat scenario influenced by player stats and inventory.

- Combat outcome must be determined by a fair rule (stats + randomness).

- Combat must result in either:
  
  - win (score reward, possible item), or
  
  - loss (HP reduction or Game Over).

**Scoring system**

- Track score throughout the game.

- Increase score for completing puzzles, winning combat, or making good decisions.

- Display score at key moments and show a final score at the end.

**Save and load**

- Provide the ability to save and resume the game later.

- Saved data must include:
  
  - player name
  
  - current scene ID (progress point)
  
  - player stats (HP/ATK/DEF)
  
  - score
  
  - inventory contents

- Loading must restore the game to the exact saved state.





## IPO Table

#### Inputs

- Player name (string)

- Scene choice (1 or 2)

- Puzzle answer (string/number)

- Inventory actions ( “use item” choice)

- Save request and filename/slot

- Load request and chosen save file

#### Processes

- Display scene text + two options

- Validate input and re-prompt on invalid entries

- Update current scene based on choice

- Update stats/score/inventory based on consequences

- Run puzzle logic (validate + check answer + apply reward/penalty)

- Run combat logic (calculate outcome using stats + random factor)

- Save state to file and load state from file with validation

#### Outputs

- Scene narrative + options

- Errors for invalid input

- Feedback messages (items gained, HP changed, score changed)

- Inventory display

- Stats and score display

- Game Over screen + restart prompt

- Win screen + final score

- Save/load success/error messages





## Algorithm

![](C:\Users\PC\Pictures\Screenshots\Screenshot%202026-01-30%20113915.png)

 


