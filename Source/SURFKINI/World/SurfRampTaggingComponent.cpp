// Copyright 2026 SURFKINI Team. Open-Source Licensed.
// Source: momentum-mod/game, src/public/surf_ramp.cpp

#include "World/SurfRampTaggingComponent.h"

USurfRampTaggingComponent::USurfRampTaggingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool USurfRampTaggingComponent::IsSurfaceSurfable(const FVector& SurfaceNormal) const
{
	// Calculate slope angle from Z-up normal
	float DotZ = FMath::Clamp(SurfaceNormal.Z, -1.0f, 1.0f);
	float SlopeAngleDegrees = FMath::RadiansToDegrees(FMath::Acos(DotZ));

	return (SlopeAngleDegrees >= MinSurfableAngle && SlopeAngleDegrees <= MaxSurfableAngle);
}
