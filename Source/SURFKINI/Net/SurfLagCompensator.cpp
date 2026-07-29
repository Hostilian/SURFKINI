#include "Net/SurfLagCompensator.h"

FVector USurfLagCompensator::GetRewoundPosition(FVector CurrentPos, FVector PrevPos, float LerpAlpha)
{
	return FMath::Lerp(PrevPos, CurrentPos, FMath::Clamp(LerpAlpha, 0.0f, 1.0f));
}
