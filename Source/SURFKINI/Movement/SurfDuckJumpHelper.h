#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfDuckJumpHelper.generated.h"

UCLASS()
class SURFKINI_API USurfDuckJumpHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Movement")
	static float CalculateCrouchHeight(bool bIsCrouching, float CrouchRatio);
};
