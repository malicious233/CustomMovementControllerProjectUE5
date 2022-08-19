// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_GasmaskGuy.h"


// Sets default values
AFG_GasmaskGuy::AFG_GasmaskGuy()
{
	
}

void AFG_GasmaskGuy::BeginPlay()
{
	Super::BeginPlay();

	//Construct state object before doing anything else
	IdleState = NewObject<UFG_BaseState>(this, IdleStateClass);
	AirborneState = NewObject<UFG_BaseState>(this, AirborneStateClass);
	
	//...

	ActiveState = IdleState;
	SetState(IdleState);
}

void AFG_GasmaskGuy::SetState(UFG_BaseState* ToState) 
{
	//I think I can move this function into BaseCharacter
	
	ActiveState->Exit();
	ActiveState = ToState;
	ActiveState->Enter();
}

void AFG_GasmaskGuy::Ping()
{
	MoveComp->AddImpulse(FVector::UpVector * 600.f);
	GEngine->AddOnScreenDebugMessage(
		INDEX_NONE,
		1.0f,
		FColor::Blue,
		FString::Printf(TEXT("Ping!"))); //Printf returns a string
}

void AFG_GasmaskGuy::Pinging()
{
	
	GEngine->AddOnScreenDebugMessage(
			INDEX_NONE,
			0.0f,
			FColor::Blue,
			FString::Printf(TEXT("Pinging!"))); //Printf returns a string
}

