// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_GasmaskGuy_AirborneState.h"
#include "FG_GasmaskGuy.h"

void UFG_GasmaskGuy_AirborneState::Tick_Implementation(float DeltaTime)
{
	Super::Tick_Implementation(DeltaTime);
	
	AFG_GasmaskGuy* G = GetOwner(); //I am lazy
	if ((G->MoveComp->IsGrounded()))
	{
		G->SetState(G->IdleState);
	}

	if (GetOwner()->GetCameraInputVector().Rotation() != FRotator::ZeroRotator)
	{
		GetOwner()->MoveComp->RotateCharacter(GetOwner()->MoveComp->GetVelocity().GetSafeNormal(), 10 * DeltaTime);
	}

	//Add a reduced move force
	GetOwner()->MoveComp->Walk(GetOwner()->GetCameraInputVector(), GetOwner()->WalkSpeed * 0.4f, GetOwner()->MaxWalkSpeed);
}
