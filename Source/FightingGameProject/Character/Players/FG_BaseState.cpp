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
	//Go through all possible actions for this state and see if I am already buffering something
	for (const UFG_Action* Action: (PossibleActions))
	{
		if (Action->ButtonInput == GetFGCharacter()->ButtonInputBuffer)
		{
			Action->Delegate.ExecuteIfBound(); //Perform action immediately
			
			GEngine->AddOnScreenDebugMessage(
			INDEX_NONE,
			1.0f,
			FColor::Blue,
			FString::Printf(TEXT("Buffered!"))); //Printf returns a string
			break;
			//Perhaps I do not need to have the break be mandatory here incase some bufferable actions dont stop other bufferable actions-
			//-since not all bufferable actions hop into a new Finitestatemachine state
		}
	}

	GetFGCharacter()->ButtonInputBuffer = EButtonInput::NONE; //Clear buffer as not to allow buffering onto other states
}

void UFG_BaseState::Exit_Implementation()
{
	
}



AFG_BaseCharacter* UFG_BaseState::GetFGCharacter()
{
	return OwnerFGCharacter;
}


