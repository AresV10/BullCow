#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void IntroPrint();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

//Program start
int main()
{
	IntroPrint();
	
	bool bPlayAgain = false;
	do
	{
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}

void IntroPrint()
{

	// intro to game
	//int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "Welcome to Bulls and Cows" << std::endl << "Can you guess a " << BCGame.GetHiddenWordLength();
	std::cout<< " letter isogram i'm thinking of \nAn Isogram is a word with no repeating letters\nAfter every guess, the number of cow and bulls will be displayed\nA bull is when you guess the right letter in the right place whereas \nA cow is when you guess a right letter in the wrong place\n\n";
		
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//std::cout << MaxTries << std::endl;

	//loop for number of tries
	
	while (!BCGame.IsGameWon()&& (BCGame.GetCurrentTry() <= MaxTries))
	{
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = "<<BullCowCount.Cows<<std::endl<<std::endl;
	}

	PrintGameSummary();

	return;
}

FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::INVALID_STATUS;
	FText Guess = "";
	do {
		
		int32 MyTry = BCGame.GetCurrentTry();
		// take input
		std::cout << "Try " << MyTry <<" out of "<<BCGame.GetMaxTries()<< ". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
			{
			case EGuessStatus::WRONG_LENGTH:
				std::cout << "Enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
				break;

			case EGuessStatus::NOT_ISOGRAM:
				std::cout << "Enter a proper Isogram\n\n";
				break;

			case EGuessStatus::NOT_LOWERCASE:
				std::cout << "Enter word in lower case.\n\n";
				break;

			default:
				break;
			}
		} while (Status != EGuessStatus::OK);

		return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play with the same word again? (y/n) ";
	FText Response = "";
	getline(std::cin, Response);
	return ((Response[0] == 'y')|| (Response[0] == 'Y'));
	
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done. You won !\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}

