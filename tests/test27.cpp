// High Scores
// Demonstrates algorithms

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// Initialising a constant vector called "iter"
vector<int>::const_iterator iter;

// Function with a for loop that goes through all current elements in the Vector called Scores, and outputs them.
void PrintHighScores(vector<int> scores)
{
    //for(iter = scores.begin(); iter != scores.end(); ++iter)
    for (auto &iter : scores)
    {
        cout << iter << endl;
    }
}

int main()
{
    cout << "Creating a list of Scores.";

    // Initialising a vector called Scores and setting some elements to it
    vector<int> scores;
    scores.push_back(1500);
    scores.push_back(3500);
    scores.push_back(7500);

    // Calling the function to print the vector's elements
    cout << "\nHigh Scores:\n";
    PrintHighScores(scores);

    // Getting the user to input a score, and checking the user's input against all elements in the vector, in an attempt to find a match
    cout << "\nFinding a score.";
    int score;
    cout << "\nEnter a Score to find: ";
    cin >> score;
    iter = find(scores.begin(), scores.end(), score);
    
    // If a match is found...
    if(iter != scores.end())
    {
        cout << "\nScore found.\n";
    }

    // If a match is not found...
    else
    {
        cout << "\nScore not found.\n";
    }

    // Shuffling the order of all of the elements inside the "Scores" vector randomly and outputting them
    cout << "\nRandomising Scores.";
    srand(static_cast<unsigned int>(time(0)));
    random_shuffle(scores.begin(), scores.end());
    cout << "\nHigh Scores:\n";
    PrintHighScores(scores);

    // Sorting Scores in  Ascending order
    cout << "\nSorting Scores.";
    sort(scores.begin(), scores.end());
    cout << "\nHigh Scores:\n";
    PrintHighScores(scores);

    return 0;
}