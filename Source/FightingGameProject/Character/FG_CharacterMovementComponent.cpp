// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_CharacterMovementComponent.h"

#include "FightingGameProject/MyMath.h"


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

	//Handle Ground Check
	if (CheckGrounded())
	{
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

	//Handle Turning delta
	TurnDelta = PreviousYaw - GetOwner()->GetActorRotation().Yaw;
	PreviousYaw = GetOwner()->GetActorRotation().Yaw;
	
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

void UFG_CharacterMovementComponent::Walk(FVector Direction, const float Acceleration, const float MaxWalkSpeed)
{
	Direction.Normalize();

	FVector AccelToAdd = Direction * Acceleration;
	FVector GroundVelocity = FMyMath::ZeroZVector(GetVelocity());

	float AccelGroundDot = FVector::DotProduct(AccelToAdd, GroundVelocity.GetSafeNormal());
	if (AccelGroundDot <= 0)
	{
		//If it's below zero it will not add more velocity, so reduce the factor to 0.
		AccelGroundDot = 0;
	}

	//I still wish I had a better name for this value
	FVector AccelFactor = AccelGroundDot * GroundVelocity.GetSafeNormal();

	if (GroundVelocity.Size() > MaxWalkSpeed)
	{
		//When moving too fast, it will subtract the correct amount to not overshoot the MaxWalkSpeed
		AccelToAdd = AccelToAdd - AccelFactor;
	}

	//Projects the acceltoAdd onto the current plane to more smoothly follow along surfaces
	FHitResult Hit;
	FVector SweepVector = ColliderRef->GetComponentLocation() + FVector::DownVector * 0.5f;
	FCollisionShape Shape = FCollisionShape::MakeCapsule(ColliderRef->GetScaledCapsuleRadius(), ColliderRef->GetScaledCapsuleHalfHeight());
	FCollisionQueryParams Param;
	Param.AddIgnoredActor(GetOwner());
	
	GetWorld()->SweepSingleByChannel(Hit, ColliderRef->GetComponentLocation(), SweepVector, ColliderRef->GetComponentRotation().Quaternion(),
		ECollisionChannel::ECC_WorldStatic, Shape, Param);

	if (AccelToAdd.Z > 1)
	{
		AccelToAdd = AccelToAdd.VectorPlaneProject(AccelToAdd, Hit.Normal);
	}
	

	AddForce(AccelToAdd);
}

void UFG_CharacterMovementComponent::HandleWalk(float Axis)
{
	FVector WalkVelocityDelta = FVector::RightVector * Axis * WalkSpeed;
}


void UFG_CharacterMovementComponent::RotateCharacter(FVector Direction, const float RotationSpeed)
{
	Direction = FMyMath::ZeroZVector(Direction);
	Direction.Normalize();
	
	FRotator OldRot = GetOwner()->GetActorRotation();
	FRotator NewRot = Direction.Rotation();
	NewRot = FMath::Lerp(OldRot, NewRot, RotationSpeed);
	
	GetOwner()->SetActorRotation(NewRot);
}

float UFG_CharacterMovementComponent::GetTurningDelta()
{
	return TurnDelta;
}

void UFG_CharacterMovementComponent::Jump()
{
	Velocity.Z = JumpForce;
}

FVector UFG_CharacterMovementComponent::GetVelocity()
{
	return Velocity; //watch the master of encapsulation at work
}

void UFG_CharacterMovementComponent::OnLanded_Implementation()
{
	
}

void UFG_CharacterMovementComponent::ApplyGravity()
{
	AddForce(FVector::UpVector * Gravity);
}

void UFG_CharacterMovementComponent::ApplyFriction()
{
	FVector GroundVelocity = FMyMath::ZeroZVector(Velocity);
	FVector DeaccelVector = FMyMath::MoveTowards(GroundVelocity, FVector::Zero(), Friction * GetWorld()->DeltaTimeSeconds);
	DeaccelVector.Z = Velocity.Z;

	Velocity = DeaccelVector;
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
		if (!bIsGrounded)
		{
			OnLanded_Implementation();
		}
		bIsGrounded = true;
		return true;
	}
	bIsGrounded = false;
	return false;
}

