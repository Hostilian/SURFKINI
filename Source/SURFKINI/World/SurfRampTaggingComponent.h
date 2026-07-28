// Copyright 2026 SURFKINI Team. Open-Source Licensed.
// Source: momentum-mod/game, src/public/surf_ramp.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurfRampTaggingComponent.generated.h"

/**
 * USurfRampTaggingComponent
 * Tagging component attached to level geometry exposing surface slope angle and surfability status.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURFKINI_API USurfRampTaggingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USurfRampTaggingComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surf Ramp")
	float MaxSurfableAngle = 75.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surf Ramp")
	float MinSurfableAngle = 40.0f;

	UFUNCTION(BlueprintPure, Category = "Surf Ramp")
	bool IsSurfaceSurfable(const FVector& SurfaceNormal) const;
};
