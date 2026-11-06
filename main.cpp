#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <random>
#include <algorithm>

using namespace std;

// ------------------------------------------------------------
// JUMANJI: THE LOST JUNGLE
// A console adventure starring Ruby Roundhouse.
// ------------------------------------------------------------

// Game-wide information.
int health = 100;
bool hasKey = false;
bool hasMap = false;
bool hasRope = false;
bool guardianDefeated = false;
bool gameOver = false;
vector<string> inventory;

// Random number generator used for surprise events.
random_device rd;
mt19937 generator(rd());

// Display a decorative divider.
void printLine()
{
    cout << "============================================================\n";
}

// Display the game title.
void showTitle()
{
    cout << R"(
      _   _ _   _ __  __    _    _   _ ___
     | | | | | | |  \/  |  / \  | \ | |_ _|
     | |_| | | | | |\/| | / _ \ |  \| || |
     |  _  | |_| | |  | |/ ___ \| |\  || |
     |_| |_|\___/|_|  |_/_/   \_\_| \_|___|

                 THE LOST JUNGLE
)";
    printLine();
    cout << "                 A RUBY ROUNDHOUSE ADVENTURE\n";
    printLine();
}

// Wait for the player to press Enter.
void pauseGame()
{
    cout << "\nPress Enter to continue...";
    string unused;
    getline(cin, unused);
}

// Read a number safely and reject invalid input.
int getChoice(int minimum, int maximum)
{
    string input;
    int choice;

    while (true)
    {
        cout << "\nEnter your choice (" << minimum << "-" << maximum << "): ";
        getline(cin, input);

        try
        {
            size_t used = 0;
            choice = stoi(input, &used);

            if (used == input.size() && choice >= minimum && choice <= maximum)
            {
                return choice;
            }
        }
        catch (...)
        {
            // The input was not a valid whole number.
        }

        cout << "That is not a valid choice. Try again.\n";
    }
}

// Show current health and collected items.
void showStatus()
{
    printLine();
    cout << "                         RUBY'S STATUS\n";
    printLine();
    cout << "Health: " << health << "/100 HP\n";
    cout << "Inventory:\n";

    if (inventory.empty())
    {
        cout << "  (Nothing collected yet)\n";
    }
    else
    {
        for (const string& item : inventory)
        {
            cout << "  - " << item << '\n';
        }
    }

    printLine();
}

// Add an item only once.
void addItem(const string& item)
{
    if (find(inventory.begin(), inventory.end(), item) == inventory.end())
    {
        inventory.push_back(item);
        cout << "\nItem collected: " << item << "!\n";
    }
}

// Check whether Ruby has an item.
bool hasItem(const string& item)
{
    return find(inventory.begin(), inventory.end(), item) != inventory.end();
}

// Restore health without exceeding the maximum.
void healPlayer(int amount)
{
    int oldHealth = health;
    health = min(100, health + amount);
    cout << "\nRuby recovered " << health - oldHealth << " HP. ";
    cout << "Health: " << health << "/100\n";
}

// Reduce health and check whether the adventure has ended.
void damagePlayer(int amount)
{
    health = max(0, health - amount);
    cout << "\nRuby lost " << amount << " HP. ";
    cout << "Health: " << health << "/100\n";

    if (health == 0)
    {
        printLine();
        cout << "RUBY HAS BEEN DEFEATED\n";
        cout << "The jungle has claimed another adventurer.\n";
        printLine();
        gameOver = true;
    }
}

// Ruby's special ability: a 75% chance to dodge danger.
bool useAgility()
{
    uniform_int_distribution<int> roll(1, 100);

    cout << "\nRuby uses her special ability: EVASIVE MANEUVER!\n";

    if (roll(generator) <= 75)
    {
        cout << "She flips out of danger without taking damage!\n";
        return true;
    }

    cout << "The move almost works, but Ruby is caught off guard!\n";
    damagePlayer(15);
    return false;
}

// Opening story.
void introduction()
{
    showTitle();

    cout << "\nYou are Ruby Roundhouse, an adventurer trapped inside Jumanji.\n";
    cout << "The jungle is alive, dangerous, and full of secrets.\n\n";
    cout << "Your mission:\n";
    cout << "  1. Explore the Lost Jungle.\n";
    cout << "  2. Find the ancient jewel.\n";
    cout << "  3. Defeat the guardian.\n";
    cout << "  4. Escape Jumanji!\n\n";

    cout << "SPECIAL ABILITY: EVASIVE MANEUVER\n";
    cout << "Ruby has a 75% chance to dodge certain attacks.\n";
    cout << "Watch your health and choose carefully. Every decision matters.\n";

    pauseGame();
}

