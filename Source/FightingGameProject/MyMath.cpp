#include "MyMath.h"

FVector UMyMath::MoveTowards(const FVector Current, const FVector Target, const float MaxDistanceDelta)
{
	FVector a = Target - Current;
	const float magnitude = a.Length();
	if (magnitude <= MaxDistanceDelta || magnitude == 0.f)
	{
		return Target;
	}
	return Current + a / magnitude * MaxDistanceDelta;
}

FVector UMyMath::ZeroZVector(FVector Target)
{
	Target.Z = 0;
	return Target;
}

FVector UMyMath::ZeroZNormalizedVector(FVector Target)
{
	Target.Z = 0;
	Target.Normalize();
	return Target;
}
