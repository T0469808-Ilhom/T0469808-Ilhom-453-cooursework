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





## Introduction:



The aim of this program is to create an interactive text-based “choose your own adventure” game in C++ that delivers a structured story with branching paths based on the player’s choices. The player progresses through scenes by selecting between two options, with consequences that may lead to success, new routes, item collection, or game over. To enhance gameplay and replayability, the program includes player name personalisation, inventory management with meaningful item effects, puzzle and combat encounters, a scoring system, and save/load features, while applying strong input validation to prevent crashes and handle invalid inputs reliably. 







## Analysis and Design

### Game Concept

**The Architect of Threads (original concept inspired by the “almighty designer” trope)**   
The player wakes in a constructed world called the **City of Blueprints**, controlled by a mysterious Architect. Reality is governed by “Threads” (rules). The player must reach the **Core Console** and rewrite one rule to escape. The city contains puzzles, enemies (“Glitches”), and hidden items that influence the path to the final ending.











## Program specification

### Functional requirements

Player interaction and choices

- Present the player with **binary choices** (two options) in each scenario.
  
  

- Some choices must result in **Game Over** and restart, while other choices allow progress toward victory.
  
  

- Provide clear feedback on the consequences of choices.
  
  

- Include **at least 30 binary choices** across the full game.
  
  

**Inventory and items**

- Implement an **inventory** where players can collect, view, and manage items.
  
  

- Include varied item types such as **weapons, clothing/armour, and food**.
  
  …

- Ensure items have meaningful impact by:
  
  - modifying **health / attack / defense**, and/or
  
  - unlocking new paths/choices.
    
    

**Gameplay scenarios**

- Include **puzzle-based scenarios** (riddle/anagram/math).
  
  

- Include **combat-based scenarios** influenced by inventory and stats.
  
  

- Include **item collection scenarios** integrated into the story.
  
  

**Save/load**

- Allow the player to **save progress** and **resume later** using a text or binary file.
  
  

- Save state includes: **player name, current scene, inventory, stats, score**.
  
  

- Provide an intuitive interface for loading saves.
  
  

**Score system**

- Track score and reward the player for:
  
  - solving puzzles and completing challenges
  
  - defeating enemies in combat
    
    

- Display score at key points and show a final score screen.
  
  

**Error handling**

- Validate all user inputs (choices, puzzle answers, save/load).
  
  

- Provide meaningful error messages and prompts to retry.
  
  

#### Non-functional requirements

- Follow OOP principles including **encapsulation**, **inheritance**, and **polymorphism** (e.g., different scene types derived from a base `Scene`).
  
  IY453 Software Design and Imple…

- Simple, consistent text UI with clear instructions (especially for saving/loading).
  
  IY453 Software Design and Imple…

- Must compile and run in **CLion using C++17 or later** (cross-platform where possible).
  
  IY453 Software Design and Imple…

- Maintain work on GitHub with **multiple commits** showing progress over time











## IPO Table

|     |     |     |     |
| --- | --- | --- | --- |
|     |     |     |     |
|     |     |     |     |
|     |     |     |     |















## Algorithm

 


