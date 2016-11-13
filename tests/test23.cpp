// Hero's Inventory 3.0
// Demonstrates iterators

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// initialising a vector called "inventory"
vector<string> inventory;

// initialising an iterator called "myIterator"
vector<string>::iterator myIterator;

// initialising a constant iterator called "iter
vector<string>::const_iterator iter;

// Function which has a for loop that checks what is in the vector and outputting it
// "auto" means the compiler works out the data type automatically
// "&iter" is a reference to the current element in the vectoe
// It will go through every element that currently exists in the vector and output all of them
void PrintVector(vector<string> inventory)
{
    //for(iter = inventory.begin(); iter != inventory.end(); ++iter)
    for(auto &iter : inventory)
    {
        cout << iter << endl;
    }
}

int main()
{
    // Adding elements to the vector
    inventory.push_back("sword");
    inventory.push_back("armour");
    inventory.push_back("shield");

    // Outputting elements of vector
    cout << "Your items:\n";
    PrintVector(inventory);

    // Inserts a new element replacing the element currently at the beginnng of the vector
    // Stores a pointer to the new element
    cout << "\nYou trade your sword for a battle axe.";
    myIterator = inventory.begin();
    *myIterator = "battle axe";

    // Outputting Updated elements
    cout << "\nYour Items:\n";
    PrintVector(inventory);

    // Pointing to the location of "*myIterator" and getting the size of the element at that location
    cout << "\nThe item name '" << *myIterator << "' has ";
    cout << (*myIterator).size() << " characters in it.\n";

    // Same as above, but a different way of writing the code for getting the size
    cout << "\nThe item name '" << *myIterator << "' has ";
    cout << myIterator->size() << " characters in it.\n";

    // Inserting an element at the beginning of the vector
    cout << "\nYou recover a crossbow from a slain enemy.";
    inventory.insert(inventory.begin(), "crossbow");

    // Outputting updated vector elements
    cout << "\nYour items:\n";
    PrintVector(inventory);

    // Erasing the 3rd element in the vector
    // 0 is the beginning of the vector, so 0 + 2 = 2, therefore the element stored at 2, will be erased (also the third element).
    cout << "\nYour armour is destroyed in a fierce battle.";
    inventory.erase((inventory.begin() + 2));

    // Outputting updated elements in the vector
    cout << "\nYour items:\n";
    PrintVector(inventory);

    return 0;
}









