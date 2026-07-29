// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurfParkourComponent.generated.h"

UENUM(BlueprintType)
enum class ESurfParkourState : uint8
{
	None        UMETA(DisplayName = "None"),
	WallRunning UMETA(DisplayName = "Wall Running"),
	Vaulting    UMETA(DisplayName = "Vaulting"),
	Mantling    UMETA(DisplayName = "Mantling")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURFKINI_API USurfParkourComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USurfParkourComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Parkour")
	bool DetectWallRun(const FVector& Velocity, FVector& OutWallNormal);

	UFUNCTION(BlueprintCallable, Category = "Parkour")
	bool DetectVaultOrMantle(FVector& OutTargetLocation);

	UFUNCTION(BlueprintPure, Category = "Parkour")
	ESurfParkourState GetParkourState() const { return ParkourState; }

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Parkour|Debug")
	ESurfParkourState ParkourState = ESurfParkourState::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parkour|Tuning")
	float WallRunCheckDistance = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parkour|Tuning")
	float MaxMantleHeight = 120.0f;
};
