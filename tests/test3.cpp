// Games List

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void printVector(vector<string> gamesList)
{
    for(auto &iter : gamesList)
    {
        cout << "\n";
        cout << iter;
    }
}

#include <stdio.h>

void addItem(vector<string> &gamesList)
{
    cout << "\n";
    char buffer[1024] = {};
    gets_s(buffer, 1024);
    string addedGame = buffer;
    gamesList.push_back(addedGame);
}

void deleteItem(vector<string> &gamesList)
{
    cout << "\n";
    char buffer[1024] = {};
    gets_s(buffer, 1024);
    string deletedGame = buffer;

    auto iter = find(gamesList.begin(), gamesList.end(), deletedGame);
    if (iter != gamesList.end())
    { 
        gamesList.erase(iter);
    }
}

int main()
{
    string userInput;
    vector<string> gamesList;

    cout << "Welcome to the Favourite Games List maker!\n";
    cout << "\nInsert 'add' if you wish to add a game to your list.\n";
    cout << "\nInsert 'delete' if you wish to delete a game from your list.\n";
    cout << "\nInsert 'quit' when you have completed your list and no longer wish to add or delete items.\n";

    char buffer[1024] = {};

    while(userInput != "quit")
    {
        cout << "\n\nWould you like to add or delete a title from your list?\n\n";

        gets_s(buffer, 1024);
        userInput = buffer;

        if(userInput.compare("add") == 0)
        {
            cout << "\nPlease type the title of the game you wish to add to the list.\n";
            addItem(gamesList);
            cout << "\nYour Favourite Game List So Far:\n";
            printVector(gamesList);
        }

        else if(userInput.compare("delete") == 0)
        {
            cout << "\nPlease type the title of the game you wish to remove from the list.\n";
            deleteItem(gamesList);
            cout << "\nYour Favourite Game List So Far:\n";
            printVector(gamesList);
        }

    }
        cout << "\nThank you for using the Favourite Games List Maker.\n";
        cout << "\nYour final List of Favourite Games is:" << endl;
        printVector(gamesList);
        cout << "\n\nGoodbye!";

        return 0;
}