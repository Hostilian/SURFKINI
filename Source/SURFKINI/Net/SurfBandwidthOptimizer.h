#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfBandwidthOptimizer.generated.h"

UCLASS()
class SURFKINI_API USurfBandwidthOptimizer : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Net")
	static FVector QuantizeVector(const FVector& InVector, float Precision = 0.01f);
};
