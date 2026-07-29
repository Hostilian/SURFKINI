// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SurfModManifest.generated.h"

USTRUCT(BlueprintType)
struct FSurfModManifest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modding")
	FString ModID = "com.surfkini.speedrun";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modding")
	FString ModName = "Classic Speedrun Mutator";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modding")
	FString Author = "Community Developer";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modding")
	FString Version = "1.0.0";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modding")
	float MaxAirSpeedOverride = 40.0f;
};

UCLASS(BlueprintType)
class SURFKINI_API USurfModSystem : public UObject
{
	GENERATED_BODY()

public:
	USurfModSystem();

	UFUNCTION(BlueprintCallable, Category = "Modding")
	bool ValidateModManifest(const FSurfModManifest& Manifest) const;
};
