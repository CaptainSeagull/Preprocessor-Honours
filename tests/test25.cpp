// Word Jumble
// Classic Word Jumble where the Player can ask for a Hint.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Swaps two characters around
void Swap(char & x, char & y)
{
    char temp = x;
    x = y;
    y = temp;

}

int main()
{
    // Storing the Word, Hint, and SIZE of enum
    enum fields
    {
        WORD, HINT, NUM_FIELDS
    };

    // Storing the number of words
    const int NUM_WORDS = 5;

    // An array called WORDS, which stores the number of words AND the number of fields (2). This is because both the WORD and the HINT
    // -make up a field. Therefore there are two fields.
    const string WORDS[NUM_WORDS][NUM_FIELDS] =
    {
        {"wall", "Do you feel like you're banging your head against something?"},
        {"glasses", "These might help you see the answer."},
        {"laboured", "Going slowly, is it?"},
        {"persistent", "Keep at it!"},
        {"jumble", "What this game is all about!"}
    };


    // Generating a random number between 0 and the value of NUM_WORDS, so between 0 and 5.
    srand(static_cast<unsigned int>(time(0)));

    //score
    int score = 0;
  
    char AnotherGame = 'y';
    while(AnotherGame == 'y')
    {
        int choice = (rand() % NUM_WORDS);

        bool usedHint = false;

        // The generated number, stored above as Choice, is used to select a word in the array corresponding to the number generated.
        // So "0" would be Wall, "1" would be Glasses, etc.
        string theWord = WORDS[choice][WORD];

        // The corresponding Hint to go along with the Word is initialised here.
        string theHint = WORDS[choice][HINT];


        string jumble = theWord;

        // Length of the word chosen
        int length = jumble.size();

        //
        for(int i = 0; i < length; ++i)
        {
            // Gets two random indexes between 0 and the length of the chosen word
            int index1 = (rand() % length);
            int index2 = (rand() % length);

            /*
            char temp = jumble[index1];
            jumble[index1] = jumble[index2];
            jumble[index2] = temp;*/

            // Calls Swap function to swap a letter of the chosen word with another letter of the chosen word to create a jumble.
            // Keeps going while "i" is less than the length of the word.

            Swap(jumble[index1], jumble[index2]);
            int j = 0;
        }

        // Welcoming Player and Game instructions
        cout << "\t\t\tWelcome to Word Jumble!\n\n";
        cout << "Unscramble the letters to make a word.\n";
        cout << "Enter 'hint' for a hint.\n";
        cout << "Enter 'quit' to quit the game.\n\n";
        cout << "The Jumble is: " << jumble;

        // Inputing and Storing Player's Guess
        string Guess;
        cout << "\n\nYour guess: ";
        cin >> Guess;

        // While the Player's guess does not equal the correct word, or "quit", run this loop.
        while((Guess != theWord) && (Guess != "quit"))
        {
            // If Player's guess is "hint", display hint.
            if(Guess == "hint")
            {
                usedHint = true;
                cout << theHint;
            }

            // Let the Player know their guess is incorrect
            else
            {
                cout << "Sorry, that's not it.";
            }

            // Prompt Player to input another guess
            cout << "\nYour Guess: ";
            cin >> Guess;
        }

        // If the Player guessed the word correctly, display the congratulation message and ask if the Player wants to play again.
        if(Guess == theWord)
        {
            
            // Score
                if(usedHint == true)
                    {
                        score += length / 2;   
                    }
                else
                {
                    score += length;
                }



            cout << "\nThat's it! You guessed it!\n";

            cout << "\nYour score is: " << score;
        }

        // Ask player if they want to play again, if "y", run the gameplay loop again, if "n", quit game.
        cout << "\nWould you like to play again?\n";
        cin >> AnotherGame;

        if(AnotherGame == 'n')
        {
            cout << "Thanks for playing! Goodbye.";
        }

    }

    return 0;

}