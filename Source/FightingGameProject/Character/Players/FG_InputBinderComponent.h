// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FG_InputBinderComponent.generated.h"


UCLASS(meta=(BlueprintSpawnableComponent))
class FIGHTINGGAMEPROJECT_API UFG_InputBinderComponent : public UActorComponent
{
	GENERATED_BODY()

	UFG_InputBinderComponent();
	
private: //Private Variables
	
	TArray<FInputAxisBinding> RememberedAxisBindings;
	//Does this need to be garbage collected somehow or does the TArray handle it?

	TArray<FInputActionBinding> RememberedActionBindings;
	//Ditto
	
	UPROPERTY()
	UInputComponent* InputCompRef;

private: //Private Functions
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: //Public Functions

	/**
	 * @brief Binds an Axis to a state which gets cleared when exiting state. If InputComponent is null it wont go through
	 * //DOESNT WORK ATM
	 * @tparam UserClass 
	 * @param AxisName 
	 * @param EventType 
	 * @param Func 
	 */
	template<class UserClass>
	void BindAxisToState(FName AxisName, FInputActionHandlerSignature::TMethodPtr<UserClass> Func);
	//TODO: Do that the behavior for when you call this function when InputComponent is null is correct

	/**
	 * @brief Binds an Action to a state which gets cleared when exiting state. If InputComponent is null it wont go through
	 * //DOESNT WORK ATM
	 * @tparam UserClass 
	 * @param AxisName 
	 * @param EventType 
	 * @param Func 
	 */
	template<class UserClass>
	void BindActionToState(FName ActionName, EInputEvent EventType, FInputActionHandlerSignature::TMethodPtr<UserClass> Func);
	//TODO: Do that the behavior for when you call this function when InputComponent is null is correct
	
	
	/**
	 * @brief Remembers axis, clears when EmptyAxisBindings is called.
	 * //ATTENTION: Remember to call EmptyAxisBindings when leaving the state
	 * @param FInputAxisBinding 
	 */
	void inline AddAxisBinding(const FInputAxisBinding Item);

	/**
	 * @brief Remembers actions, clears when EmptyActionBindings is called.
	 * //ATTENTION: remember to call EmptyAxisBindings when leaving the state
	 * @param FInputActionBinding
	 */
	void inline AddActionBinding(const FInputActionBinding Item);
	
	/**
	 * @brief Unbinds the remembered Axis' from given InputComponent while leaving all the other bound axis' untouched
	 * //Call this when exiting a state
	 * @param InputComponent
	 */
	void EmptyAxisBindings(UInputComponent& InputComp);

	/**
	 * @brief Unbinds the remembered Action' from given InputComponent while leaving all the other bound actions' untouched
	 * //Call this when exiting a state
	 * @param InputComponent
	 */
	void EmptyActionBindings(UInputComponent& InputComp);
	
	/**
	 * @brief Empty both axis and action bindings
	 * @param InputComponent 
	 */
	void EmptyBindings(UInputComponent& InputComponent);
	
	/**
	 * @brief Compares two Axis bindings if they're the same with some gethandle magic
	 * @param Left hand side
	 * @param Right hand side
	 * @return If they are the same
	 */
	bool CompareInputAxisBindings(const FInputAxisBinding lhs, const FInputAxisBinding rhs);

	/**
	 * @brief Compares two Action bindings if they are the same
	 * @param lhs 
	 * @param rhs 
	 * @return If they are the same
	 */
	bool CompareInputActionBindings(const FInputActionBinding lhs, const FInputActionBinding rhs);

public: //Public Variables

private: //Private Functions
};






