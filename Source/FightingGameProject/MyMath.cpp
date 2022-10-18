#include "MyMath.h"

FVector FMyMath::MoveTowards(const FVector Current, const FVector Target, const float MaxDistanceDelta)
{
	FVector a = Target - Current;
	const float magnitude = a.Length();
	if (magnitude <= MaxDistanceDelta || magnitude == 0.f)
	{
		return Target;
	}
	return Current + a / magnitude * MaxDistanceDelta;
}

FVector FMyMath::ZeroZVector(FVector Target)
{
	Target.Z = 0;
	return Target;
}

FVector FMyMath::ZeroZNormalizedVector(FVector Target)
{
	Target.Z = 0;
	Target.Normalize();
	return Target;
}
