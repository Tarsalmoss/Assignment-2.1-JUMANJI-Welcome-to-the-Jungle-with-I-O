
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <random>
#include <ctime>

using namespace std;

// Create a random number generator for random events.
mt19937 rng(static_cast<unsigned int>(time(nullptr)));

// Store the player's health.
int health = 100;

// Store the player's inventory.
vector<string> inventory;

// Store whether the player has escaped.
bool gameOver = false;

// Store whether the player has the ancient key.
bool hasKey = false;

// Store whether the player has the jungle map.
bool hasMap = false;

// Store whether the player has defeated the guardian.
bool guardianDefeated = false;

// Display a decorative line.
void line()
{
    cout << "==================================================\n";
}

// Display the game title.
void title()
{
    line();
    cout << "             JUMANJI: THE LOST JUNGLE\n";
    line();
}

// Pause the game until the player presses Enter.
void pauseGame()
{
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Collect a valid number from the player.
int getChoice(int minimum, int maximum)
{
    int choice;

    // Continue asking until the player enters a valid choice.
    while (true)
    {
        cout << "\nYour choice: ";

        // Check whether the player entered a number.
        if (cin >> choice)
        {
            // Check whether the number is within the allowed range.
            if (choice >= minimum && choice <= maximum)
            {
                return choice;
            }
        }

        // Clear invalid input from the console.
        cout << "Invalid input! Please enter a number between "
             << minimum << " and " << maximum << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Display the player's current health and inventory.
void showStatus()
{
    line();
    cout << "                 PLAYER STATUS\n";
    line();

    cout << "Character: Ruby Roundhouse\n";
    cout << "Health: " << health << "/100 HP\n";

    cout << "\nInventory:\n";

    // Check whether the inventory contains anything.
    if (inventory.empty())
    {
        cout << "Your inventory is empty.\n";
    }
    else
    {
        // Display every item in the inventory.
        for (int i = 0; i < inventory.size(); i++)
        {
            cout << "- " << inventory[i] << "\n";
        }
    }

    line();
}

// Add an item to the player's inventory.
void addItem(string item)
{
    inventory.push_back(item);

    cout << "\nYou collected: " << item << "!\n";
}

// Check whether the player owns a specific item.
bool hasItem(string item)
{
    // Search through the player's inventory.
    for (int i = 0; i < inventory.size(); i++)
    {
        if (inventory[i] == item)
        {
            return true;
        }
    }

    return false;
}

// Reduce the player's health.
void damagePlayer(int damage)
{
    health -= damage;

    // Prevent health from becoming negative.
    if (health < 0)
    {
        health = 0;
    }

    cout << "\nRuby lost " << damage << " health!\n";
    cout << "Current health: " << health << "/100\n";
}

// Restore the player's health.
void healPlayer(int amount)
{
    health += amount;

    // Prevent health from exceeding 100.
    if (health > 100)
    {
        health = 100;
    }

    cout << "\nRuby recovered " << amount << " health!\n";
    cout << "Current health: " << health << "/100\n";
}

// Check whether the player is still alive.
bool checkHealth()
{
    if (health <= 0)
    {
        line();
        cout << "             GAME OVER\n";
        cout << "The jungle has claimed another adventurer...\n";
        line();

        gameOver = true;
        return false;
    }

    return true;
}

// Introduce Ruby and the adventure.
void introduction()
{
    title();

    cout << "\nWelcome to JUMANJI!\n\n";

    cout << "You are Ruby Roundhouse.\n";
    cout << "A skilled fighter with incredible agility.\n\n";

    cout << "Your mission is to survive the Lost Jungle,\n";
    cout << "find the ancient jewel, and escape Jumanji.\n\n";

    cout << "But remember...\n";
    cout << "The jungle is unpredictable.\n";
    cout << "Every choice has a consequence.\n\n";

    cout << "SPECIAL ABILITY: EVASIVE MANEUVER\n";
    cout << "Ruby can use her agility to avoid dangerous attacks.\n";

    pauseGame();
}

// Allow the player to use Ruby's special ability.
void useAgility()
{
    cout << "\nRuby uses her incredible agility!\n";

    // Generate a random chance of successfully dodging.
    uniform_int_distribution<int> chance(1, 100);

    int result = chance(rng);

    // Give Ruby a 75 percent chance of dodging.
    if (result <= 75)
    {
        cout << "Amazing! Ruby dodged the attack!\n";
    }
    else
    {
        cout << "Ruby failed to dodge completely!\n";
        damagePlayer(15);
    }
}

// Explore the dangerous river.
void riverPath()
{
    line();
    cout << "                 THE CROCODILE RIVER\n";
    line();

    cout << "\nRuby approaches a river filled with crocodiles.\n";
    cout << "A small wooden bridge is nearby.\n\n";

    cout << "1. Attempt to cross the bridge.\n";
    cout << "2. Swim across the river.\n";
    cout << "3. Use agility to jump across the rocks.\n";

    int choice = getChoice(1, 3);

    if (choice == 1)
    {
        cout << "\nThe bridge begins to collapse!\n";
        damagePlayer(20);

        addItem("Rope");
    }
    else if (choice == 2)
    {
        cout << "\nA crocodile suddenly attacks!\n";
        useAgility();

        if (health > 0)
        {
            addItem("Crocodile Scale");
        }
    }
    else
    {
        cout << "\nRuby jumps across the rocks with ease!\n";
        cout << "Her agility saves the day.\n";

        addItem("Rope");
        healPlayer(10);
    }

    checkHealth();
}

// Explore the ancient ruins.
void ruinsPath()
{
    line();
    cout << "                  THE ANCIENT RUINS\n";
    line();

    cout << "\nRuby discovers an abandoned temple.\n";
    cout << "Inside, she finds a mysterious puzzle.\n\n";

    cout << "An inscription reads:\n";
    cout << "\"I have cities, but no houses.\n";
    cout << "I have forests, but no trees.\n";
    cout << "I have rivers, but no water.\n";
    cout << "What am I?\"\n\n";

    cout << "1. A painting.\n";
    cout << "2. A map.\n";
    cout << "3. A dream.\n";

    int choice = getChoice(1, 3);

    if (choice == 2)
    {
        cout << "\nCorrect! Ruby solved the puzzle!\n";
        cout << "A secret compartment opens.\n";

        addItem("Ancient Key");
        addItem("Jungle Map");

        hasKey = true;
        hasMap = true;
    }
    else
    {
        cout << "\nWrong answer!\n";
        cout << "A trap activates beneath Ruby's feet!\n";

        damagePlayer(20);

        if (health > 0)
        {
            cout << "\nRuby discovers a hidden key while escaping.\n";

            addItem("Ancient Key");
            hasKey = true;
        }
    }

    checkHealth();
}

// Explore the dangerous jungle canopy.
void canopyPath()
{
    line();
    cout << "                  THE JUNGLE CANOPY\n";
    line();

    cout << "\nRuby discovers a path high above the jungle floor.\n";
    cout << "The only way forward is across a series of vines.\n\n";

    cout << "1. Carefully climb across.\n";
    cout << "2. Swing quickly from vine to vine.\n";
    cout << "3. Find another way around.\n";

    int choice = getChoice(1, 3);

    if (choice == 1)
    {
        cout << "\nRuby carefully makes her way across.\n";

        addItem("Jungle Map");
        hasMap = true;
    }
    else if (choice == 2)
    {
        cout << "\nRuby swings through the canopy!\n";

        uniform_int_distribution<int> chance(1, 100);

        if (chance(rng) <= 80)
        {
            cout << "She lands safely on the other side!\n";

            addItem("Ancient Key");
            hasKey = true;
        }
        else
        {
            cout << "A vine snaps!\n";
            damagePlayer(25);
        }
    }
    else
    {
        cout << "\nRuby finds a hidden healing plant.\n";

        healPlayer(20);
        addItem("Healing Herb");
    }

    checkHealth();
}

// Give the player an opportunity to prepare.
void preparation()
{
    line();
    cout << "                 PREPARING FOR THE JOURNEY\n";
    line();

    cout << "\nRuby finds a small abandoned campsite.\n";
    cout << "She has a moment to catch her breath.\n\n";

    cout << "1. Rest and recover health.\n";
    cout << "2. Check inventory.\n";
    cout << "3. Continue exploring.\n";

    int choice = getChoice(1, 3);

    if (choice == 1)
    {
        healPlayer(25);
    }
    else if (choice == 2)
    {
        showStatus();
    }
    else
    {
        cout << "\nRuby decides to keep moving.\n";
    }
}

// Introduce the final guardian.
void guardianBattle()
{
    line();
    cout << "                THE JUNGLE GUARDIAN\n";
    line();

    cout << "\nA massive stone creature awakens!\n";
    cout << "It guards the ancient jewel.\n\n";

    cout << "The creature roars and charges toward Ruby!\n";

    // Give the player a chance to avoid the first attack.
    cout << "\n1. Dodge using agility.\n";
    cout << "2. Fight the guardian directly.\n";
    cout << "3. Search for a weakness.\n";

    int choice = getChoice(1, 3);

    if (choice == 1)
    {
        useAgility();
    }
    else if (choice == 2)
    {
        cout << "\nRuby attacks the guardian!\n";
        damagePlayer(20);
    }
    else
    {
        cout << "\nRuby notices a glowing crystal on its chest.\n";
        cout << "She discovers the guardian's weakness!\n";

        addItem("Guardian's Weakness");
    }

    if (!checkHealth())
    {
        return;
    }

    // Determine whether Ruby has discovered the guardian's weakness.
    bool weaknessFound = hasItem("Guardian's Weakness");

    cout << "\nThe guardian prepares one final attack!\n";

    if (weaknessFound)
    {
        cout << "Ruby targets the glowing crystal!\n";
        cout << "The guardian collapses!\n";

        guardianDefeated = true;
    }
    else
    {
        cout << "\nRuby must make one final decision!\n";

        cout << "1. Use agility to dodge and counterattack.\n";
        cout << "2. Use the rope to trap the guardian.\n";
        cout << "3. Run toward the ancient jewel.\n";

        int finalChoice = getChoice(1, 3);

        if (finalChoice == 1)
        {
            cout << "\nRuby dodges the attack and strikes!\n";
            guardianDefeated = true;
        }
        else if (finalChoice == 2 && hasItem("Rope"))
        {
            cout << "\nRuby uses the rope to trap the guardian!\n";
            guardianDefeated = true;
        }
        else if (finalChoice == 3 && hasKey)
        {
            cout << "\nRuby uses the key to unlock the jewel chamber!\n";
            guardianDefeated = true;
        }
        else
        {
            cout << "\nRuby gets caught by the guardian!\n";
            damagePlayer(40);
        }
    }

    checkHealth();

    if (guardianDefeated)
    {
        cout << "\nThe guardian has been defeated!\n";
        cout << "Ruby discovers the ancient jewel!\n";

        addItem("Jewel of Jumanji");
    }
}

// Determine the player's ending.
void finalEnding()
{
    if (!checkHealth())
    {
        return;
    }

    line();
    cout << "                 THE FINAL ESCAPE\n";
    line();

    cout << "\nRuby approaches the ancient exit portal.\n";
    cout << "The jewel begins to glow.\n\n";

    cout << "What will Ruby do?\n\n";

    cout << "1. Activate the portal using the jewel.\n";
    cout << "2. Search for another way out.\n";
    cout << "3. Stay in Jumanji and explore forever.\n";

    int choice = getChoice(1, 3);

    if (choice == 1 && guardianDefeated)
    {
        line();
        cout << "                 PERFECT ENDING!\n";
        line();

        cout << "\nRuby places the Jewel of Jumanji into the portal.\n";
        cout << "A blinding light fills the jungle!\n\n";

        cout << "The jungle disappears around her.\n";
        cout << "Ruby has escaped Jumanji!\n\n";

        cout << "CONGRATULATIONS!\n";
        cout << "You completed the adventure!\n";
    }
    else if (choice == 2 && hasMap)
    {
        line();
        cout << "                 SECRET ENDING!\n";
        line();

        cout << "\nRuby studies her jungle map.\n";
        cout << "She discovers a hidden passage behind the ruins.\n\n";

        cout << "Using her agility, she escapes through the passage!\n";
        cout << "Ruby survives the Lost Jungle!\n";
    }
    else if (choice == 3)
    {
        line();
        cout << "                 JUNGLE EXPLORER ENDING!\n";
        line();

        cout << "\nRuby decides to remain in Jumanji.\n";
        cout << "There are still countless mysteries to discover.\n";
        cout << "Her adventure is far from over...\n";
    }
    else
    {
        line();
        cout << "                 LOST IN JUMANJI!\n";
        line();

        cout << "\nRuby cannot activate the portal.\n";
        cout << "The jungle begins to close around her.\n";
        cout << "She must find another way to escape...\n";
    }

    gameOver = true;
}

// Main function where the game begins.
int main()
{
    // Display the introduction.
    introduction();

    // Allow Ruby to choose her first destination.
    line();
    cout << "                 CHOOSE YOUR PATH\n";
    line();

    cout << "\nWhere should Ruby explore first?\n\n";

    cout << "1. Crocodile River.\n";
    cout << "2. Ancient Ruins.\n";
    cout << "3. Jungle Canopy.\n";

    int pathChoice = getChoice(1, 3);

    // Send Ruby to the selected location.
    if (pathChoice == 1)
    {
        riverPath();
    }
    else if (pathChoice == 2)
    {
        ruinsPath();
    }
    else
    {
        canopyPath();
    }

    // Continue the adventure if Ruby survives.
    if (!gameOver)
    {
        preparation();
    }

    // Continue to the final encounter if Ruby survives.
    if (!gameOver)
    {
        guardianBattle();
    }

    // Show the final ending if Ruby survives.
    if (!gameOver)
    {
        finalEnding();
    }

    // Display the final player statistics.
    cout << "\n";
    showStatus();

    cout << "\nThank you for playing JUMANJI: THE LOST JUNGLE!\n";

    cout << "Created by: Ian Andalon\n";

    return 0;
}
