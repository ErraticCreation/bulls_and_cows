#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame(){ Reset(); }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "rant";
	
	MyMaxTries = MAX_TRIES;
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
		 end_game_message = "**********\n	Congratulations - You Won!! \n**********\n";
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
		return EGuessStatus::Not_Lowercase; //TODO write function
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
