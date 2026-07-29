// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurfHUDWidget.generated.h"

UCLASS()
class SURFKINI_API USurfHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USurfHUDWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateSpeedometer(float CurrentSpeed);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateStrafeSync(float SyncPercentage);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateVitals(float Health, float Armor);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateAmmo(int32 CurrentAmmo, int32 ReserveAmmo);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD|Stats")
	float DisplaySpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD|Stats")
	float DisplayStrafeSync = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD|Stats")
	float DisplayHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD|Stats")
	float DisplayArmor = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD|Stats")
	int32 DisplayAmmo = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD|Stats")
	int32 DisplayReserveAmmo = 90;
};
