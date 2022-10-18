#pragma once

#include "HAL/PlatformMath.h"

struct FMyMath : public FPlatformMath
{
	//Alfons's personal little math library

	/**
	 * @brief Basically Unity's movetowards
	 * @param Current 
	 * @param Target 
	 * @param MaxDistanceDelta 
	 * @return 
	 */
	static FVector MoveTowards(const FVector Current, const FVector Target, const float MaxDistanceDelta);

	/**
	 * @brief Returns the same vector but Z is 0.
	 * @param Target 
	 * @return 
	 */
	static FVector ZeroZVector(FVector Target);
	
	/**
	 * @brief Returns a normalized vector with its Z being 0.
	 * @param Target 
	 * @return 
	 */
	static FVector ZeroZNormalizedVector(FVector Target);
};
