#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfStrafesCalculator.generated.h"

UCLASS()
class SURFKINI_API USurfStrafesCalculator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Movement")
	static float CalculateStrafeSync(const FVector& Velocity, const FVector& WishDir, float DeltaYaw);
};
