// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString& Guess);
	const bool IsIsogram(const FString& Guess);
	const TArray<FString> GetValidHiddenWords();
	const FBullCowCount GetBullCows(const FString& Guess);

	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 PlayerLives;
	bool bGameOver;
	TArray<FString> WordsList;
	TArray<FString> Isograms;

};
