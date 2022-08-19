// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FG_BaseState.generated.h"

/**
 * 
 */

class AFG_BaseCharacter;

UCLASS()
class FIGHTINGGAMEPROJECT_API UFG_BaseState : public UObject
{
	GENERATED_BODY()

	
	
public: //Public Functions

	UFG_BaseState();
	
	//Called every frame
	UFUNCTION(BlueprintNativeEvent)
	void Tick(float DeltaTime);

	//Called on enter
	UFUNCTION(BlueprintNativeEvent)
	void Enter();

	//Called when you exit
	UFUNCTION(BlueprintNativeEvent)
	void Exit();

	//TODO: Add an array of Actions which you subscribe to when you enter any state.

	UFUNCTION(BlueprintCallable)
	AFG_BaseCharacter* GetFGCharacter();
	
private: //Private Functions
	

private: //Private Variables
	UPROPERTY()
	AFG_BaseCharacter* OwnerFGCharacter;
};

