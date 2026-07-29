#include "Movement/SurfStrafesCalculator.h"

float USurfStrafesCalculator::CalculateStrafeSync(const FVector& Velocity, const FVector& WishDir, float DeltaYaw)
{
	float Speed = Velocity.Size();
	if (Speed < 10.0f)
	{
		return 100.0f;
	}

	float Dot = FVector::DotProduct(Velocity.GetSafeNormal(), WishDir);
	bool bCorrectSide = (DeltaYaw > 0.0f && WishDir.Y > 0.0f) || (DeltaYaw < 0.0f && WishDir.Y < 0.0f);

	if (bCorrectSide)
	{
		return FMath::Clamp(Dot * 100.0f, 0.0f, 100.0f);
	}

	return 0.0f;
}
