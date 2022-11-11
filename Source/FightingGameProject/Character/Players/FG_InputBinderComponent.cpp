// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_InputBinderComponent.h"


/**
 * @brief This component is not used anymore. A similar behavior now just exists in the FG_BaseCharacter
 */
UFG_InputBinderComponent::UFG_InputBinderComponent()
{
	//Note for future self, be a bit wary of getting references for components in constructors, the order of how things happen is a bit mysterious.
	//InputCompRef = Cast<APawn>(GetOwner())->InputComponent;
	PrimaryComponentTick.bCanEverTick = true;
}

void UFG_InputBinderComponent::BeginPlay()
{
	Super::BeginPlay();
	InputCompRef = Cast<APawn>(GetOwner())->InputComponent;
}

void UFG_InputBinderComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

template <class UserClass>
void UFG_InputBinderComponent::BindAxisToState(FName AxisName,
	FInputActionHandlerSignature::TMethodPtr<UserClass> Func)
{
	if (InputCompRef == nullptr)
	{
		return;
	}
	FInputAxisBinding bind = GetOwner()->InputComponent->BindAxis(AxisName, GetOwner(), Func);
	AddAxisBinding(bind);
}

template<class UserClass>
void UFG_InputBinderComponent::BindActionToState(FName ActionName, EInputEvent EventType,
	FInputActionHandlerSignature::TMethodPtr<UserClass> Func)
{
	if (InputCompRef == nullptr)
	{
		return;
	}
	FInputActionBinding bind = GetOwner()->InputComponent->BindAction(ActionName, EventType, GetOwner(), Func);
	AddActionBinding(bind);
}


bool UFG_InputBinderComponent::CompareInputAxisBindings(FInputAxisBinding lhs, FInputAxisBinding rhs)
{
	return lhs.AxisDelegate.GetDelegateForManualSet().GetHandle() == rhs.AxisDelegate.GetDelegateForManualSet().GetHandle() && lhs.AxisName == rhs.AxisName;
}

bool UFG_InputBinderComponent::CompareInputActionBindings(FInputActionBinding lhs, FInputActionBinding rhs)
{
	return lhs.ActionDelegate.GetDelegateForManualSet().GetHandle() == rhs.ActionDelegate.GetDelegateForManualSet().GetHandle() && lhs.GetActionName() == rhs.GetActionName();
}



void UFG_InputBinderComponent::AddAxisBinding(FInputAxisBinding Item)
{
	RememberedAxisBindings.Add(Item);
}

void UFG_InputBinderComponent::AddActionBinding(FInputActionBinding Item)
{
	RememberedActionBindings.Add(Item);
}

void UFG_InputBinderComponent::EmptyAxisBindings(UInputComponent& InputComp)
{
	//Loops through all axis remembered axis bindings
	for (int32 i = 0; i < RememberedAxisBindings.Num(); ++i)
	{
		//Then loops through all the axis bindings in the input component.
		//TODO: Question whether or not InputComp should be reference type... is there too much copying going on here?
		for (int32 b = 0; b < InputComp.AxisBindings.Num(); ++b)
		{

			//If they are the same, remove that binding and keep on iterating
			FInputAxisBinding binding = InputComp.AxisBindings[b];
			if (CompareInputAxisBindings(binding, RememberedAxisBindings[i]))
			{
				InputComp.AxisBindings.RemoveAt(b);
				b--;
				continue;
			}
		}
		
	}
	//RememberedAxisBindings.Empty();
}

void UFG_InputBinderComponent::EmptyActionBindings(UInputComponent& InputComp)
{
	//Loops through all axis remembered axis bindings
	for (int i = 0; i < RememberedActionBindings.Num(); ++i)
	{
		//Then loops through all the axis bindings in the input component.
		//TODO: Question whether or not InputComp should be reference type... is there too much copying going on here?
		for (int b = 0; b < InputComp.GetNumActionBindings(); ++b)
		{

			//If they are the same, remove that binding and keep on iterating
			FInputActionBinding binding = InputComp.GetActionBinding(b);
			if (CompareInputActionBindings(binding, RememberedActionBindings[i]))
			{
				GEngine->AddOnScreenDebugMessage(
					INDEX_NONE,
					1.0f,
					FColor::Blue,
					FString::Printf(TEXT("Removed an Action bind!"))); //Printf returns a string
				InputComp.RemoveActionBinding(b);
				
				b--;
				continue;
			}
		}
		
	}
	//RememberedActionBindings.Empty();
}

void UFG_InputBinderComponent::EmptyBindings(UInputComponent& InputComponent)
{
	EmptyAxisBindings(InputComponent);
	EmptyActionBindings(InputComponent);
}
