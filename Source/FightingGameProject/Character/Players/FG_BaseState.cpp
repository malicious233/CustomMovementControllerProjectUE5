// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_BaseState.h"

#include "FightingGameProject/Character/FG_BaseCharacter.h"

UFG_BaseState::UFG_BaseState()
{
	OwnerFGCharacter = Cast<AFG_BaseCharacter>(GetOuter());
}

void UFG_BaseState::Tick_Implementation(float DeltaTime)
{
	
}

void UFG_BaseState::Enter_Implementation()
{
	for (const UFG_Action* Action: (PossibleActions))
	{
		if (Action->ButtonInput == GetFGCharacter()->ButtonInputBuffer)
		{
			Action->Delegate.ExecuteIfBound();
			break;
		}
	}
	
	if (GetFGCharacter()->ButtonInputBuffer != EButtonInput::NONE)
	{
		GEngine->AddOnScreenDebugMessage(
		INDEX_NONE,
		1.0f,
		FColor::Blue,
		FString::Printf(TEXT("Buffered!"))); //Printf returns a string

		GetFGCharacter()->ButtonInputBuffer = EButtonInput::NONE; //consume buffer
	}
}

void UFG_BaseState::Exit_Implementation()
{
	
}



AFG_BaseCharacter* UFG_BaseState::GetFGCharacter()
{
	return OwnerFGCharacter;
}


