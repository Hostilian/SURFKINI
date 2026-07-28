// SURFKINI — Surf Ramp Test Map Level Script Actor Header
// Procedural CS-style surf ramp geometry builder for physics verification.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SurfRampTestMap.generated.h"

UCLASS()
class SURFKINI_API ASurfRampTestMap : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ASurfRampTestMap();

	virtual void BeginPlay() override;

protected:
	/** Generates static mesh surf ramp at target transform */
	void SpawnSurfRamp(FVector Location, FRotator Rotation, FVector Scale);
};
