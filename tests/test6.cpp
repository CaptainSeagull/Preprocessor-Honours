// Hangman
// The classic game of Hangman

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>

using namespace std;

int main()
{
    // Setup

    // Setting maximum number of incorrect guesses allowed
    const int MAX_WRONG = 8;

    // Collection of possible words to guess stored inside a vector called "words"
    vector<string> words;
    words.push_back("GUESS");
    words.push_back("HANGMAN");
    words.push_back("DIFFICULT");

    // Choosing a random element (word) stored in the vector for the player to guess
    srand(static_cast<unsigned int>(time(0)));
    random_shuffle(words.begin(), words.end());

    // Words to guess
    const string THE_WORD = words[0];

    // Number of incorrect guesses so far
    int wrong = 0;

    // Word guessed so far
    string soFar(THE_WORD.size(), '-');

    // Letters already guessed
    string used = "";

    cout << "Welcome to Hangman. Good Luck!\n";

    // Main loop

    // Keep looping while the max number of allowed guesses has not been achieved and while the player hasn't guessed the word
    while((wrong < MAX_WRONG) && (soFar != THE_WORD))
    {
        // Output remaining number of guesses
        cout << "\n\nYou have " << (MAX_WRONG - wrong);
        cout << " incorrect guesses left.\n";

        // Output user's guesses so far, and how much of the word they have guessed.
        cout << "You've used the following letters:\n" << used << endl;
        cout << "\nSo far, the word is:\n" << soFar << endl;


        // Get a guess from player, convert the guess to uppercase to match with the uppercase words in the vector
        char guess;
        cout << "\n\nEnter your guess ";
        cin >> guess;

        // Make uppercase since secret word in uppercase
        guess = toupper(guess);

        // Loop while the user inputs a guess that has already been used
        while(used.find(guess) != string::npos)
        {
            cout << "\nYou've already guessed " << guess << endl;
            cout << "Enter your guess: ";
            cin >> guess;
            guess = toupper(guess);
        }

        used += guess;

        // If the user guesses a letter in the word correctly, output the updated word
        if(THE_WORD.find(guess) != string::npos)
        {
            cout << "That's right! " << guess << " is in the word.\n";

            // Update soFar to include newly guessed letter
            for(int i = 0; i < THE_WORD.length(); ++i)
            {
                if(THE_WORD[i] == guess)
                {
                    soFar[i] = guess;
                }
            }
        }

        // Otherwise add to the amount of wrong guesses
        else
        {
            cout << "Sorry, " << guess << " isn't in the word.\n";
            ++wrong;
        }

    }
    // Shut down
    // If the user has used all of their allowed guesses...
    if(wrong == MAX_WRONG)
    {
        cout << "\nYou've been hanged!";
    }

    // Otherwise congradulate user
    else
    {
        cout << "\nYou guessed it!";
    }

    // Output the word the user was trying to guess
    cout << "\nThe word was " << THE_WORD << endl;

    return 0;

}