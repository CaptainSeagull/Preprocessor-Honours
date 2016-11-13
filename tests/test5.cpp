// Game Lobby
// Simulates a game lobby where players wait

#include <iostream>
#include <string>

using namespace std;

// PLAYER CLASS
class Player
{
public:
    Player(const string &name = "");

    // Gets Player Name
    string GetName() const;

    // Gets next player in line.
    Player *GetNext() const;

    // Sets next player in line.
    void SetNext(Player *next);

private:
    // holds name of player
    string m_Name;

    // pointer to next player in list
    Player *m_pNext;
};

// Constructor
// initialises m_Name to a string object based on what's passed to the constructor.
// it also sets m_pNext to 0, making it a null pointer.
Player::Player(const string &name):
m_Name(name),
m_pNext(0)

{ }

// Function to get Player's Name
string Player::GetName() const
{
    return m_Name;
}

// Function to GET next player in line
Player *Player::GetNext() const
{
    return m_pNext;
}

// Function to SET next player in line
void Player::SetNext(Player *next)
{
    m_pNext = next;
}

// LOBBY CLASS
class Lobby
{
    friend ostream &operator<<(ostream &os, const Lobby &aLobby);

public:
    Lobby();
    ~Lobby();
    void AddPlayer();
    void RemovePlayer();
    void Clear();

private:

    // a pointer that points to a player object, which represents the first person in line.
    // represents the player at the front of the queue.
    Player *m_pHead;
};

// Constructor 
// makes a m_pHead a null pointer
Lobby::Lobby():
    m_pHead(0)
{ }

// Destructor
// clears lobby
Lobby::~Lobby()
{
    Clear();
}

// Add Player member function
// initialises a player object and allocates memory to it from the heap
// adds the new player object to the end of the queue
void Lobby::AddPlayer()
{
    // create a new player node
    // gets a new player's name from the user and uses it to instantiate a new player on the heap.
    // then sets the player object's data member to the null pointer
    cout << "Please enter the name of the new player: ";
    string name;
    cin >> name;
    Player *pNewPlayer = new Player(name);

    // if list is empty, make head of list this new player
    if(m_pHead == 0)
    {
        m_pHead = pNewPlayer;
    }

    // Otherwise find the end of the list and add the player there
    else
    {
        Player *pIter = m_pHead;
        while(pIter->GetNext() != 0)
        {
            pIter = pIter->GetNext();
        }
        pIter->SetNext(pNewPlayer);
    }
}

// Remove Player Function
// removes first player in the queue, freeing allocated memory
void Lobby::RemovePlayer()
{
    if(m_pHead == 0)
    {
        cout << "The Game Lobby is empty. No one to remove!\n";
    }
    else
    {
        // creates a pointer pTemp, and points it to the first player object in the list
        // then m_pHead is set to the next thing in the list--either the next player object or 0.
        // finally, the function destroys the Player object pointed to by pTemp.
        Player *pTemp = m_pHead;
        m_pHead = m_pHead->GetNext();
        delete pTemp;
    }
}

// Clear Lobby function
void Lobby::Clear()
{
    while(m_pHead != 0)
    {
        // this function will keep removing the first player object in the list by calling RemovePlayer() until there are no more player objects left
        RemovePlayer();
    }
}

// Operator << Function
// send a lobby object to cout using << operator (because a Lobby object cannot be output normally)
ostream &operator<<(ostream &os, const Lobby &aLobby)
{
    // if the lobby is empty, the appropriate message is sent to the output stream.
    // otherwise the function cycles through all of the players in the list, sending their names to the output stream, using pIter to move through the list.
    Player *pIter = aLobby.m_pHead;
    os << "\nHere's who's in the Game Lobby:\n";
    if(pIter == 0)
    {
        os << "The Lobby is empty.\n";
    }
    else
    {
        while(pIter != 0)
        {
            os << pIter->GetName() << endl;
            pIter = pIter->GetNext();
        }
    }
    return os;
}


// MAIN
int main()
{
    Lobby myLobby;
    int choice;

    do
    {
        cout << myLobby;
        cout << "\nGAME LOBBY\n";
        cout << "0 - Exit the program.\n";
        cout << "1 - Add a Player to the Lobby.\n";
        cout << "2 - Remove a Player from the Lobby.\n";
        cout << "3 - Clear the Lobby\n";
        cout << endl << "Enter choice: ";
        cin >> choice;

        switch(choice)
        {
            case 0: cout << "Goodbye.\n";
                break;
            case 1: myLobby.AddPlayer();
                break;
            case 2: myLobby.RemovePlayer();
                break;
            case 3: myLobby.Clear();
                break;
            default: cout << "That was not a valid choice.\n";
        }
    } 
    while(choice != 0);

    return 0;
}


























