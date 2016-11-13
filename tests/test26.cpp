#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string> 

enum Question
{
	tooLow,
	tooHigh,
	correct,
};

struct UserRange
{
	int Min;
	int Max;
};

UserRange GetRangeFromUser()
{
	UserRange Ranges;

	std::cout << "Please choose a range of numbers.\n Start with the lowest value in the range: \n \n";
	int MinUserRange;
	std::cin >> MinUserRange;
	Ranges.Min = MinUserRange;

	std::cout << "\n Now choose the highest value in the range: \n \n";
	int MaxUserRange;
	std::cin >> MaxUserRange;
	Ranges.Max = MaxUserRange;

	std::cout << "\n Think of a number between the range you chose. The computer will try to guess it.";
	return Ranges;


}

// Random Number Generator
int RandomNumberGenerator(int Min, int Max)
{
	int result = Min + (rand() % (Max - Min) + 1);

	std::cout << "\n Was " << result << "\n the number you thought of between your chosen ranges?";
	return result;

}

// Process Random Number
Question ProcessRandomNum(int RandomNumber)
{
	std::string UserInput;

	std::cout << "\nx = too high \n";
	std::cout << "y = too low \n";
	std::cout << "z = correct \n \n";

	//If Computer's Guessed Number is HIGHER than the User's Chosen Number... 

	std::cin >> UserInput;

	if (UserInput.compare("x") == 0)
	{
		return tooHigh;
	}

	//If Computer's Guessed Number is LOWER than the User's Chosen Number... 
	else if (UserInput.compare("y") == 0)
	{
		return tooLow;
	}

	//If Computer's Guessed Number is EQUAL to the User's Chosen Number... 
	else if (UserInput.compare("z") == 0)
	{
		return correct;

	}
}

int main()
{
    srand(0);

    bool PlayAgain = true;

    while(PlayAgain == true)
    {
        Question question = tooHigh;

        //Range
        UserRange Ranges = GetRangeFromUser();

        while(question != correct)
        {

            // Random Number
            int ComputerGuess = RandomNumberGenerator(Ranges.Min, Ranges.Max);

            // See if Computer Guess is too high, low or correct
            question = ProcessRandomNum(ComputerGuess);

            switch(question)
            {
                case tooHigh:
                    Ranges.Max = ComputerGuess - 1;
                    break;

                case tooLow:
                    Ranges.Min = ComputerGuess + 1;
                    break;

                case correct:
                    std::cout << "\n The Computer Guessed Correctly! \n \n";
                    break;
            }
        }

        std::cout << "\n Would you like to play again?\n \n";

        char UserAnswer;

        std::cin >> UserAnswer;

        std::cout << "\n";

        if(UserAnswer == 'y')
        {
            PlayAgain = true;
            //call function to play program again;
        }

        else
        {
            PlayAgain = false;
            //call function to close program;
        }
    }

    return 0;
}