// First location: the crocodile river.
void riverPath()
{
    printLine();
    cout << "                         CROCODILE RIVER\n";
    printLine();
    cout << "A wide river blocks Ruby's path. Crocodiles circle below.\n";
    cout << "An old bridge hangs over the water, and thick vines hang nearby.\n\n";

    cout << "1. Cross the old wooden bridge.\n";
    cout << "2. Swing across using the vines.\n";
    cout << "3. Try to swim across.\n";

    int choice = getChoice(1, 3);

    if (choice == 1)
    {
        cout << "\nThe bridge cracks beneath Ruby's feet!\n";
        damagePlayer(20);
        if (!gameOver)
        {
            cout << "Ruby grabs a loose rope before reaching the other side.\n";
            hasRope = true;
            addItem("Strong Rope");
        }
    }
    else if (choice == 2)
    {
        cout << "\nRuby swings from vine to vine with incredible agility.\n";
        hasRope = true;
        addItem("Strong Rope");
        healPlayer(10);
    }
    else
    {
        cout << "\nA crocodile rushes toward Ruby!\n";
        if (useAgility())
        {
            addItem("Crocodile Scale");
        }
    }
}

// Second location: the ancient temple and its riddle.
void ruinsPath()
{
    printLine();
    cout << "                          ANCIENT RUINS\n";
    printLine();
    cout << "Ruby discovers a forgotten temple covered in vines.\n";
    cout << "An inscription glows above a stone door:\n\n";
    cout << "\"I have cities, but no houses.\n";
    cout << "I have forests, but no trees.\n";
    cout << "I have rivers, but no water.\n";
    cout << "What am I?\"\n\n";

    cout << "1. A painting\n";
    cout << "2. A map\n";
    cout << "3. A dream\n";

    int choice = getChoice(1, 3);

    if (choice == 2)
    {
        cout << "\nCorrect! The stone door slides open.\n";
        cout << "Inside, Ruby finds an ancient key and a jungle map.\n";
        hasKey = true;
        hasMap = true;
        addItem("Ancient Key");
        addItem("Jungle Map");
    }
    else
    {
        cout << "\nWrong answer! A trap springs from the floor!\n";
        damagePlayer(20);

        if (!gameOver)
        {
            cout << "While escaping, Ruby spots a key beside the doorway.\n";
            hasKey = true;
            addItem("Ancient Key");
        }
    }
}

// Third location: the jungle canopy.
void canopyPath()
{
    printLine();
    cout << "                         JUNGLE CANOPY\n";
    printLine();
    cout << "Ruby climbs high above the jungle floor.\n";
    cout << "A trail of vines leads toward a distant stone platform.\n\n";

    cout << "1. Carefully climb across the branches.\n";
    cout << "2. Swing quickly from vine to vine.\n";
    cout << "3. Search the nearby plants for supplies.\n";

    int choice = getChoice(1, 3);

    if (choice == 1)
    {
        cout << "\nRuby moves carefully and finds a map carved into a tree.\n";
        hasMap = true;
        addItem("Jungle Map");
    }
    else if (choice == 2)
    {
        cout << "\nRuby swings across the canopy!\n";
        uniform_int_distribution<int> roll(1, 100);

        if (roll(generator) <= 80)
        {
            cout << "She lands safely and discovers an ancient key.\n";
            hasKey = true;
            addItem("Ancient Key");
        }
        else
        {
            cout << "A vine snaps! Ruby falls onto a lower branch.\n";
            damagePlayer(25);
        }
    }
    else
    {
        cout << "\nRuby finds a healing plant hidden beneath broad leaves.\n";
        addItem("Healing Herb");
        healPlayer(20);
    }
}

// A small campsite where the player can prepare.
void campsite()
{
    if (gameOver)
    {
        return;
    }

    printLine();
    cout << "                         ABANDONED CAMPSITE\n";
    printLine();
    cout << "Ruby finds an abandoned campsite and takes a moment to prepare.\n\n";

    cout << "1. Rest and recover 25 HP.\n";
    cout << "2. Check health and inventory.\n";
    cout << "3. Move on.\n";

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
        cout << "\nRuby tightens her backpack and continues.\n";
    }
}

