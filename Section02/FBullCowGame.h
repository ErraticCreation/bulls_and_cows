#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// All values initialized to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame 
{
public:
	FBullCowGame(); // constructor

	int32 GetHiddenWordLength() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	void Reset();
	FBullCowCount SubmitValidGuess(FString);
	FString PrintGameSummary();
	

// Ignore For Now.
private:
	// See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	// Helper Methods
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};