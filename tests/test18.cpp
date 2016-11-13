// Simple Pigeon Caretaker Game
// Demonstrates creating a new type

#include <iostream>

using namespace std;

class Pigeon // class definition -- defines a new type, Pigeon.
{
public:
    int m_Hunger; // data member
    void Pigeon::Greet() // member function definition
    {
        cout << "Hi. I'm a Pigeon. My hunger level is " << m_Hunger << ".\n";
    }
};

int main()
{
    Pigeon Rolly;
    Pigeon Tumbles;

    Rolly.m_Hunger = 9;
    cout << "Rolly's hunger level is " << Rolly.m_Hunger << ".\n";

    Tumbles.m_Hunger = 3;
    cout << "Tumbles' hunger level is " << Tumbles.m_Hunger << ".\n\n";

    Rolly.Greet();
    Tumbles.Greet();

    return 0;
}