// Final challenge: the stone guardian.
void guardianBattle()
{
    if (gameOver)
    {
        return;
    }

    printLine();
    cout << "                         THE STONE GUARDIAN\n";
    printLine();
    cout << "A giant stone creature rises from the ground!\n";
    cout << "A glowing crystal shines in the center of its chest.\n";
    cout << "The guardian blocks the path to the ancient jewel.\n\n";

    cout << "1. Dodge its first attack with Ruby's agility.\n";
    cout << "2. Charge forward and attack.\n";
    cout << "3. Study the creature to find a weakness.\n";

    int choice = getChoice(1, 3);

    if (choice == 1)
    {
        useAgility();
    }
    else if (choice == 2)
    {
        cout << "\nRuby lands a hit, but the guardian strikes back!\n";
        damagePlayer(20);
    }
    else
    {
        cout << "\nRuby notices the glowing crystal is the guardian's weak point!\n";
        guardianDefeated = true;
    }

    if (gameOver)
    {
        return;
    }

    if (!guardianDefeated)
    {
        cout << "\nThe guardian raises both arms for another attack!\n";
        cout << "Ruby needs one final move.\n\n";

        cout << "1. Dodge and counterattack.\n";
        cout << "2. Use the strong rope to trip the guardian.\n";
        cout << "3. Use the ancient key on the jewel chamber door.\n";

        int finalChoice = getChoice(1, 3);

        if (finalChoice == 1)
        {
            cout << "\nRuby dodges the attack and strikes the glowing crystal!\n";
            guardianDefeated = true;
        }
        else if (finalChoice == 2 && hasRope)
        {
            cout << "\nRuby loops the rope around the guardian's legs.\n";
            cout << "The creature crashes down, shattering its crystal!\n";
            guardianDefeated = true;
        }
        else if (finalChoice == 3 && hasKey)
        {
            cout << "\nThe ancient key opens a side passage around the guardian!\n";
            guardianDefeated = true;
        }
        else
        {
            cout << "\nRuby has no item for that plan. The guardian hits her!\n";
            damagePlayer(40);
        }
    }

    if (gameOver)
    {
        return;
    }

    if (guardianDefeated)
    {
        cout << "\nThe stone guardian collapses into a pile of rocks!\n";
        cout << "Behind it, Ruby discovers the glowing Jewel of Jumanji.\n";
        addItem("Jewel of Jumanji");
    }
}

// The ending depends on the player's choices and collected items.
void finalEnding()
{
    if (gameOver)
    {
        return;
    }

    printLine();
    cout << "                         THE FINAL PORTAL\n";
    printLine();
    cout << "Ruby reaches an ancient portal. The jungle begins to shake.\n";
    cout << "The jewel glows in her hands. This is her chance to escape.\n\n";

    cout << "1. Place the jewel into the portal.\n";
    cout << "2. Use the jungle map to search for a hidden exit.\n";
    cout << "3. Stay in Jumanji and explore the jungle.\n";

    int choice = getChoice(1, 3);

    if (choice == 1 && guardianDefeated && hasItem("Jewel of Jumanji"))
    {
        printLine();
        cout << "                         PERFECT ENDING!\n";
        printLine();
        cout << "Ruby places the jewel into the portal.\n";
        cout << "A brilliant light surrounds her as the jungle disappears.\n";
        cout << "She has escaped Jumanji!\n";
    }
    else if (choice == 2 && hasMap)
    {
        printLine();
        cout << "                          SECRET ENDING!\n";
        printLine();
        cout << "Ruby studies the map and discovers a hidden passage.\n";
        cout << "She uses her agility to race through it and escape!\n";
    }
    else if (choice == 3)
    {
        printLine();
        cout << "                     JUNGLE EXPLORER ENDING!\n";
        printLine();
        cout << "Ruby decides that her adventure is not over.\n";
        cout << "She turns toward the jungle and disappears into the trees.\n";
    }
    else
    {
        printLine();
        cout << "                       LOST IN JUMANJI\n";
        printLine();
        cout << "The portal remains closed. Ruby must keep searching for a way out.\n";
    }

    gameOver = true;
}

// Main function: controls the order of the adventure.
int main()
{
    introduction();

    printLine();
    cout << "                         CHOOSE YOUR PATH\n";
    printLine();
    cout << "Where will Ruby explore first?\n\n";
    cout << "1. Crocodile River\n";
    cout << "2. Ancient Ruins\n";
    cout << "3. Jungle Canopy\n";

    int path = getChoice(1, 3);

    if (path == 1)
    {
        riverPath();
    }
    else if (path == 2)
    {
        ruinsPath();
    }
    else
    {
        canopyPath();
    }

    if (!gameOver)
    {
        campsite();
    }

    if (!gameOver)
    {
        guardianBattle();
    }

    if (!gameOver)
    {
        finalEnding();
    }

    cout << "\n";
    showStatus();
    cout << "\nThanks for playing JUMANJI: THE LOST JUNGLE!\n";
    cout << "Created by: Ian Andalon\n";

    return 0;
}
