// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FG_GasmaskGuy_BaseState.h"
#include "FG_GasmaskGuy_IdleState.generated.h"

/**
 * 
 */


UCLASS()
class FIGHTINGGAMEPROJECT_API UFG_GasmaskGuy_IdleState : public UFG_GasmaskGuy_BaseState
{
	GENERATED_BODY()

	void Enter_Implementation() override;
	
	void Tick_Implementation(float DeltaTime) override;
};
