// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_CharacterMovementComponent.h"


// Sets default values for this component's properties
UFG_CharacterMovementComponent::UFG_CharacterMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFG_CharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFG_CharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Owner = GetOwner();

	
	if (CheckGrounded())
	{
		//Velocity.Z = 0;
		GEngine->AddOnScreenDebugMessage(
		INDEX_NONE,
		0.0f,
		FColor::Blue,
		FString::Printf(TEXT("GROUNDED"))); //Printf returns a string
		ApplyFriction();
	}
	else
	{
		ApplyGravity();
	}

	//Collision and handle depenetration
	int Iterations = 10;
	float RemainingTime = DeltaTime;
	while (RemainingTime > 0.f && ++Iterations << 10)
	{
		FHitResult Hit;
		Owner->AddActorWorldOffset(Velocity * RemainingTime, true, &Hit);

		//If hit, depenetrate
		if (Hit.bBlockingHit)
		{
			if (Hit.bStartPenetrating)
			{
				Owner->AddActorWorldOffset(Hit.Normal * (Hit.PenetrationDepth + 0.1f));
			}
			else
			{
				
				Velocity = FVector::VectorPlaneProject(Velocity, Hit.Normal);
				RemainingTime -= RemainingTime * Hit.Time;
				//Hit time is percentage travelled before hit
				
			}
		}
		else
		{
			break;
		}
	}

	
}


void UFG_CharacterMovementComponent::AddForce(const FVector& Force)
{
	Velocity += Force * GetWorld()->GetDeltaSeconds();
}

void UFG_CharacterMovementComponent::AddImpulse(const FVector& Impulse)
{
	Velocity += Impulse;
}

bool UFG_CharacterMovementComponent::IsGrounded()
{
	return bIsGrounded;
}

void UFG_CharacterMovementComponent::HandleWalk(float Axis)
{
	FVector WalkVelocityDelta = FVector::RightVector * Axis * WalkSpeed;
}

void UFG_CharacterMovementComponent::Jump()
{
	Velocity.Z = JumpForce;
}

FVector UFG_CharacterMovementComponent::GetVelocity()
{
	return Velocity; //watch the master on encapsulation at work
}

void UFG_CharacterMovementComponent::ApplyGravity()
{
	AddForce(FVector::UpVector * Gravity);
}

void UFG_CharacterMovementComponent::ApplyFriction()
{
	FVector FrictionVector = -FVector(FVector(Velocity.X, Velocity.Y, 0) * Friction);
	AddForce(FrictionVector);
}

bool UFG_CharacterMovementComponent::CheckGrounded()
{
	FHitResult Hit;

	FVector SweepVector = ColliderRef->GetComponentLocation() + FVector::DownVector * 0.5f;
	FCollisionShape Shape = FCollisionShape::MakeCapsule(ColliderRef->GetScaledCapsuleRadius(), ColliderRef->GetScaledCapsuleHalfHeight());
	FCollisionQueryParams Param;
	Param.AddIgnoredActor(GetOwner());
	
	GetWorld()->SweepSingleByChannel(Hit, ColliderRef->GetComponentLocation(), SweepVector, ColliderRef->GetComponentRotation().Quaternion(),
		ECollisionChannel::ECC_WorldStatic, Shape, Param);
	if (Hit.bBlockingHit) //Check if the Z velocity check was neccessary
	{
		GEngine->AddOnScreenDebugMessage(
		INDEX_NONE,
		0.0f,
		FColor::Blue,
		FString::Printf(TEXT("Hit: %s"), *Hit.GetActor()->GetName())); //Printf returns a string
		bIsGrounded = true;
		return true;
	}
	bIsGrounded = false;
	return false;
}

