// Source: Valve Source Engine SDK (Clean-Room Port for SURFKINI UE5.8)
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfPhysicsSolver.generated.h"

UCLASS()
class SURFKINI_API USurfPhysicsSolver : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Physics")
	static FVector ClipVelocity(const FVector& InVelocity, const FVector& Normal, float Overbounce = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Physics")
	static FVector AirAccelerate(const FVector& InVelocity, const FVector& WishDir, float WishSpeed, float Accel, float DeltaTime);
};
