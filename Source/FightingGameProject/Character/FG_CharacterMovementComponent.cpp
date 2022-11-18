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

	//Handle floating and ground check
	//The player hovers a few units above the floor with a single ray that is being casted down.
	//This means that the capsule colliders height doesn't exactly represent the actual height of the player
	FloatingDetectionDisabledTimer -= DeltaTime;
	if (FloatingDetectionDisabledTimer < 0)
	{
		FVector Start = GetOwner()->GetActorLocation();
		FVector End = Start + FVector::DownVector * FloatRayDistance;

		FHitResult Hit;
		FCollisionQueryParams Param;
		Param.AddIgnoredActor(GetOwner());
	
		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Param))
		{
			bIsGrounded = true;
			Velocity.Z = 0;
			float Height = FMath::FInterpTo(Start.Z, Hit.Location.Z + FloatHeight, DeltaTime, 15.f);
			FVector ToVector = Start;
			ToVector.Z = Height;
			GetOwner()->SetActorLocation(ToVector);
			ApplyFriction();
		}
		else
		{
			bIsGrounded = false;
			ApplyGravity();
		}
	}
	else
	{
		//The trail of logic of this if-else-thing can probably be improved but it works for now
		bIsGrounded = false;
		ApplyGravity();
	}
	
	

	
	
}


void UFG_CharacterMovementComponent::AddForce(const FVector& Force)
{
	Velocity += Force * GetWorld()->GetDeltaSeconds();
}

void UFG_CharacterMovementComponent::AddImpulse(const FVector& Impulse)
{
	if (Impulse.Z != 0)
	{
		FloatingDetectionDisabledTimer = 0.1;
	}
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
	FVector GroundVelocity = UMyMath::ZeroZVector(GetVelocity());

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
	Direction = UMyMath::ZeroZVector(Direction);
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
	OnJump.Broadcast();
	FloatingDetectionDisabledTimer = 0.3; //Briefly disabled the ground detection and hovering as not to immediately snap back to the floor
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
	FVector GroundVelocity = UMyMath::ZeroZVector(Velocity);
	FVector DeaccelVector = UMyMath::MoveTowards(GroundVelocity, FVector::Zero(), Friction * GetWorld()->DeltaTimeSeconds);
	DeaccelVector.Z = Velocity.Z;

	Velocity = DeaccelVector;
}


bool UFG_CharacterMovementComponent::CheckGrounded()
{
	/*
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
	*/
	return false;
}

