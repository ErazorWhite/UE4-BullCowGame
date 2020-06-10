// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame(); // Setting Up Game

    PrintLine(TEXT("HiddenWord: %s."), *HiddenWord); // Debug Line

    // For real player need to press TAB and then start inputing guess...
    // Promt player for guess
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    if (!bGameOver)
    {
        PrintLine(TEXT("Your guess: %s"), *Input);
        ProcessGuess(Input);        
    }
    else
    {
        PrintLine(TEXT("Game is over!"));
        SetupGame();
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the Player
    ClearScreen();
    PrintLine(TEXT("Welcome to Bull Cows."));
    PrintLine(TEXT("Guess the %i letters word!"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess \nand press enter to continue..."));

    // HiddenWord must be set from list of isograms
    HiddenWord = TEXT("team");
    PlayerLives = 3;
    bGameOver = false;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to continue..."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (HiddenWord == Guess)
    {
        ClearScreen();
        PrintLine(TEXT("You won!"));
        EndGame();
        return;
        // Ask the Player if he wants play again?
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("It is %i Characters Long, try again!"), HiddenWord.Len());
        return;
    }

    // if (!IsIsogram)
    // {
    //     PrintLine(TEXT("Guess must be with no repeating letters."));
    // }

    PrintLine(TEXT("Wrong guess! You lost 1 live."));
    PrintLine(TEXT("Current lives: %i"), --PlayerLives);

    if (PlayerLives <= 0) // Check if lives is greater then zero
    {
        ClearScreen();
        PrintLine(TEXT("Have no lives left!"));
        PrintLine(TEXT("The hidden word was %s."), *HiddenWord); // Debug Line
        EndGame();
        return;
    }
}