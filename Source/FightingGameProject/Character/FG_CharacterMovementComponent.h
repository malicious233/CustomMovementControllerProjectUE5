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

	UFUNCTION(BlueprintCallable)
	bool IsGrounded();

	//Character Functions
	UFUNCTION(BlueprintCallable)
	void HandleWalk(const float Axis);

	UFUNCTION(BlueprintCallable)
	void Jump();

private: //Private Functions
	void ApplyGravity();

	bool CheckGrounded();
	
private: //Private variables
	FVector Velocity = FVector::ZeroVector;

	bool bIsGrounded;
	
	
public: //Public variables
	UPROPERTY(EditAnywhere)
	float Gravity = -200.f;

	UPROPERTY(EditAnywhere)
	float WalkSpeed = 200.f;

	UPROPERTY(EditAnywhere)
	float JumpForce = 600.f;

	UCapsuleComponent* ColliderRef;
};
