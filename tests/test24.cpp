// Hero's Inventory 2.0
// Demonstrates vectors

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//For loop for checking the size of the vector and outputting the vector elements
void PrintVector(vector<string> inventory)
{
    for(unsigned i = 0, count = inventory.size(); i < count; ++i)
    {
        cout << inventory[i] << endl;
    }
}


int main()
{
    // initialising vector and adding elements to vector
    vector<string> inventory;
    inventory.push_back("sword");
    inventory.push_back("armour");
    inventory.push_back("shield");

    // Outputting size of the vector
    cout << "You have " << inventory.size() << " items.\n";

    // Outputting elements of Vector
    cout << "\nYour items:\n";
    PrintVector(inventory);

    // Assigning a new item to the first element in the vector
    cout << "\nYou trade your sword for a battle axe.";
    inventory[0] = "battle axe";

    // Outputting the changes to the vector elements
    cout << "\nYour items:\n";
    PrintVector(inventory);

    // Getting the number of characters of the first element in the vector and outputting the result
    cout << "\nThe item name '" << inventory[0] << "' has ";
    cout << inventory[0].size() << " characters in it.\n";

    // Getting rid of the last element in the vector
    cout << "\nYour shield is destroyed in a fierce battle.";
    inventory.pop_back();

    // Outputting the changes to the vector elements again
    cout << "\nYour items: \n";
    PrintVector(inventory);

    // Clearing the vector of all it's elements
    cout << "\nYou were robbed of all of your possessions by a thief.";
    inventory.clear();
    
    // For loop checking if vector has no elements
    if(inventory.empty())
    {
        cout << "\nYou have nothing.\n";
    }
    else
    {
        cout << "\nYou have at least one item.\n";
    }

    return 0;
}