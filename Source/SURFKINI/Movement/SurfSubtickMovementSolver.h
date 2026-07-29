#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfSubtickMovementSolver.generated.h"

UCLASS()
class SURFKINI_API USurfSubtickMovementSolver : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Movement")
	static FVector StepPosition(FVector CurrentPos, FVector Velocity, float SubtickDelta);
};
