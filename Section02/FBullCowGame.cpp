#pragma once
#include "FBullCowGame.h"
#include <map>
#include <vector>
#include <ctime>
// To make syntax Unreal friendly
#define TMap std::map
#define TArray std::vector
using int32 = int;

FBullCowGame::FBullCowGame(){ Reset(); } // default constructor

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,9}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	FString HIDDEN_WORD = GetHiddenWord();
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

//receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();
	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{ // compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{ // if they match here	
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				// if they are in the same place
				if (MHWChar == GChar) 
				{ // increment bulls 
					BullCowCount.Bulls++; 
				}
				else 
				{ // must be a cow
					BullCowCount.Cows++; 
				}
			}
		}
	}
	
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else 
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

FString FBullCowGame::PrintGameSummary()
{
	FString end_game_message = "";
	if (bGameIsWon) 
	{
		 end_game_message = "**********\n	\n __   __ _______ __   __ \n|  | |  |       |  | |  |\n|  |_|  |   _   |  | |  |\n|       |  | |  |  |_|  |\n|_     _|  |_|  |       |\n  |   | |       |       |\n _|___|_|_______|_______|\n| | _ | |   |  |  | |  | \n| || || |   |   |_| |  | \n|       |   |       |  | \n|       |   |  _    |__| \n|   _   |   | | |   |__  \n|__| |__|___|_|  |__|__| \n \n**********\n";
	}
	else 
	{
		end_game_message = "**********\n	Better luck next time. \n**********\n";
	}
	return end_game_message;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	
	TMap<char, bool> LetterSeen;// setup our map
	
	// loop through all letters of the word
	for (auto Letter : Word) 
	{
		Letter = tolower(Letter); // handle mixed case
		// if the letter is in the map
		if (LetterSeen[Letter]) 
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true; //add the letter to map
		}
	}	
	return true; // for example in cases where /0 is entered
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // If guess isn't isogram 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) // If guess isn't lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length()) // If guess length is off
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

FString FBullCowGame::GetHiddenWord() const
{
	// Create an array containing possible isograms for guessing (single words with no repeating characters)
	TArray<FString> List{ "air","arm","gas","mag","rag","orc","rob","sob","age","ark", "damp", "sour", "bags", "ears", "foam", "firm", "grim", "grin", "marsh", "girls", "marks", "males", "fails", "grams", "major", "savior", "ransom", "morals", "disarm", "radios", "armies", "isogram", "mirages", "margins", "roaming" };
	// return a random word from the list
	return List[(rand() % List.size())];
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	if (Word.length() <= 0) 
	{
		return false;
	}
	else 
	{
		for (auto Letter : Word)
		{
			// If not a lower case letter
			if (!islower(Letter))
			{
				return false;
			}
		}
	}
	return true;
}
