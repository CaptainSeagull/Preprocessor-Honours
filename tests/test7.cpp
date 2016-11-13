// Heap Data Member
// Demonstrates an object with a dynamically allocated data member

#include <iostream>
#include <string>

using namespace std;

// critter class
class Critter
{

// public member functions

public:
    // Class constructor prototype
    Critter(const string& name = "", int age = 0);

    // destructor prototype
    ~Critter();

    //copy constructor prototype
    Critter(const Critter &c);

    // overloaded assignment op
    Critter &Critter::operator=(const Critter &c);

    // "Greet" member function prototype
    void Greet() const;

// private member functions

private:

    // pointer to the data member that stores the critter's name
    string *m_pName;

    // data member that stores age
    int m_Age;
};

// Class constructor
Critter::Critter(const string &name, int age)
{
    cout << "Constructor called\n";

    // Allocates memory for a string object, assigns "name" to it, and points m_pName to that chunk of assigned memory on the heap
    m_pName = new string(name);

    // assigning m_Age to age
    m_Age = age;
}

// destructor definition
Critter::~Critter()
{
    cout << "Destructor called\n";

    // deletes the string object on the heap that is pointed to with m_pName
    delete m_pName;
}

// copy constructor definition
// makes a DEEP copy
// NOTE: copy constructors with a parameter the same data type as the class MUST be passed by reference! (No idea why though...)
Critter::Critter(const Critter &c)
{
    cout << "Copy Constructor called\n";

    // creates a copy of the data stored at m_pName, allocates new memory for the copy, and creates a pointer to that new memory
    // -(so if the data stored at the original location of m_pName is changed, it is not altered in the copy, as the copy is
    // -stored at a new memory address)
    m_pName = new string(*(c.m_pName));

    // copies the value of m_Age to the copy m_Age's data member.
    m_Age = c.m_Age;
}

Critter &Critter::operator=(const Critter &c) // overload assignment op def
{
    cout << "Overloaded Assignment Operator called\n";

    // "this" is a pointer that points to the object being used to call the function (whatever is on the left side of the "=")
    // if "this" does not equal the copy's memory address...
    if(this != &c)
    {
        // free memory storing m_pName
        delete m_pName;

        // create a copy of the data stored at m_pName, allocate new memory for the copy, and create a pointer to this new memory
        m_pName = new string(*(c.m_pName));

        // copy the value of m_Age to the copy m_Age's data member
        m_Age = c.m_Age;
    }
    // return the data stored at the memory address, pointed to by "this".
    return *this;
}

void Critter::Greet() const
{
    // outputs a greeting from the critter
    // outputs the name stored at the memory location pointed to by m_pName
    cout << "I'm " << *m_pName << " and I'm " << m_Age << " years old.\n";

    // outputs the memory address of m_pName

    // NOTE: When a variable is declared with a * before it, it means that variable is a pointer.
    // NOTE: Any other time a * is before a variable that is already initialised in a program, it means "dereference this pointer"
    // -or, "get what's at the memory address of this pointer"

    // NOTE: A &pointer means "get the memory address of this pointer"
    // NOTE: When declaring a variable the "&" before it means that variable is a reference
    cout << "&m_pName: " << &m_pName << endl;
}

// Testing destructor
void testDestructor()
{
    // Creates a critter object "toDestroy"
    Critter toDestroy("Rover", 3);

    // Calls greet member function
    toDestroy.Greet;
}

// Testing copy constructor
void testCopyConstructor(Critter aCopy)
{
    // Calls the greet member function
    // aCopy is the copy of whatever object the copy constructor copied
    aCopy.Greet();
}

// testing assignment operator
void testAssignmentOp()
{
    // Creating two new critter objects
    Critter crit1("crit1", 7);
    Critter crit2("crit2", 9);

    // Setting crit1's values to be a copy of crit2's values
    crit1 = crit2;

    // Calling the greet member function for both objects
    crit1.Greet();
    crit2.Greet();
    cout << endl;

    // Creating a third critter object
    Critter crit3("crit", 11);

    // Assigning crit3's values to itself
    crit3 = crit3;

    // Calling greet member function
    crit3.Greet();
}


int main()
{
    // calling test destructor
    testDestructor();
    cout << endl;

    // creating a new critter object "crit"
    Critter crit("Poochie, 5");

    // calling greet member function
    crit.Greet();

    // calling copyconstructor test function and passing crit in as a parameter
    testCopyConstructor(crit);

    // calling the greet member function again
    crit.Greet();
    cout << endl;

    // calling assignment operator function
    testAssignmentOp();

    return 0;
}


















