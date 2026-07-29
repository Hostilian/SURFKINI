#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfLagCompensator.generated.h"

UCLASS()
class SURFKINI_API USurfLagCompensator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Net")
	static FVector GetRewoundPosition(FVector CurrentPos, FVector PrevPos, float LerpAlpha);
};
