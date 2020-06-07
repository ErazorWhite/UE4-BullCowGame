// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame(); // Setting Up Game

    PrintLine(TEXT("HiddenWord: %s."), *HiddenWord); // Debug Line

    // Welcoming the Player
    PrintLine(TEXT("Welcome to Bull Cows."));
    PrintLine(TEXT("Guess the %i letters word!"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess \nand press enter to continue..."));

    // For real player need to press TAB and then start inputing guess...
    // Promt player for guess
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();

    if (!isPlayerWon)
    {
        if (PlayerLives > 0) // Check if lives is greater then zero
        {
            PrintLine(TEXT("Your guess: ") + Input);

            // Check isIsogram for PlayerGuess
            if (!isPlayerGuessValid(Input))
            {
                PrintLine(TEXT("It is %i Characters Long, try again!"), HiddenWord.Len());
            }
            else
            {

                if (HiddenWord == Input)
                {
                    PrintLine(TEXT("You won!"));
                    isPlayerWon = true;
                    // Ask the Player if he wants play again?
                }
                else
                {
                    PlayerLives--;
                    PrintLine(TEXT("Wrong guess! You lost 1 live."));
                    PrintLine(TEXT("Current lives: %i"), PlayerLives);
                }
            }
        }
        else
        {
            PrintLine(TEXT("You have lose!"));
            // Ask the Player if he wants play again?
            return;
        }
    }
    else
    {
        PrintLine(TEXT("You already won this game!"));
    }
}

void UBullCowCartridge::SetupGame()
{
    // HiddenWord must be set from list of isograms
    HiddenWord = TEXT("team");

    PlayerLives = 3;     // Set Lives
    isPlayerWon = false; // Set flag isPlayerWon
}

bool UBullCowCartridge::isPlayerGuessValid(FString PlayerGuess)
{
    if (PlayerGuess.Len() == HiddenWord.Len())
    {
        return true;
    }
    return false;
}