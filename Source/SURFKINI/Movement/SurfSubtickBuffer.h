#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfSubtickBuffer.generated.h"

UCLASS()
class SURFKINI_API USurfSubtickBuffer : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Movement")
	static bool IsBufferedJumpValid(int32 LastJumpMs, int32 LastGroundedMs, int32 CurrentTimeMs);
};
