// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FightingGameProject/Character/FG_Action.h"
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

	
	TArray<UFG_Action*> PossibleActions; //List of actions you can do in this state.

	UFUNCTION(BlueprintCallable)
	inline AFG_BaseCharacter* GetFGCharacter();

	
	template<typename T>
	void RegisterButtonAction(EButtonInput Button, T* ThisClass, void(T::*Func)(void))
	{
		FSimpleDelegate PtrFunc;
		PtrFunc.BindUObject(ThisClass, Func);
		UFG_Action* Action = NewObject<UFG_Action>();
		Action->ButtonInput = Button;
		Action->Delegate = PtrFunc;
		PossibleActions.Add(Action);
	}
	
private: //Private Functions
	

private: //Private Variables
	UPROPERTY()
	AFG_BaseCharacter* OwnerFGCharacter;
};

