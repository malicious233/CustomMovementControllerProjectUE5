// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FightingGameProject/Character/Players/FG_BaseState.h"
#include "FG_GasmaskGuy_BaseState.generated.h"

/**
 * 
 */

class UFG_BaseState;
class AFG_GasmaskGuy;

UCLASS(Blueprintable)
class FIGHTINGGAMEPROJECT_API UFG_GasmaskGuy_BaseState : public UFG_BaseState
{
	GENERATED_BODY()

private:
	UPROPERTY()
	AFG_GasmaskGuy* Owner;

	UPROPERTY()
	UFG_CharacterMovementComponent* MoveCompRef;
	
public:
	UFG_GasmaskGuy_BaseState();
	
	UFUNCTION(BlueprintCallable)
	AFG_GasmaskGuy* GetOwner();

	UFUNCTION()
	UFG_CharacterMovementComponent* GetMoveComp();
};
