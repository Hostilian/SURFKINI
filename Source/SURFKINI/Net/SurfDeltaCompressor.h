#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfDeltaCompressor.generated.h"

UCLASS()
class SURFKINI_API USurfDeltaCompressor : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Net")
	static int32 CompressXor(int32 BaseVal, int32 NewVal);
};
