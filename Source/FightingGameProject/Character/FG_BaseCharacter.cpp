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
	
	CameraSpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	CameraSpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(CameraSpringArmComp);
}

// Called when the game starts or when spawned
void AFG_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFG_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentButtonBufferDuration -= DeltaTime;
	if (CurrentButtonBufferDuration < 0)
	{
		ButtonInputBuffer = EButtonInput::NONE;
	}
	
	ActiveState->Tick(DeltaTime);
}

// Called to bind functionality to input
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

float AFG_BaseCharacter::GetHorizontalInput()
{
	return HorizontalInput;
}

float AFG_BaseCharacter::GetVerticalInput()
{
	return VerticalInput;
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
