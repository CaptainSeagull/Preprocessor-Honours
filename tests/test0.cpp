// Pigeon Caretaker
// Simulates Caring for a Virtual Pet Pigeon

#include <iostream>
#include <string>

using namespace std;

class Pigeon
{
public:

    Pigeon();

    int m_Hunger;
    int m_Boredom;
    string m_Name;
    Pigeon(int hunger, int boredom);

    string GetName();
    string NameValue();
    int GetHunger();
    int GetBoredom();
    void Talk();
    void Eat(int food = 4);
    void Play(int fun = 4);
    void GetLevels();

private:

    int GetMood() const;
    void PassTime(int time = 1);
};

Pigeon::Pigeon()
{
    m_Hunger = 0;
    m_Boredom = 0;
}

Pigeon::Pigeon(int hunger, int boredom)
{
    m_Hunger = hunger;
    m_Boredom = boredom;
}

// functions

// Get Name
string Pigeon::GetName()
{
    cout << "\nYour Pigeon's name is: ";
    cin >> m_Name;
    cout << "\n";
    return m_Name;
}

string Pigeon::NameValue()
{
    return m_Name;
}

// Get Hunger
int Pigeon::GetHunger()
{
    return m_Hunger;
}

// Get Boredom
int Pigeon::GetBoredom()
{
    return m_Boredom;
}

// Get Mood
inline int Pigeon::GetMood() const
{
    return (m_Hunger + m_Boredom);
}

// Pass time
void Pigeon::PassTime(int time)
{
    m_Hunger += time;
    m_Boredom += time;
}

// Talk
void Pigeon::Talk()
{
    int mood = GetMood();

    cout << "\nI'm " << Pigeon::NameValue() << " the Pigeon and I feel ";

    if(mood > 15 && m_Hunger > m_Boredom) {
        cout << "angry and starving!! >:( *coos aggressively*\n\n";
    } else if(mood > 15 && m_Boredom > m_Hunger) {
        "angry and super bored!! >:( *coos aggressively*\n\n";
    } else if(mood > 15 && m_Boredom == m_Hunger) {
        "angry, super bored, and starving!! >:( *coos aggressively*\n\n";
    }

    else if(mood > 10 && m_Hunger > m_Boredom) {
        cout << "frustrated and hungry. :/ *coos grumpily*\n\n";
    } else if(mood > 10 && m_Boredom > m_Hunger) {
        cout << "frustrated and bored. :/ *coos grumpily*\n\n";
    } else if(mood > 10 && m_Boredom == m_Hunger) {
        cout << "frustrated, bored, and hungry. :/ *coos grumpily*\n\n";
    }

    else if(mood > 5 && m_Hunger > m_Boredom) {
        cout << "fine. :) I am a little hungry though... *coos contently*\n\n";
    } else if(mood > 5 && m_Boredom > m_Hunger) {
        cout << "fine. :) I am a little bored though... *coos contently*\n\n";
    } else if(mood > 5 && m_Boredom == m_Hunger) {
        cout << "fine. :) I am a bit bored and a little bit hungry though... *coos contently*\n\n";
    }

    else {
        cout << "very happy! :D *coos lovingly*\n\n";
    }

    PassTime();
}

// Eat
void Pigeon::Eat(int food)
{
    cout << "\n*gobbles food happily* Yummy yum! :D :D :D *happy coos*";
    m_Hunger -= food;

    if(m_Hunger < 0) {
        m_Hunger = 0;
    }

    PassTime();
}

void Pigeon::Play(int fun /*= 4*/)
{
    cout << "\nWheeee!! Fun fun!! :D :D :D *excited coos*";

    m_Boredom -= fun;
    if(m_Boredom < 0) {
        m_Boredom = 0;
    }

    PassTime();
}

void Pigeon::GetLevels()
{
    cout << "\nYour Pigeon's Hunger Level is: " << GetHunger() << "\n";
    cout << "\nYour Pigeon's Boredom Level is: " << GetBoredom() << "\n";
    PassTime();
}

int main()
{
    Pigeon One(4, 4);
    One.GetName();
    One.Talk();

    int choice;

    do {
        cout << "\n\nPigeon Caretaker\n\n";
        cout << "0 - Quit\n";
        cout << "1 - Listen to your Pigeon\n";
        cout << "2 - Feed your Pigeon\n";
        cout << "3 - Play with your Pigeon\n\n";

        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 0:
                cout << "\nGoodbye... :( *coos sadly*\n";
                break;
            case 1:
                One.Talk();
                break;
            case 2:
                One.Eat();
                break;
            case 3:
                One.Play();
                break;
            case 4:
                One.GetLevels();
                break;
            default:
                cout << "\nSorry but " << choice << " isn't a valid choice.\n";
        }
    } while(choice != 0);

    return 0;
}

