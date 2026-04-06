# IY 453 Course work

| Assessment Details | Please Complete All Details              |
| ------------------ | ---------------------------------------- |
| Group              | B                                        |
| Module Title       | IY453 Software Design and Implementation |
| Assessment Type    | Cousrse work                             |
| Module Tutor Name  | Jonathan Shore                           |
| Student ID Number  | P469808                                  |
| Date of Submission | 30.01.2026                               |

- [x] *I confirm that this assignment is my own work. Where I have referred to academic sources, I have provided in-text citations and included the sources in
  the final reference list.*

- [x] *Where I have used AI, I have cited and referenced appropriately.





## Table of Contents

[Introduction: 3](#_Toc226400620)

[Analysis and design: 4](#_Toc226400621)

[Program specifications: 4](#_Toc226400622)

[IPO table: 6](#_Toc226400623)

[Algorithms: 10](#_Toc226400624)

[Testing: 18](#_Toc226400625)

[Test table: 18](#_Toc226400626)

[Annotation Screenshots: 23](#_Toc226400627)

[Technical elements: 33](#_Toc226400628)

[Evaluation: 35](#_Toc226400629)

[References: 38](#_Toc226400630)

[Appendix code listing: 39](#_Toc226400631)

## Introduction:

This report documents the design, development and testing of a text-based adventure game created as part of the IY453 Software Design and Implementation module. The game is called Ravenspire and is written in C++.

The idea behind a text-based adventure game is simple: the player reads a description of a situation and chooses between two options. Each choice leads somewhere different, and those decisions shape the outcome of the game. There are no graphics or animations just text, decisions and consequences. 

Ravenspire puts the player in the role of a prisoner waking up in a cell beneath a castle with no memory of how they got there. The goal is to escape. Along the way the player encounters puzzles, combat, items to collect and traps to survive. There are three possible endings depending on the choices made and the items collected throughout the game.

The program was built using object-oriented programming principles. Game data such as scenes, items and combat encounters are stored in CSV files and loaded at runtime, which keeps the code flexible and the story easy to update without changing the program itself.

## Analysis and Design

 



## Program specifications:

#### **Functional requirements:**

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

### Algorithm:

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_1.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_2.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_3.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_4.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_5.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_6.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_7.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_8.png)

![](https://github.com/T0469808-Ilhom/T0469808-Ilhom-453-cooursework/blob/main/Flowchart_9.png)

### Class Diagram:

#### Testing

The program was tested using black box testing. Only the inputs entered by the user and the outputs shown by the program were examined. Each input was tested at least four times using valid, invalid, boundary and edge case data.

## Testing

The program was tested using black box testing. This means the tests only examined the values entered by the user and the outputs produced by the program. The internal code was not used during testing.

## Testing

The program was tested using black box testing. This means the tests only examined the values entered by the user and the outputs produced by the program. The internal code was not used during testing.

| No. | Input           | Test description               | Test data    | Expected output                              | Actual output                                                                                                   | Pass/Fail |
| --- | --------------- | ------------------------------ | ------------ | -------------------------------------------- | --------------------------------------------------------------------------------------------------------------- | --------- |
| 1   | Main menu       | Exact valid  start game        | 1            | Asks for player name and starts the game     | Asked for player name and started the game                                                                      | Pass      |
| 2   | Main menu       | Exact valid  load game         | 2            | Loads the saved game and resumes             | Loaded the saved game at the correct scene                                                                      | Pass      |
| 3   | Main menu       | Exact valid exit               | 3            | Exits the program cleanly                    | Exited with goodbye message                                                                                     | Pass      |
| 4   | Main menu       | Out of range  too high         | 4            | Error shown and re-prompted                  | Error shown and re-prompted                                                                                     | Pass      |
| 5   | Main menu       | Out of range  too low          | 0            | Error shown and re-prompted                  | Error shown and re-prompted                                                                                     | Pass      |
| 6   | Main menu       | Negative number                | -1           | Error shown and re-prompted                  | Error shown and re-prompted                                                                                     | Pass      |
| 7   | Main menu       | Letter only                    | abc          | Error shown and re-prompted                  | Error shown, buffer cleared, re-prompted                                                                        | Pass      |
| 8   | Main menu       | Input with trailing letters    | 1abc         | Error shown and re-prompted                  | Program accepted 1 and ignored abc  cin >> reads until whitespace so trailing characters are left in the buffer | Fail      |
| 9   | Main menu       | Decimal number                 | 1.5          | Error shown and re-prompted                  | Program accepted 1 and left .5 in the buffer  same cin >> behaviour as test 8                                   | Fail      |
| 10  | Main menu       | Very large number              | 99999        | Error shown and re-prompted                  | Error shown and re-prompted                                                                                     | Pass      |
| 11  | Player name     | Standard name                  | Ilhom        | Name accepted and used throughout the game   | Name appeared correctly in welcome message and story text                                                       | Pass      |
| 12  | Player name     | Name with a space              | Ali Khan     | Full name accepted and displayed correctly   | Full name displayed correctly throughout                                                                        | Pass      |
| 13  | Player name     | Blank — press Enter            | (empty)      | Program uses default name Player             | Program used Player as the default                                                                              | Pass      |
| 14  | Player name     | Numbers only                   | 12345        | Accepted as a valid name                     | Accepted and used correctly                                                                                     | Pass      |
| 15  | Player name     | Special characters             | @#!          | Accepted as a valid name                     | Accepted and used correctly                                                                                     | Pass      |
| 16  | Player name     | Single character               | A            | Accepted as a valid name                     | Accepted and used correctly                                                                                     | Pass      |
| 17  | Player name     | Very long name                 | Thisverylong | Accepted as a valid name                     | Accepted and used correctly                                                                                     | Pass      |
| 18  | Scene choice    | Valid choice 1 in story scene  | 1            | Moves to the first linked scene              | Moved to the correct next scene                                                                                 | Pass      |
| 19  | Scene choice    | Valid choice 1 in puzzle scene | 1            | Correct answer result applied, score added   | Score increased and game continued                                                                              | Pass      |
| 20  | Scene choice    | Valid choice 1 in item scene   | 1            | Item added to inventory                      | Item added and inventory shown                                                                                  | Pass      |
| 21  | Scene choice    | Valid choice 1 in combat scene | 1            | Combat runs and stats update                 | Combat completed and stats updated                                                                              | Pass      |
| 22  | Scene choice    | Valid choice 2 in story scene  | 2            | Moves to the second linked scene             | Moved to the correct next scene                                                                                 | Pass      |
| 23  | Scene choice    | Valid choice 2 in puzzle scene | 2            | Health penalty applied                       | Health reduced by correct amount                                                                                | Pass      |
| 24  | Scene choice    | Valid choice 2 in item scene   | 2            | Item left and game continues                 | Left-item message shown and game continued                                                                      | Pass      |
| 25  | Scene choice    | Valid choice 2 in combat scene | 2            | Combat runs and stats update                 | Combat completed and stats updated                                                                              | Pass      |
| 26  | Scene choice    | Save  uppercase                | S            | Game saved and returns to menu               | Saved successfully and returned to menu                                                                         | Pass      |
| 27  | Scene choice    | Save  lowercase                | s            | Same as uppercase                            | Saved successfully and returned to menu                                                                         | Pass      |
| 28  | Scene choice    | Exit  uppercase                | E            | Program closes immediately                   | Program closed immediately                                                                                      | Pass      |
| 29  | Scene choice    | Exit  lowercase                | e            | Same as uppercase                            | Program closed immediately                                                                                      | Pass      |
| 30  | Scene choice    | Out of range number            | 3            | Error shown and re-prompted for 1, 2, S or E | Error shown and re-prompted                                                                                     | Pass      |
| 31  | Scene choice    | Very large number              | 99999        | Error shown and re-prompted                  | Error shown and re-prompted                                                                                     | Pass      |
| 32  | Scene choice    | Random letter                  | x            | Error shown and re-prompted                  | Error shown and re-prompted                                                                                     | Pass      |
| 33  | Scene choice    | Empty input                    | (empty)      | Error shown and re-prompted                  | Error shown and re-prompted                                                                                     | Pass      |
| 34  | Scene choice    | Special characters             | @#!          | Error shown and re-prompted                  | Error shown and re-prompted                                                                                     | Pass      |
| 35  | Scene choice    | Input with trailing letters    | 1abc         | Error shown and re-prompted                  | Program rejected 1abc  getline reads the full string so it does not match 1 or 2 and the error is shown         | Pass      |
| 36  | Scene choice    | Negative number                | -1           | Error shown and re-prompted                  | Error shown and re-prompted                                                                                     | Pass      |
| 37  | Inventory check | Valid  show inventory          | 1            | Inventory displayed then combat opens        | Inventory shown and combat opened                                                                               | Pass      |
| 38  | Inventory check | Valid  skip inventory          | 2            | Inventory skipped and combat opens           | Skipped and combat opened                                                                                       | Pass      |
| 39  | Inventory check | Out of range                   | 3            | Error shown and re-prompted                  | Error shown and re-prompted                                                                                     | Pass      |
| 40  | Inventory check | Letter                         | abc          | Error shown and re-prompted                  | Error shown, buffer cleared, re-prompted                                                                        | Pass      |
| 41  | Inventory check | Negative number                | -1           | Error shown and re-prompted                  | Error shown and re-prompted                                                                                     | Pass      |
| 42  | Inventory check | Input with trailing letters    | 1abc         | Error shown and re-prompted                  | Program accepted 1 and ignored abc  same cin >> limitation as test 8                                            | Fail      |

### 

### 



## Annotation Screenshots:



Screenshot – 1:

![]()



This screenshot shows the main menu displayed when the program starts.
The title Ravenspire Castle is printed at the top. The user is presented with
three options: start a new game, load a saved game, or exit. The program waits
for the user to enter 1, 2 or 3 and will reject anything else and re-prompt.





Screenshot – 2:

![]()

This screenshot shows the program asking the player to enter their name
after selecting Start Game. The name is stored in the Player class and used
throughout the game in scene descriptions and messages. If the player presses
Enter without typing anything, the program defaults to the name Player.





Screenshots – 3:

![]()



This screenshot shows an item scene where the player has chosen to pick
up the item. The item name is added to the inventory, and the score bonuses are
applied immediately. The updated inventory is shown so the player can see what
they are carrying.





Screenshot – 4:

![]()



This screenshot shows a puzzle scene with the sub-type displayed above
the description. The player must choose between two options one is correct and
awards score, the other is wrong and reduces health. The correct answer is
stored in the CSV and checked in PuzzleScene:Play.



Screenshot – 5:

![]()



This screenshot shows a combat scene. The player's attack power is
combined with a random number between 1 and 6 to produce the player total. The
enemy power is also combined with a random number to produce the enemy total.
The higher total wins. If the player loses, health is reduced by the enemy
damage value.





Screenshot – 6:

![]()



This screenshot shows a story scene loaded from scenes.csv. The
description is displayed and the player is given two choices. At the bottom the
program reminds the player they can type S to save and return to the menu or E
to exit the program immediately.





Screenshots – 7:

![]()



This screenshot shows the result of choosing the wrong answer in a
puzzle scene. The program displays the health penalty and shows the new health
value. If health reaches zero the player loses a life and health is restored to

100 If all lives are lost the game ends.





Screenshot – 8:

![]()



This screenshot shows an item scene where the player has chosen to pick
up the item. The item name is added to the inventory and the stat bonuses are
applied immediately. The updated inventory is shown so the player can see what
they are carrying.



Screenshot – 9:

![]()



This screenshot shows the save prompt which appears automatically every
5 scenes. The player can choose to save and return to the main menu or continue
playing. If they save, the game state is written to savegame.txt including the
player name, current scene, health, lives, attack power, score and inventory.





Screenshot – 10:

![]()



This screenshot shows the program loading a saved game. The save file is
read line by line and all player data is restored. The game resumes at the
exact scene where the player saved so no progress is lost.



Screenshot – 11:

![]()





This screenshot shows what happens when the player enters something
invalid such as a letter or a number outside the valid range. The program
displays an error message and re-prompts without crashing.





## Technical elements:

The Player class stores the main player data,
including the name, health, lives, attack power, score, and inventory. These
values are kept as private member variables, which means they cannot be changed
directly from outside the class. This helps protect the data and makes sure
that changes happen in a controlled way through the class methods.

Four structs are used as simple data containers:
StorySceneData, PuzzleSceneData, CombatSceneData, and ItemSceneData. Each one
stores one row of scene data loaded from a CSV file. Structs are suitable here
because their purpose is only to hold data.

The SceneLoader class is responsible for reading
the scene files. It loads the CSV data, splits each row into fields, and stores
the result in the correct struct type. This allows the scene content to stay
outside the main code, which makes the story easier to edit and manage.

The Scene class is an abstract base class used
to represent a general scene. It provides shared features that all scene types
need, such as input checking and player name replacement. It also defines the
Play function as a pure virtual function, which means every derived class must
implement its own version. This is an example of polymorphism the game loop can
call Play on any scene type without knowing in advance which type it is, which
makes the program flexible and easy to extend.

The four derived scene classes are StoryScene,
PuzzleScene, CombatScene, and ItemScene. Each class has a different role in the
game. StoryScene is used for normal story progression, PuzzleScene handles
puzzle-based choices, CombatScene manages battles, and ItemScene allows the
player to collect items and gain bonuses. Separating these scene types makes
the program easier to organise and understand.

Key variables used across the program include
current_scene_id_ which tracks which scene the player is currently in, and
scene_counter_ which counts how many scenes have been played and is used to
trigger the save prompt every five scenes. The variable valid_choice is used as
a controller in while loops across the program to avoid using while(true),
keeping the loop logic clear and predictable. The variable next_scene_id is
declared at the start of each Play method and set before it is returned, which
ensures there is always a single return statement at the end of the function.

The program also uses methods to divide tasks
into smaller parts. This makes the code easier to read, test, and maintain.
Different methods are used for loading files, validating input, saving
progress, and running scenes, so each part of the program has a clear purpose.

Input validation is an important technical
element in the program. The GetValidChoice method is used to check that the
player enters only allowed values. This reduces the chance of invalid input
causing problems and helps the game continue safely.

The Game class controls the overall flow of the
program. It manages the main menu, starts a new game, loads saved progress,
runs the main game loop, and decides which scene should be played next. It also
handles special cases such as saving, exiting, and game over.

The SaveGame and LoadSaveFile functions are used
to store and restore the player's progress. This allows the user to leave the
game and continue later from the same point. Save and load functionality is
important because it improves usability and supports longer gameplay.

Vectors are used in several parts of the
program. The inventory is stored as a vector of strings so items can be added
dynamically as the player picks them up. The loaded scene data for each scene
type is also stored in a vector so any number of scenes can be loaded from the
CSV without knowing the size in advance. Vectors are more flexible than
fixed-size arrays because they grow automatically as data is added.



# Evaluation:

**Does the program meet the assignment brief?**

The program meets most of the requirements. It has a working text-based
adventure game with binary choices in every scene, four scene types: story,
puzzle, combat and item a save and load system that writes to a text file, a
score system, input validation throughout, and a player name that appears in
the story text. The game uses object-oriented paradigm with a base Scene class
and four derived classes, inheritance, encapsulation and polymorphism through
the virtual Play method. All scenes are loaded from CSV files at runtime. The
main requirement that is only partially met is items unlocking new paths the
unlock_tag field exists in ItemSceneData and is loaded from the CSV, but in the
current code it only prints a message saying the item could be important later
rather than actually changing which route the player can take.

**Strengths:**

The first strength is the CSV-based scene system. All story content,
puzzle answers, enemy stats and item bonuses are stored in external files. This
means the entire game story can be changed or extended without touching the
code. It also means the code and content are fully separated, which makes both
easier to maintain.

The second strength is input validation. The Scene class uses getline to
read input and checks it against exactly the values 1, 2, S and E. If the input
does not match, the error message is shown and the prompt repeats. The Game
class uses cin with buffer clearing for the main menu. Neither input point
allows the program to crash or move forward on invalid input.

The third strength is the save and load system. When the player presses
S during a scene, the current scene ID is restored to the previous scene before
saving so the game loads back at the right point. The save file uses labelled
fields like name= and scene= which makes it easy to read and debug. The load
function reads each label using substr to strip the prefix before converting
the value.

**Weaknesses:**

The first weakness is that the combat outcome in not fully randomised. Because
it was noticed that most of the time the player wins the battel however the
outcome of the combats meant to be randomised.  The program takes 2 random numbers adds them
to both player and enemy, but the winner mostly is the player.

The second weakness is the exit command. When the player types E during
a scene the program closes immediately through exit (0) without saving progress
or giving any warning. If the player presses E by accident or forgets they have
unsaved progress, everything since the last save is gone with no way to recover
it. A better approach would be to show a warning message first and ask the
player to confirm before closing or at least offer them the option to save
before exiting.

**Areas of improvement:**

One improvement would be to make the unlock_tag system actually change
the story path. Currently the field is loaded and stored but only used to print
a message. A better implementation would check whether the player has the
required item and does that item block or unlock a specific choice, which would
make collecting items feel genuinely important to progression.

The second area for improvement is the randomised battle system. At the
moment, the game uses randomness to decide the result of a fight, but the
player can also collect weapons that increase attack power. Because of this, it
is difficult to make every battle a true 50/50 chance for both sides. In most
cases, one side will have at least a small advantage. This means the combat
system could be improved by balancing the damage of weapons, enemy power, and
random values more carefully.

**Issues encountered in testing:**

An issue found during testing was the way the main menu handled some
invalid inputs. Because the menu uses cin >> choice, inputs such as 1abc
were partly accepted as valid. The program read only the number 1 and ignored
the remaining letters, which means the input was not checked properly. This was
recorded as a failed test because the program should have rejected the whole
input and asked the user to try again.

**Lessons learned:**

One thing that worked well
was storing the scene data in CSV files from the beginning. This made the story
much easier to manage because scenes, puzzle answers, and item values could be
changed without rewriting large parts of the code. It also made the game
content more organised and easier to expand.

One thing that did not work
well was adding the inline save and exit commands later in development. Because
these options were introduced after the main scene system had already been
built, extra logic had to be added to several parts of the program. This made
the code more complicated than it needed to be. It would have been better to
plan these commands earlier so they could be built naturally into the scene
system from the start.

If I started the project
again, I would use getline for the main menu from the beginning so that all
user input could be handled in a more consistent way. I would also plan the
item and unlock system more carefully so that collected items had a stronger effect
on the paths available to the player. This would make the game feel more
complete and would improve both the gameplay and the overall design.



<style>
</style>

# References:

Cppreference. (2023a). std::basic_ifstream. Retrieved from: [https://en.cppreference.com/w/cpp/io/basic_ifstream.html](https://en.cppreference.com/w/cpp/io/basic_ifstream.html?utm_source=chatgpt.com) [Accessed 24 March 2026].

Cppreference. (2023b). std::basic_ofstream. Retrieved from: [https://en.cppreference.com/w/cpp/io/basic_ofstream.html](https://en.cppreference.com/w/cpp/io/basic_ofstream.html?utm_source=chatgpt.com) [Accessed 25 March 2026].

Cppreference. (2025a). std::rand. Retrieved from: [https://en.cppreference.com/w/cpp/numeric/random/rand.html](https://en.cppreference.com/w/cpp/numeric/random/rand.html?utm_source=chatgpt.com) [Accessed 29 March 2026].

Cppreference. (2025b). std::vector. Retrieved from: [https://en.cppreference.com/w/cpp/container/vector.html](https://en.cppreference.com/w/cpp/container/vector.html?utm_source=chatgpt.com) [Accessed 27 March 2026].

Cppreference. (2025c). virtual function specifier. Retrieved from: [https://en.cppreference.com/w/cpp/language/virtual.html](https://en.cppreference.com/w/cpp/language/virtual.html?utm_source=chatgpt.com) [Accessed 28 March 2026].

Microsoft. (2021). Classes and Structs (C++). Retrieved from: [https://learn.microsoft.com/en-us/cpp/cpp/classes-and-structs-cpp?view=msvc-170](https://learn.microsoft.com/en-us/cpp/cpp/classes-and-structs-cpp?view=msvc-170&utm_source=chatgpt.com) [Accessed 27 March 2026].

International Software Testing Qualifications Board. (2024). Certified
Tester Foundation Level Syllabus. Retrieved from: [https://istqb.org/?download_id=3345&sdm_process_download=1](https://istqb.org/?download_id=3345&sdm_process_download=1&utm_source=chatgpt.com) [Accessed 2 April 2026].

IBM. (n.d.). Virtual member functions (C++ only). Retrieved from: [https://www.ibm.com/docs/en/xl-c-and-cpp-aix/13.1.3?topic=only-virtual-member-functions-c](https://www.ibm.com/docs/en/xl-c-and-cpp-aix/13.1.3?topic=only-virtual-member-functions-c&utm_source=chatgpt.com) [Accessed 29 March 2026].

Open AI. Model: Thinking. Prompt: Create narrative story for the following
project make sure the number of scenes are above 30: [Accessed 18 march 2026.]





# Appendix code listing:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <cstdlib>


using namespace std;


/* Holds everything about the player — health, lives, attack and score.
   All values are controlled so they never drop below zero. */
class Player {
private:
    string name_;
    int health_;
    int lives_;
    int attack_power_;
    int score_;
    vector<string> inventory_;

public:
    Player() {
        name_ = "Player";
        health_ = 100;
        lives_ = 3;
        attack_power_ = 10;
        score_ = 0;
    }

    /* Setters — clamp values to 0 to prevent negative stats */
    void SetName(const string& new_name) {
        name_ = new_name;
    }

    void SetHealth(int value) {
        if (value < 0) { health_ = 0; }
        else if (value > 100) { health_ = 100; }
        else { health_ = value; }
    }

    void SetLives(int value) {
        if (value < 0) { lives_ = 0; }
        else if (value > 3) { lives_ = 3; }
        else { lives_ = value; }
    }

    void SetAttackPower(int value) {
        if (value < 0) { attack_power_ = 0; }
        else { attack_power_ = value; }
    }

    void SetScore(int value) {
        if (value < 0) { score_ = 0; }
        else { score_ = value; }
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
        health_ = 100;
    }

    void ResetAll() {
        name_ = "Player";
        health_ = 100;
        lives_ = 3;
        attack_power_ = 10;
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
    void AddItem(const string& item_name, int hp_delta, int atk_delta, int score_delta) {
        inventory_.push_back(item_name);

        ChangeHealth(hp_delta);
        ChangeAttackPower(atk_delta);
        AddScore(score_delta);

        cout << "You obtained: " << item_name << "\n";

        if (hp_delta != 0) {
            cout << "HP " << (hp_delta > 0 ? "+" : "") << hp_delta << "\n";
        }

        if (atk_delta != 0) {
            cout << "ATK " << (atk_delta > 0 ? "+" : "") << atk_delta << "\n";
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
        cout << "\n=====  Inventory =====\n";

        if (inventory_.empty()) {
            cout << "\n Inventory is empty.\n";
        } else {
            for (const string& item : inventory_) {
                cout << "- " << item << "\n";
            }
        }
    }

    void ShowStats() const {
        cout << "\n===== PLAYER STATS =====\n";
        cout << "Name:         " << name_         << "\n";
        cout << "Health:       " << health_       << "\n";
        cout << "Lives:        " << lives_        << "\n";
        cout << "Attack Power: " << attack_power_ << "\n";
        cout << "Score:        " << score_        << "\n";
        cout << "\n";
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
    int score_bonus;
    string unlock_tag;
};

/* Handles all file reading for the game.
    Scene data lives in CSV files so the story can be changed without touching the code. */
class SceneLoader {
public:
    /* Breaks a CSV line into separate fields.
   Handles fields that contain commas inside quotes so descriptions load correctly. */
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

                if (fields.size() == 11) {
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
                    scene.score_bonus = stoi(fields[9]);
                    scene.unlock_tag = fields[10];

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

/* Base class for all scene types.
   Derived classes only need to implement Play().
   Input and name replacement are handled here. */
class Scene {
protected:
    int scene_id_;
    string description_;

    // Used during scenes accepts 1 or 2 as choices, S to save and E to exit.
    // Returns -2 for save and -3 for exit so the game loop can handle them.
    int GetValidChoice(int min, int max) {
        string input;
        int choice = 0;
        bool valid_choice = false;

        while (!valid_choice) {
            cout << "\n[S = Save and go to menu | E = Exit game]\n";
            cout << "Enter your choice: ";
            getline(cin, input);

            if (input == "S" || input == "s") {
                choice = -2;
                valid_choice = true;
            }
            else if (input == "E" || input == "e") {
                choice = -3;
                valid_choice = true;
            }
            else if (input == "1" || input == "2") {
                choice = stoi(input);
                valid_choice = true;
            }
            else {
                cout << "Invalid choice. Please enter 1, 2, S or E.\n";
            }
        }

        return choice;
    }

    /* Looks for the placeholder {player_name} in the scene text and swaps it
   with the actual player name so descriptions feel personal. */
    string ReplacePlayerName(string text, Player* player) {
        size_t position = text.find("{player_name}");

        if (position < text.length()) {
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
        cout << "\n ==== Story scene ==== \n ";
        cout << "\n" << ReplacePlayerName(description_, player) << "\n";
        cout << "\n";
        cout << "1. " << choice_1_ << "\n";
        cout << "2. " << choice_2_ << "\n";

        choice = GetValidChoice(1, 2);

        if (choice == -2 || choice == -3) {
            next_scene_id = choice;
        }
        else if (choice == 1) {
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

        cout << "\n=== Puzzle Scene ===\n";
        cout << "Type: " << sub_type_ << "\n";
        cout << ReplacePlayerName(description_, player) << "\n";
        cout << "1. " << choice_1_ << "\n";
        cout << "2. " << choice_2_ << "\n";

        choice = GetValidChoice(1, 2);

        // If player chose to save or exit pass the signal straight back
        if (choice == -2 || choice == -3) {
            next_scene_id = choice;
        }
        else {
            // Set next scene from choice first so it always has a valid value
            if (choice == 1) {
                next_scene_id = next_scene_1_;
            }
            else {
                next_scene_id = next_scene_2_;
            }

            if (choice == correct_choice_) {
                cout << "Correct! You earned " << score_reward_ << " score.\n";
                player->AddScore(score_reward_);
                cout << "Score is now: " << player->GetScore() << "\n";
            }
            else {
                cout << "Wrong answer. You lose " << damage_if_wrong_ << " health.\n";
                player->ChangeHealth(-damage_if_wrong_);
                cout << "Health is now: " << player->GetHealth() << "\n";

                // If health hits zero lose a life — only game over when all lives gone
                if (player->GetHealth() <= 0) {
                    player->LoseLife();

                    if (player->GetLives() <= 0) {
                        cout << "You have no lives left.\n";
                        next_scene_id = -1;
                    }
                    else {
                        cout << "You lost a life. Lives remaining: " << player->GetLives() << "\n";
                        player->ResetForNewLife();
                        cout << "Health restored to: " << player->GetHealth() << "\n";
                    }
                }
            }
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

        cout << "\n ===== Combat Scene =====\n";
        cout << ReplacePlayerName(description_, player) << "\n";
        cout << "Enemy: " << enemy_name_ << "\n";
        cout << "1. " << choice_1_ << "\n";
        cout << "2. " << choice_2_ << "\n";

        choice = GetValidChoice(1, 2);

        if (choice == -2 || choice == -3) {
            next_scene_id = choice;
        }
        else {
            if (choice == 1) {
                cout << "You chose: " << choice_1_ << "\n";
            }
            else {
                cout << "You chose: " << choice_2_ << "\n";
            }

            player_roll = rand() % 6 + 1;
            enemy_roll = rand() % 6 + 1;

            player_total = player->GetAttackPower() + player_roll;
            enemy_total = enemy_power_ + enemy_roll;

            cout << player->GetName() << " total: " << player_total << "\n";
            cout << enemy_name_ << " total: " << enemy_total << "\n";

            if (player_total >= enemy_total) {
                cout << "You defeated " << enemy_name_ << ".\n";
                player->AddScore(10);
                cout << "Score is now: " << player->GetScore() << "\n";
                next_scene_id = next_scene_1_;
            }
            else {
                cout << "You were hit by " << enemy_name_ << ". You lose " << enemy_damage_ << " health.\n";
                player->ChangeHealth(-enemy_damage_);
                cout << "Health is now: " << player->GetHealth() << "\n";
                next_scene_id = next_scene_2_;

                if (player->GetHealth() <= 0) {
                    player->LoseLife();

                    if (player->GetLives() <= 0) {
                        cout << "You have no lives left.\n";
                        next_scene_id = -1;
                    }
                    else {
                        cout << "You lost a life. Lives remaining: " << player->GetLives() << "\n";
                        player->ResetForNewLife();
                        cout << "Health restored to: " << player->GetHealth() << "\n";
                    }
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
        score_bonus_ = data.score_bonus;
        unlock_tag_ = data.unlock_tag;
    }

    int Play(Player* player) {
        int choice;
        int next_scene_id;

        cout << "\n===== Item Scene =====\n";

        // If this item has a special role in the story, note it for the player.
        if (unlock_tag_ != "" && unlock_tag_ != "none") {
            cout << "This item could be important later.\n";
        }

        cout << ReplacePlayerName(description_, player) << "\n";
        cout << "1. " << choice_1_ << "\n";
        cout << "2. " << choice_2_ << "\n";

        choice = GetValidChoice(1, 2);


        if (choice == -2 || choice == -3) {
            next_scene_id = choice;
        }
        else if (choice == 1) {
            player->AddItem(item_name_, health_bonus_, attack_bonus_, score_bonus_);
            player->ShowInventory();
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

    // Used for the main menu only accepts numbers between min and max.
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
        bool is_ending = (scene_id == 44 || scene_id == 45 || scene_id == 46);
        return is_ending;
    }

    void LoadAllScenes() {
        story_scenes_ = scene_loader_.LoadStoryScenes("scenes.csv");
        puzzle_scenes_ = scene_loader_.LoadPuzzleScenes("puzzleScene.csv");
        combat_scenes_ = scene_loader_.LoadCombatScenes("combatScene.csv");
        item_scenes_ = scene_loader_.LoadItemScenes("itemScene.csv");
    }

    void SaveGame() {
        ofstream file("savegame.txt");
        vector<string> inventory;

        if (!file.is_open()) {
            cout << "Error: could not save the game.\n";
        }
        else {
            file << "name=" << player_.GetName() << "\n";
            file << "scene=" << current_scene_id_ << "\n";
            file << "health=" << player_.GetHealth() << "\n";
            file << "lives=" << player_.GetLives() << "\n";
            file << "attack=" << player_.GetAttackPower() << "\n";
            file << "score=" << player_.GetScore() << "\n";

            inventory = player_.GetInventory();
            file << "items=" << inventory.size() << "\n";

            for (int i = 0; i < inventory.size(); i++) {
                file << inventory[i] << "\n";
            }

            file.close();
            cout << "Game saved successfully.\n";
        }
    }

    /* Reads the save file and restores the player back to where they left off.
   Returns false if the file is missing or the data does not look right. */
    bool LoadSaveFile() {
        ifstream file("savegame.txt");
        string line;
        int item_count;
        bool loaded = false;

        if (!file.is_open()) {
            cout << "Error: could not open savegame.txt\n";
        }
        else {
            player_.ResetAll();

            getline(file, line);
            player_.SetName(line.substr(5));

            getline(file, line);
            current_scene_id_ = stoi(line.substr(6));

            getline(file, line);
            player_.SetHealth(stoi(line.substr(7)));

            getline(file, line);
            player_.SetLives(stoi(line.substr(6)));

            getline(file, line);
            player_.SetAttackPower(stoi(line.substr(7)));

            getline(file, line);
            player_.SetScore(stoi(line.substr(6)));

            getline(file, line);
            item_count = stoi(line.substr(6));
            player_.ClearInventory();

            for (int i = 0; i < item_count; i++) {
                getline(file, line);
                player_.AddInventoryItem(line);
            }

            loaded = true;
            file.close();
        }

        return loaded;
    }

    /* Finds the right scene type for the current ID.
   Puzzle, combat and item are checked before story so they always take priority. */

    bool PlayCurrentScene() {
        StorySceneData story_data = scene_loader_.GetStorySceneById(story_scenes_, current_scene_id_);
        PuzzleSceneData puzzle_data = scene_loader_.GetPuzzleSceneById(puzzle_scenes_, current_scene_id_);
        CombatSceneData combat_data = scene_loader_.GetCombatSceneById(combat_scenes_, current_scene_id_);
        ItemSceneData item_data = scene_loader_.GetItemSceneById(item_scenes_, current_scene_id_);
        bool scene_found = true;

        if (puzzle_data.scene_id != -1) {
            PuzzleScene scene(puzzle_data);
            current_scene_id_ = scene.Play(&player_);
        }
        else if (combat_data.scene_id != -1) {
            // Offer inventory check before combat so player can see their items
            if (!player_.GetInventory().empty()) {
                cout << "\nCheck inventory before the fight? 1. Yes  2. No\n";
                int inv_choice = GetValidChoice(1, 2);

                if (inv_choice == 1) {
                    player_.ShowInventory();
                }
            }

            CombatScene scene(combat_data);
            current_scene_id_ = scene.Play(&player_);
        }
        else if (item_data.scene_id != -1) {
            ItemScene scene(item_data);
            current_scene_id_ = scene.Play(&player_);
        }
        else if (story_data.scene_id != -1) {
            StoryScene scene(story_data);
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

/* Decides what happens after each scene ends.
   Handles game over, story endings, and the save or exit signals from the player. */
    bool HandleSceneResult(int previous_scene_id) {
        bool keep_playing = true;

        if (current_scene_id_ == -1) {
            cout << "\nGame Over.\n";
            keep_playing = false;
        }
        else if (current_scene_id_ == -2) {
            // Restore the previous scene before saving so the player
            // returns to the right place when they load the game.
            current_scene_id_ = previous_scene_id;
            SaveGame();
            cout << "Game saved. Returning to main menu.\n";
            keep_playing = false;
        }
        else if (current_scene_id_ == -3) {
            cout << "Goodbye!\n";
            exit(0);
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
            cout << "\n==== RAVENSPIRE CASTLE ====\n";
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

```
