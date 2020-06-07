// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Welcoming the Player
    PrintLine(TEXT("Welcome to Bull Cows."));
    PrintLine(TEXT("Guess the 4 letter word."));
    PrintLine(TEXT("Press enter to continue..."));

    SetupGame(); // Setting Up Game

    // For real player need to press TAB and then start inputing guess...
    // Promt player for guess
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();

    // Validate PlayerGuess

    if (!isPlayerWon)
    {
        if (PlayerLives > 0) // Check if lives is greater then zero
        {
            PrintLine(TEXT("Your guess: ") + Input);

            // Check isIsogram for PlayerGuess
            // Check isCorrectNumberOfSymbols for PlayerGuess
            // If not ^ Promt to guess again

            if (HiddenWord == Input)
            {
                PrintLine(TEXT("You won!"));
                isPlayerWon = true;
                // Ask the Player if he wants play again?
            }
            else
            {
                PrintLine(TEXT("Wrong guess! You lost 1 live."));
                PlayerLives--;
                FString toString = FString::Printf(TEXT("%d"), PlayerLives);
                PrintLine(TEXT("Current lives: ") + toString);
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

    PlayerLives = 3;    // Set Lives
    isPlayerWon = false; // Set flag isPlayerWon
}