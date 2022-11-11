// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FightingGameProject/Character/FG_BaseCharacter.h"
#include "UObject/Object.h"
#include "FG_Action.generated.h"

/**
 * Object which stores a function pointer and a button input.
 * Used in FG_BaseCharacter as essentially an inputbinding wrapper to work with input buffering actions
 */
UCLASS()
class FIGHTINGGAMEPROJECT_API UFG_Action : public UObject
{
	GENERATED_BODY()

public:
	UFG_Action();
	
	UPROPERTY()
	EButtonInput ButtonInput;
	
	FSimpleDelegate Delegate; //This doesnt need to be garbage collected seemingly

public:
};
