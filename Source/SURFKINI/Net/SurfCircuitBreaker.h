#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfCircuitBreaker.generated.h"

UCLASS()
class SURFKINI_API USurfCircuitBreaker : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Net")
	static bool ShouldAllowRpc(int32 Failures, int32 Threshold);
};
