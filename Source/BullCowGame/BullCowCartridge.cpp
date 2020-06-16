// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Containers/Array.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    Isograms = GetValidHiddenWords();
    SetupGame(); // Setting Up Game

    // PrintLine(TEXT("Number of possible words is: %i."), WordsList.Num()); // Debug Line
    // PrintLine(TEXT("Number of valid words is: %i."), Isograms.Num());   // Debug Line

    // For real player need to press TAB and then start inputing guess...
    // Promt player for guess
}

void UBullCowCartridge::OnInput(const FString &PlayerInput) // When the player hits enter
{
    if (!bGameOver)
    {
        PrintLine(TEXT("Your guess: %s"), *PlayerInput);
        ProcessGuess(PlayerInput);
    }
    else
    {
        PrintLine(TEXT("Game is over!"));
        SetupGame();
    }
}

void UBullCowCartridge::SetupGame()
{
    // ValidWord must be set from list of isograms
    ValidWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    PlayerLives = 3;
    bGameOver = false;

    // Welcoming the Player
    ClearScreen();
    PrintLine(TEXT("Welcome to Bull Cows."));
    PrintLine(TEXT("Guess the %i letters word!"), ValidWord.Len());
    PrintLine(TEXT("Type in your guess \nand press enter to continue..."));
    PrintLine(TEXT("ValidWord: %s."), *ValidWord); // Debug Line
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to continue..."));
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
    if (ValidWord == Guess)
    {
        ClearScreen();
        PrintLine(TEXT("You won!"));
        EndGame();
        return;
        // Ask the Player if he wants play again?
    }

    if (Guess.Len() != ValidWord.Len())
    {
        PrintLine(TEXT("It is %i Characters Long, try again!"), ValidWord.Len());
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("Guess must be with no repeating letters."));
        PrintLine(TEXT("Try again."));
        return;
    }

    PrintLine(TEXT("Wrong guess! You lost 1 live."));
    PrintLine(TEXT("Current lives: %i"), --PlayerLives);

    if (PlayerLives <= 0) // Check if lives is greater then zero
    {
        ClearScreen();
        PrintLine(TEXT("Have no lives left!"));
        PrintLine(TEXT("The hidden word was %s."), *ValidWord); // Debug Line
        EndGame();
        return;
    }
}

const bool UBullCowCartridge::IsIsogram(const FString &Guess)
{
    for (int Index = 0; Index < Guess.Len(); Index++)
    {
        for (int Comparison = Index + 1; Comparison < Guess.Len(); Comparison++)
        {
            if (Guess[Index] == Guess[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

const TArray<FString> UBullCowCartridge::GetValidHiddenWords()
{
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(WordsList, *WordListPath);

    TArray<FString> Isograms;

    for (FString Word : WordsList)
    {
        if (IsIsogram(Word) && Word.Len() >= 4 && Word.Len() <= 8)
        {
            Isograms.Emplace(Word);
        }
    }

    return Isograms;
}