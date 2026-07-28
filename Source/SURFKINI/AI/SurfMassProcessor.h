// SURFKINI — Mass Entity Surf Processor Header
// Applies ClipVelocity surf physics to UMassEntity transforms for high-density crowds (500+ NPCs).

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SurfMassProcessor.generated.h"

UCLASS()
class SURFKINI_API USurfMassProcessor : public UObject
{
	GENERATED_BODY()

public:
	USurfMassProcessor();

	/** Updates entity transforms using clean-room ClipVelocity physics */
	void ProcessEntities(float DeltaTime);

protected:
	UPROPERTY(EditAnywhere, Category = "Mass Surf Config")
	float MassAirAccel = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Mass Surf Config")
	float MassOverbounce = 1.001f;
};
