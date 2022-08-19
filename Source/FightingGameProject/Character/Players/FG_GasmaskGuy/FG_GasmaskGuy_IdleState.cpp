﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_GasmaskGuy_IdleState.h"

#include "FG_GasmaskGuy.h"

void UFG_GasmaskGuy_IdleState::Enter_Implementation()
{
	Super::Enter_Implementation();

	AFG_GasmaskGuy* G = GetOwner(); //I am lazy
	FInputActionBinding bind = GetOwner()->InputComponent->BindAction(TEXT("Jump"), IE_Pressed, GetOwner(), &AFG_GasmaskGuy::Ping);
	GetOwner()->InputBinderComp->AddActionBinding(bind);
	
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
