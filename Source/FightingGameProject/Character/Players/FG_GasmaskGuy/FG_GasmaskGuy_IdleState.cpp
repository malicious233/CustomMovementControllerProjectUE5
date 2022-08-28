// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_GasmaskGuy_IdleState.h"
#include "FightingGameProject/Character/Players/FG_BaseState.h"
#include "FG_GasmaskGuy.h"

UFG_GasmaskGuy_IdleState::UFG_GasmaskGuy_IdleState()
{
	
	//PossibleActions.Add(Action);
	

}

void UFG_GasmaskGuy_IdleState::Enter_Implementation()
{
	Super::Enter_Implementation();

	/*
	FSimpleDelegate PtrFunc;
	PtrFunc.BindUObject(GetOwner()->MoveComp, &UFG_CharacterMovementComponent::Jump);
	UFG_Action* Action = NewObject<UFG_Action>();
	Action->ButtonInput = EButtonInput::JUMP;
	Action->Delegate = PtrFunc;
	PossibleActions.Add(Action);
	*/
	
	RegisterButtonAction<UFG_CharacterMovementComponent>(EButtonInput::JUMP, GetOwner()->MoveComp, &UFG_CharacterMovementComponent::Jump);
	
	//This works but should really be converted into a function
	
	//AFG_GasmaskGuy* G = GetOwner(); //I am lazy
	//FInputActionBinding bind = GetOwner()->InputComponent->BindAction(TEXT("Jump"), IE_Pressed, GetOwner(), &AFG_GasmaskGuy::Ping);
	//GetOwner()->InputBinderComp->AddActionBinding(bind);
	//This seems to be getting flushed by the InputBinder on exit, which is not intended!

	
	//TODO:Binding on entering a state might not be a good idea, as the InputComponent will be null if the player isnt possessed.
	//TODO:

	//G->InputBinderComp->BindActionToState(TEXT("Jump"), IE_Pressed, &AFG_GasmaskGuy::Ping));
	
}

void UFG_GasmaskGuy_IdleState::Tick_Implementation(float DeltaTime)
{
	Super::Tick_Implementation(DeltaTime);
	
	AFG_GasmaskGuy* G = GetOwner(); //I am lazy
	if (!G->MoveComp->IsGrounded())
	{
		G->SetState(G->AirborneState);
	}
	
}
