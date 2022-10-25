// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_GasmaskGuy_IdleState.h"
#include "FightingGameProject/Character/Players/FG_BaseState.h"
#include "FG_GasmaskGuy_BaseState.h"
#include "FG_GasmaskGuy.h"

UFG_GasmaskGuy_IdleState::UFG_GasmaskGuy_IdleState()
{
}

void UFG_GasmaskGuy_IdleState::Enter_Implementation()
{
	Super::Enter_Implementation();

	AFG_GasmaskGuy* G = GetOwner(); //I am lazy
	if (!G->MoveComp->IsGrounded())
	{
		G->SetState(G->AirborneState);
	}
	//Registers all the possible actions in this state. The order of which they get subscribed determines the input priority. 
	//TODO: Do that you have an array of actions which automatically gets registered so that you can configure in the editor
	//TODO: Do that this is done once and cached instead of being called every time on Enter. This being called after the BaseState implementation is also causing some issues.
	//TODO: See if you can make this be nicely blueprintable.
	RegisterButtonAction<UFG_CharacterMovementComponent>(EButtonInput::JUMP, GetOwner()->MoveComp, &UFG_CharacterMovementComponent::Jump); //This for example registers with the jump button input the jump function from the move component.
	
}

void UFG_GasmaskGuy_IdleState::Tick_Implementation(float DeltaTime)
{
	Super::Tick_Implementation(DeltaTime);
	
	AFG_GasmaskGuy* G = GetOwner(); //I am lazy
	if (!G->MoveComp->IsGrounded())
	{
		G->SetState(G->AirborneState);
	}

	//Rotate
	if (GetOwner()->GetCameraInputVector().Rotation() != FRotator::ZeroRotator)
	{
		GetOwner()->MoveComp->RotateCharacter(GetOwner()->MoveComp->GetVelocity().GetSafeNormal(), 30 * DeltaTime);
	}
	
	//Add move force
	GetOwner()->MoveComp->Walk(GetOwner()->GetCameraInputVector(), GetOwner()->WalkSpeed, GetOwner()->MaxWalkSpeed);
	
}
