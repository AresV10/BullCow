#pragma once

# include "FBullCowGame.h"
# include <map>
# define TMap std::map

using int32 = int;


FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	
	const FString HIDDEN_WORD = "pla";
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	MyCurrentTry = 1;
	return;
}

int FBullCowGame::GetMaxTries() const
{
	TMap <int32, int32> WordLengthToMaxTries{{3,5},{4,6},{5,8},{6,10},{7,15}};
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int FBullCowGame::GetCurrentTry() 
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{

	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{

	if (!IsIsogram(Guess))	// checking for isogram
	{
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (!IsLowerCase(Guess))//not lowercase //true for lower false for upper
	{
		return EGuessStatus::NOT_LOWERCASE;
	}
	else if (Guess.length()!=GetHiddenWordLength())
	{
		return EGuessStatus::WRONG_LENGTH;
	}
	else
	{
		return EGuessStatus::OK;
	}
		
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();
	for (int32 i = 0; i < WordLength; i++)
	{

		if (Guess[i] == MyHiddenWord[i])
		{
			BullCowCount.Bulls++;
		}

		else 
		{
			for (int32 j = 0; j < WordLength; j++)
			{

				if (Guess[i] == MyHiddenWord[j])
				{
					BullCowCount.Cows++;
				}

			}
		}
	}

	if (BullCowCount.Bulls == MyHiddenWord.length())
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for(auto Letter : Word)
	{
		Letter = tolower(Letter);

		if (LetterSeen[Letter])
		{
	return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (islower(Letter))
		{
			return true;//Outputs true if it is lower case
		}
		else
		{
			return false;//Outputs false if its upper and lowercase
		}
	}
	return false;
}
