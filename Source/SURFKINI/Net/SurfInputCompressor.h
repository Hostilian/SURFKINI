#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfInputCompressor.generated.h"

UCLASS()
class SURFKINI_API USurfInputCompressor : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Net")
	static uint8 PackMoveFlags(bool bForward, bool bBack, bool bLeft, bool bRight, bool bJump, bool bCrouch);
};
