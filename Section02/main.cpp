//============================================================================
// Name        : BullCowGame
// Entry Point : main.cpp
// Author      : Tarah Nixon
// Version     :
// Copyright   : Tarah Nixon © 2016. All Rights Reserved
// Description : BullCowGame in C++
//============================================================================

//   ____  _     _    _    ____    
//  /  __\/ \ /\/ \  / \  / ___\   
//  | | //| | ||| |  | |  |    \   
//  | |_\\| \_/|| |_/\ |_/\___ |   
//  \____/\____/\____|____|____/__ 
//  /.\    /   _\/  _ \/ \  // ___\
//  \ _\_  |  /  | / \|| |  ||    \
//  /|/ /  |  \__| \_/|| |/\|\___ |
//  \__/\  \____/\____/\_/  \\____/
//                                 

/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC Pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

FBullCowGame BCGame; // Instantiate the game

/* Prototypes
___________________________________________________________________
*/
void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();

// Entry point for out application.
int main()
{
	bool bPlayAgain = false;

	do 
	{
		BCGame.Reset();
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while ((bPlayAgain == true));
	
	return 0;
}

// Introduce the game
void PrintIntro() 
{
	// ASCII Art game title
	FText GameTitle = " _______ __   __ ___     ___     _______   \n|  _    |  | |  |   |   |   |   |       |  \n| |_|   |  | |  |   |   |   |   |  _____|  \n|       |  |_|  |   |   |   |   | |_____   \n|  _   ||       |   |___|   |___|_____  |  \n| |_|   |       |       |       |_____| |  \n|_______|_______|_______|_______|_______|  \n&  _______ _______ _     _ _______         \n  |       |       | | _ | |       |        \n  |       |   _   | || || |  _____|        \n  |       |  | |  |       | |_____         \n  |      _|  |_|  |       |_____  |        \n  |     |_|       |   _   |_____| |        \n  |_______|_______|__| |__|_______|        \n";

	std::cout << GameTitle;
	std::cout << "\n" << std::endl;
	std::cout << "Welcome to Bulls and Cows, a fun word game!\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of within "<< BCGame.GetMaxTries() << " tries?";
	std::cout << std::endl;
	return;
}

void PlayGame() 
{
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << std::endl; 

	// Loop for the remaining number of turns and the game is NOT won
	do
	{
		FText Guess = GetValidGuess(); // loop checking valid guesses	
		// Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	} while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries);

	std::cout << std::endl;
	std::cout << BCGame.PrintGameSummary() << std::endl;
	
	return;
}


// Loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid;
	do
	{
		// Get guess from the player
		std::cout << "Try (" << BCGame.GetCurrentTry();
		std::cout << "/" << BCGame.GetMaxTries() << "). Enter your guess: ";
		std::getline(std::cin, Guess);

		// Check the guess validity
		Status = BCGame.CheckGuessValidity(Guess);
		
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your word in all lower case letters. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		default:
			// Assume a valid guess was given
			break;
		}
	} while (Status != EGuessStatus::OK); // Keep looping until no errors are found
	return Guess;
}

bool AskToPlayAgain() 
{
	std::cout << "Would you like to play again with a different word? (y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y' || Response[0] == 'Y');
}