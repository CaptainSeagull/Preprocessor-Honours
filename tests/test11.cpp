// Mad Lib
// Creates a story based on user input

#include <iostream>
#include <string>

using namespace std;

string askText(string prompt)
{
    string text;
    cout << prompt;
    cin >> text;
    return text;
}

int askNumber(string prompt)
{
    int num;
    cout << prompt;
    cin >> num;
    return num;
}

void tellStory(string *pName, string *pNoun, int *pNumber, string *pBodyPart, string *pVerb)
{
    cout << "\nHere's your story:\n";
    cout << "The famous explorer ";
    cout << *pName;
    cout << " had nearly given up a life-long quest to find\n";
    cout << "The Lost City of ";
    cout << *pNoun;
    cout << " when one day, the ";
    cout << *pNoun;
    cout << " found the explorer.\n";
    cout << "Surrounded by ";
    cout << *pNumber;
    cout << " " << *pNoun;
    cout << ", a tear came down to ";
    cout << *pName << "'s ";
    cout << *pBodyPart << ".\n";
    cout << "After all this time, the quest was finally over. ";
    cout << "And then, the ";
    cout << *pNoun << "\n";
    cout << "promptly devoured ";
    cout << *pName << ". ";
    cout << "The moral of the story? Be careful what you ";
    cout << *pVerb;
    cout << " for.";
}

int main()
{
    cout << "Welcome to Mad Lib.\n\n";
    cout << "Answer the following questions to help create a new story.\n";

    string name = askText("Please enter a name: ");
    string noun = askText("Please enter a plural noun: ");
    int number = askNumber("Please enter a number: ");
    string bodyPart = askText("Please enter a body part: ");
    string verb = askText("Please enter a verb: ");

    string *pName = &name;
    string *pNoun = &noun;
    int *pNumber = &number;
    string *pBodyPart = &bodyPart;
    string *pVerb = &verb;

    tellStory(pName, pNoun, pNumber, pBodyPart, pVerb);

    return 0;
}