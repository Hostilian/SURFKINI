// Source: Valve Source Engine SDK (Clean-Room Port for SURFKINI UE5.8)
#include "Movement/SurfPhysicsSolver.h"

FVector USurfPhysicsSolver::ClipVelocity(const FVector& InVelocity, const FVector& Normal, float Overbounce)
{
	float Backoff = FVector::DotProduct(InVelocity, Normal);
	if (Backoff < 0.0f)
	{
		Backoff *= Overbounce;
	}
	else
	{
		Backoff /= Overbounce;
	}

	FVector OutVelocity = InVelocity - (Normal * Backoff);
	return OutVelocity;
}

FVector USurfPhysicsSolver::AirAccelerate(const FVector& InVelocity, const FVector& WishDir, float WishSpeed, float Accel, float DeltaTime)
{
	float WishSpd = FMath::Min(WishSpeed, 30.0f);
	float CurrentSpd = FVector::DotProduct(InVelocity, WishDir);
	float AddSpeed = WishSpd - CurrentSpd;

	if (AddSpeed <= 0.0f)
	{
		return InVelocity;
	}

	float AccelSpeed = Accel * WishSpeed * DeltaTime;
	AccelSpeed = FMath::Min(AccelSpeed, AddSpeed);

	return InVelocity + (WishDir * AccelSpeed);
}
