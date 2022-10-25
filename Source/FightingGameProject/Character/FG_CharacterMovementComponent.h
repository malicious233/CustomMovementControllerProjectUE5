// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CapsuleComponent.h"
#include "FG_CharacterMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIGHTINGGAMEPROJECT_API UFG_CharacterMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFG_CharacterMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public: //Public Functions
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	//Physics Functions
	
	UFUNCTION(BlueprintCallable)
	void AddForce(const FVector& Force);

	UFUNCTION(BlueprintCallable)
	void AddImpulse(const FVector& Impulse);

	UFUNCTION(BlueprintPure)
	bool IsGrounded();

	//Character Functions

	UFUNCTION(BlueprintCallable)
	void Walk(FVector Direction, const float Acceleration, const float MaxWalkSpeed);
	
	UFUNCTION(BlueprintCallable)
	void HandleWalk(const float Axis);

	/**
	 * @brief Lerps characters Yaw
	 * @param Direction 
	 * @param RotationSpeed 
	 */
	UFUNCTION(BlueprintCallable)
	void RotateCharacter(FVector Direction, const float RotationSpeed);

	UFUNCTION(BlueprintPure)
	float GetTurningDelta();
	
	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION(BlueprintPure)
	FVector GetVelocity();

	//Events
	UFUNCTION(BlueprintNativeEvent)
	void OnLanded();


private: //Private Functions
	void ApplyGravity();

	void ApplyFriction();

	bool CheckGrounded();
	
private: //Private variables
	FVector Velocity = FVector::ZeroVector;

	bool bIsGrounded;

	float PreviousYaw;
	float TurnDelta;

	float FloatingDetectionDisabledTimer; //How long is the ground detection and hovering disabled. Used when jumping
	
	
public: //Public variables
	UPROPERTY(EditAnywhere)
	float Gravity = -200.f;

	UPROPERTY(EditAnywhere)
	float WalkSpeed = 200.f;

	UPROPERTY(EditAnywhere)
	float JumpForce = 600.f;

	UPROPERTY(EditAnywhere)
	float Friction = 60.f;

	UPROPERTY(EditAnywhere)
	float FloatHeight = 60.f; //The height of which you hover above the floor. Needed for object clearance and following inclined slopes. 

	UPROPERTY(EditAnywhere)
	float FloatRayDistance = 65.f; //The distance to check for floor to snap onto. Keep this a bit longer than the FloatHeight to more smoothly follow slopes

	UCapsuleComponent* ColliderRef;
};
