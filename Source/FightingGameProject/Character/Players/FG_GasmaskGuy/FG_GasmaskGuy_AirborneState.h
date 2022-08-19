// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FG_GasmaskGuy_BaseState.h"
#include "FG_GasmaskGuy_AirborneState.generated.h"

/**
 * 
 */

class UFG_GasmaskGuy_BaseState;

UCLASS(Blueprintable)
class FIGHTINGGAMEPROJECT_API UFG_GasmaskGuy_AirborneState : public UFG_GasmaskGuy_BaseState
{
	GENERATED_BODY()

	void Tick_Implementation(float DeltaTime) override;
};
