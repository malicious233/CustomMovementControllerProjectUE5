// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_BaseCharacter.h"
#include "Players/FG_BaseState.h"


// Sets default values
AFG_BaseCharacter::AFG_BaseCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColliderComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	RootComponent = ColliderComp;
	
	MoveComp = CreateDefaultSubobject<UFG_CharacterMovementComponent>(TEXT("MovementComponent"));
	MoveComp->ColliderRef = ColliderComp;
	
	InputBinderComp = CreateDefaultSubobject<UFG_InputBinderComponent>(TEXT("InputBinderComponent"));

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	
	
	CameraSpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	CameraSpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(CameraSpringArmComp);
}

// Called when the game starts or when spawned
void AFG_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	//MoveComp->OnJump.AddDynamic(MoveComp, &UFG_CharacterMovementComponent::Jump);
	//Don't worry, I wanted to try to create an infinite loop for the funny on purpose and it sure worked. I'm leaving it here as a testament to my stupidity
}

// Called every frame
void AFG_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RootSomething = SkeletalMeshComp->RootBoneTranslation;
	
	//Handle camera relative input
	FVector CameraFwd0Z = CameraComp->GetForwardVector();
	CameraFwd0Z.Z = 0;

	FVector CameraRight0Z = -CameraComp->GetRightVector();
	CameraRight0Z.Z = 0;
	
	FVector Rel = (FVector(GetHorizontalInput() * CameraRight0Z + GetVerticalInput() * CameraFwd0Z)).GetSafeNormal();
	CameraInputVector = Rel;

	//Input Buffer timer
	CurrentButtonBufferDuration -= DeltaTime;
	if (CurrentButtonBufferDuration < 0)
	{
		ButtonInputBuffer = EButtonInput::NONE;
	}

	//Actually tick the state
	ActiveState->Tick(DeltaTime);
}

// Called to bind functionality to input. Dont bind character-specific methods here, let our custom Action system do that to support input buffering
void AFG_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction(FName("Jump"), IE_Pressed, this, &AFG_BaseCharacter::HandleJumpInput);
	InputComponent->BindAxis(FName("Horizontal"), this, &AFG_BaseCharacter::HandleHorizontalInput);
	InputComponent->BindAxis(FName("Vertical"), this, &AFG_BaseCharacter::HandleVerticalInput);
	
}

UFG_BaseState* AFG_BaseCharacter::GetState()
{
	return ActiveState;
}

FVector AFG_BaseCharacter::GetRootSomething()
{
	return RootSomething;
	//huh?
}

float AFG_BaseCharacter::GetHorizontalInput()
{
	return HorizontalInput;
}

float AFG_BaseCharacter::GetVerticalInput()
{
	return VerticalInput;
}

FVector AFG_BaseCharacter::GetInputVector()
{
	return InputVector;
}

FVector AFG_BaseCharacter::GetCameraInputVector()
{
	return CameraInputVector;
}



void AFG_BaseCharacter::HandleHorizontalInput(const float Axis)
{
	if (Axis != 0)
	{
		HorizontalInput = Axis;
	}
	else
	{

		HorizontalInput = 0;
	}
	InputVector = FVector(HorizontalInput, VerticalInput, 0).GetSafeNormal();
	
}

void AFG_BaseCharacter::HandleVerticalInput(const float Axis)
{
	if (Axis != 0)
	{
		VerticalInput = Axis;
	}
	else
	{

		VerticalInput = 0;
	}
	InputVector = FVector(HorizontalInput, VerticalInput, 0).GetSafeNormal();
	
}

void AFG_BaseCharacter::HandleJumpInput()
{
	OnButtonInput(EButtonInput::JUMP);
	
}

void AFG_BaseCharacter::Test()
{
	
	GEngine->AddOnScreenDebugMessage(
		INDEX_NONE,
		1.0f,
		FColor::Blue,
		FString::Printf(TEXT("Test"))); //Printf returns a string
}




void AFG_BaseCharacter::OnButtonInput(const EButtonInput Input)
{
	
	GEngine->AddOnScreenDebugMessage(
		INDEX_NONE,
		1.0f,
		FColor::Blue,
		FString::Printf(TEXT("Input: h"))); //Printf returns a string
	CurrentButtonBufferDuration = BufferDuration;
	ButtonInputBuffer = Input;

	for (UFG_Action* Action: (GetState()->PossibleActions))
	{
		if (Action->ButtonInput == Input)
		{
			Action->Delegate.ExecuteIfBound();
			break;
		}
	}
}
