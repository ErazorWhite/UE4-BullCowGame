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
    // ValidHiddenWord must be set from list of isograms
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    PlayerLives = HiddenWord.Len() * 2;
    bGameOver = false;

    // Welcoming the Player
    ClearScreen();
    PrintLine(TEXT("Welcome to Bull Cows."));

    PrintLine(TEXT("Guess the %i letters word!"), HiddenWord.Len());
    PrintLine(TEXT("HiddenWord: %s."), *HiddenWord); // Debug Line
    PrintLine(TEXT("Type in your guess \nand press enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to continue..."));
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
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

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("Guess must be with no repeating letters."));
        PrintLine(TEXT("Try again."));
        return;
    }

    if (PlayerLives <= 0) // Check if lives is greater then zero
    {
        ClearScreen();
        PrintLine(TEXT("Have no lives left!"));
        PrintLine(TEXT("The hidden word was %s."), *HiddenWord); // Debug Line
        EndGame();
        return;
    }

    // GetBullCows(const FString& Guess, int32& BullCOunt, int32& CowCount);
    FBullCowCount Score = GetBullCows(Guess);
    PrintLine(TEXT("ou have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

    PrintLine(TEXT("Wrong guess! You lost 1 live."));
    PrintLine(TEXT("Current lives: %i"), --PlayerLives);
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

const FBullCowCount UBullCowCartridge::GetBullCows(const FString &Guess)
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}