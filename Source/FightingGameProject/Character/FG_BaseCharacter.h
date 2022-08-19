// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FG_CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "Players/FG_BaseState.h"
#include "Players/FG_InputBinderComponent.h"
#include "FG_BaseCharacter.generated.h"

UENUM(BlueprintType)
enum class EButtonInput : uint8
{
	NONE,
	LIGHT,
	HEAVY,
	JUMP,
};

UENUM(BlueprintType)
enum class EDirectionInput : uint8
{
	NONE,
	FORWARD,
	BACKWARD,
	UP,
	DOWN
};

UCLASS()
class FIGHTINGGAMEPROJECT_API AFG_BaseCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFG_BaseCharacter();

protected: //Protected Overrides
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: //Public Overrides
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: //Functions

	//Returns active state
	UFUNCTION(BlueprintCallable)
	UFG_BaseState* GetState();
	


private:
	void HandleHorizontalInput(float Axis);
	void HandleVerticalInput(float Axis);

	void HandleJumpInput();

	void Test();

public: //Public Variables

	//Editor Exposed Variables
	UPROPERTY(EditAnywhere)
	float BufferDuration = 0.2f;
	
	//Components
	UPROPERTY(VisibleAnywhere)
	UFG_CharacterMovementComponent* MoveComp;

	UPROPERTY(VisibleAnywhere)
	UFG_InputBinderComponent* InputBinderComp;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Collider;

	//Values
	TArray<EButtonInput> ButtonInputBufferArray; //List of the order of button inputs. Will be relevant for the command input thing

	UPROPERTY()
	EButtonInput ButtonInputBuffer; //Last button input performed before buffer clears

protected: //Protected Stuff
	UPROPERTY()
	UFG_BaseState* ActiveState;

	/**
	 * @brief Call this on any button input. Resets the buffer timer.
	 */
	UFUNCTION()
	void OnButtonInput(EButtonInput InputEnum);

private: //Private Variables

	float CurrentButtonBufferDuration = 0;
	
	UPROPERTY()
	float HorizontalInput;

	UPROPERTY()
	float VerticalInput;
};


