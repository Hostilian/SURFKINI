// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SurfGearSystem.generated.h"

UENUM(BlueprintType)
enum class ESurfGearType : uint8
{
	Movement  UMETA(DisplayName = "Movement Gear"),
	Combat    UMETA(DisplayName = "Combat Gear"),
	Utility   UMETA(DisplayName = "Utility Gear")
};

USTRUCT(BlueprintType)
struct FSurfGearItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	FString ItemName = "Speed Thrusters";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	ESurfGearType GearType = ESurfGearType::Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	float SpeedMultiplier = 1.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	float ArmorBonus = 25.0f;
};

UCLASS(BlueprintType)
class SURFKINI_API USurfGearSystem : public UObject
{
	GENERATED_BODY()

public:
	USurfGearSystem();

	UFUNCTION(BlueprintCallable, Category = "Gear System")
	void EquipGear(FSurfGearItem NewGear);

	UFUNCTION(BlueprintPure, Category = "Gear System")
	float GetTotalSpeedMultiplier() const;

	UFUNCTION(BlueprintPure, Category = "Gear System")
	float GetTotalArmorBonus() const;

private:
	UPROPERTY()
	TArray<FSurfGearItem> EquippedGear;
};
