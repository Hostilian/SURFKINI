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

FLinearColor USpeedMeterWidget::GetSpeedTierColor() const
{
	const float Speed = GetHorizontalSpeed();

	if (Speed >= 1500.0f)
	{
		// Tier 3: High speed surf green (#00FF66)
		return FLinearColor(0.0f, 1.0f, 0.4f, 1.0f);
	}
	else if (Speed >= 500.0f)
	{
		// Tier 2: Mid speed yellow (#FFCC00)
		return FLinearColor(1.0f, 0.8f, 0.0f, 1.0f);
	}

	// Tier 1: Low speed cyan/blue (#00CCFF)
	return FLinearColor(0.0f, 0.8f, 1.0f, 1.0f);
}

