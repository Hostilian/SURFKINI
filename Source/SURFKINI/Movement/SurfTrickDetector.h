#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfTrickDetector.generated.h"

UCLASS()
class SURFKINI_API USurfTrickDetector : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Movement")
	static bool Detect360Spin(float AccumulatedYawDeg);
};
