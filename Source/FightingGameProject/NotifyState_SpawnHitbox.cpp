// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState_SpawnHitbox.h"

UNotifyState_SpawnHitbox::UNotifyState_SpawnHitbox()
{
	bShouldFireInEditor = false;
}

void UNotifyState_SpawnHitbox::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	FTransform CreatorTransform = MeshComp->GetOwner()->GetTransform();
	HitboxActor = MeshComp->GetWorld()->SpawnActor(HitboxActorRef, &CreatorTransform);
	
}

void UNotifyState_SpawnHitbox::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	HitboxActor->Destroy();
}
