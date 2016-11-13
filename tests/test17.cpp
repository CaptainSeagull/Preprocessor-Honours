#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string> 

/*input a min value >> input a max value XXXXXXXXXXXXXXXXXXXXXXXX

Computer will do a random number generation between those values 
>> output the generated number

Computer will ask "Is this the number you are thinking of?"

>> IF the computer's number is higher than your number, input "too high" THEN the computer will reduce the max value to the guessed number.
(eg. if you input a value of between 1 and 10, and computer guesses 7, and 7 is too high, then the random number MAX value will change to 6. Then the computer will generate random number between 1 and 6!)

>> IF the computer's number is lower than your number, input "too low", THEN the computer will increase the min value to it's guessed number(between 1 and 10, if 5 is too low, the min and max values of the random number gen change to between 6 and 10)

These cycles will continue until the computer guesses the number you are thinking of.When the computer guesses your number, and you input "yes", the computer will say "I won! :)"

THe computer then asks "do you want to play again?" if yes, recycle program, if no, close program.*/

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

	return Ranges;

	std::cout << "\n Think of a number between the range you chose. The computer will try to guess it.";

}

// Random Number Generator
int RandomNumberGenerator(int Min, int Max)
{
	int result = Min + (rand() % (Max - Min) + 1);

	return result;

	std::cout << "\n Was " << result << "\n the number you thought of between your chosen ranges?";
}

// Process Random Number
Question ProcessRandomNum(int RandomNumber, std::string UserInput)
{

	std::cout << "x = too high \n";
	std::cout << "y = too low \n";
	std::cout << "z = correct \n";

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

		std::cout << "\n The Computer Guessed Correctly! \n \n";
	}
}

int main()
{
	srand(0);

	bool PlayAgain = true;

	while (PlayAgain == true)
	{


		//Range
		UserRange Ranges = GetRangeFromUser();

		// Random Number
		int ComputerGuess = RandomNumberGenerator(Ranges.Min, Ranges.Max);

		// Variable to store whether user's input is too high
		Question ComputerGuess = tooHigh;

		// While the Computer's Guess is too high, Do this:
		while (tooHigh)
		{
			int NewMax;
			ComputerGuess = NewMax;

			int RandomNumberGenerator(int Min, int NewMax);

			//Question ProcessRandomNum(int RandomNumber, std::string UserInput);

			Question IsComputerCorrect = ProcessRandomNum(RandomNumber, UserInput);
		}















		std::cout << "\n Would you like to play again?\n \n";

		char UserAnswer;

		std::cin >> UserAnswer;

		std::cout << "\n";

		if (UserAnswer == 'y')
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