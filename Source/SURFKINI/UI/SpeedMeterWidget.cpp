// SURFKINI — Speed Meter Widget Implementation

#include "UI/SpeedMeterWidget.h"

FText USpeedMeterWidget::GetFormattedSpeedText() const
{
	const float Speed = GetHorizontalSpeed();
	return FText::FromString(FString::Printf(TEXT("%.0f u/s"), Speed));
}

float USpeedMeterWidget::GetHorizontalSpeed() const
{
	if (SurfMovement)
	{
		return SurfMovement->GetHorizontalSpeed();
	}
	return 0.0f;
}

FString USpeedMeterWidget::GetMoveStateString() const
{
	if (!SurfMovement) return TEXT("Offline");

	switch (SurfMovement->GetMoveState())
	{
	case ESurfMoveState::Grounded: return TEXT("Grounded");
	case ESurfMoveState::Airborne: return TEXT("Airborne");
	case ESurfMoveState::Surfing:  return TEXT("Surfing");
	case ESurfMoveState::Noclip:   return TEXT("Noclip");
	default:                       return TEXT("Unknown");
	}
}
