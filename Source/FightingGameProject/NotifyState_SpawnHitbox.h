// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_SpawnHitbox.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTINGGAMEPROJECT_API UNotifyState_SpawnHitbox : public UAnimNotifyState
{
	GENERATED_BODY()
public:

	UNotifyState_SpawnHitbox();
	
	UPROPERTY()
	AActor* HitboxActor;

	UPROPERTY(EditAnywhere)
	UClass* HitboxActorRef;
	
private:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
