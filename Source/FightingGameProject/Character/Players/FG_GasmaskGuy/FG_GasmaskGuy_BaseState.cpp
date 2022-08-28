// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_GasmaskGuy_BaseState.h"

#include "FG_GasmaskGuy.h"

UFG_GasmaskGuy_BaseState::UFG_GasmaskGuy_BaseState()
{
	//Keep an eye on this. This *should* be fine since we have control over how this is constructed,
	//to make sure we get the reference to our outer in time.
	Owner = Cast<AFG_GasmaskGuy>(GetOuter());
}

AFG_GasmaskGuy* UFG_GasmaskGuy_BaseState::GetOwner()
{
	return Owner;
}

UFG_CharacterMovementComponent* UFG_GasmaskGuy_BaseState::GetMoveComp() //doesnt work lol
{
	return MoveCompRef;
}
