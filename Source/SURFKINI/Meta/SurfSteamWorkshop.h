// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SurfSteamWorkshop.generated.h"

UCLASS(BlueprintType)
class SURFKINI_API USurfSteamWorkshop : public UObject
{
	GENERATED_BODY()

public:
	USurfSteamWorkshop();

	UFUNCTION(BlueprintCallable, Category = "Steam Workshop")
	bool PublishMapToWorkshop(FString MapFilePath, FString Title, FString Description);

	UFUNCTION(BlueprintCallable, Category = "Steam Workshop")
	bool DownloadWorkshopMap(int64 WorkshopFileId);
};
