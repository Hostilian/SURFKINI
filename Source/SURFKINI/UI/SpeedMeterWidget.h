// SURFKINI — Speed Meter Widget Header
// Displays real-time horizontal velocity (ups / u/s), surf state, and acceleration feedback.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Movement/SurfMovementComponent.h"
#include "SpeedMeterWidget.generated.h"

UCLASS()
class SURFKINI_API USpeedMeterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Returns formatted horizontal speed text (e.g., "1250 u/s") */
	UFUNCTION(BlueprintPure, Category = "SURFKINI|UI")
	FText GetFormattedSpeedText() const;

	/** Returns current movement state string ("Grounded", "Airborne", "Surfing") */
	UFUNCTION(BlueprintPure, Category = "SURFKINI|UI")
	FString GetMoveStateString() const;

	/** Returns speed value as float for UI progress bars or gauge meters */
	UFUNCTION(BlueprintPure, Category = "SURFKINI|UI")
	float GetHorizontalSpeed() const;

	/** Returns color-coded linear color for speedometer tiers (Blue < 500, Yellow 500-1500, Green > 1500 u/s) */
	UFUNCTION(BlueprintPure, Category = "SURFKINI|UI")
	FLinearColor GetSpeedTierColor() const;

	/** Target surf movement component reference */
	UPROPERTY(BlueprintReadWrite, Category = "SURFKINI|UI", meta = (ExposeOnSpawn = true))
	USurfMovementComponent* SurfMovement;
};
