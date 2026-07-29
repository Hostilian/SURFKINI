#include "Movement/SurfDuckJumpHelper.h"

float USurfDuckJumpHelper::CalculateCrouchHeight(bool bIsCrouching, float CrouchRatio)
{
	float StandH = 1.8f;
	float CrouchH = 1.2f;
	return FMath::Lerp(StandH, CrouchH, FMath::Clamp(CrouchRatio, 0.0f, 1.0f));
}
