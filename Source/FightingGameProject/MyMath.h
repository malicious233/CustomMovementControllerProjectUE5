#pragma once

#include "HAL/PlatformMath.h"
#include "MyMath.generated.h"

UCLASS()
class UMyMath : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//Alfons's personal little math library

	/**
	 * @brief Basically Unity's movetowards
	 * @param Current 
	 * @param Target 
	 * @param MaxDistanceDelta 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	static FVector MoveTowards(const FVector Current, const FVector Target, const float MaxDistanceDelta);

	/**
	 * @brief Returns the same vector but Z is 0.
	 * @param Target 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	static FVector ZeroZVector(FVector Target);
	
	/**
	 * @brief Returns a normalized vector with its Z being 0.
	 * @param Target 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	static FVector ZeroZNormalizedVector(FVector Target);
};
