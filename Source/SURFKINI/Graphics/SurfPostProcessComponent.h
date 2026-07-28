// SURFKINI — Camera Velocity Tilt & Post-Process Component
// Adapted from Valve Source SDK 2013 in_camera.cpp & UE5 Camera System.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurfPostProcessComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURFKINI_API USurfPostProcessComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USurfPostProcessComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Calculates camera roll tilt based on lateral velocity vector */
	UFUNCTION(BlueprintPure, Category = "SurfGraphics")
	float CalculateCameraRoll(const FVector& Velocity, const FVector& RightVector) const;

	/** Calculates dynamic FOV multiplier based on velocity magnitude */
	UFUNCTION(BlueprintPure, Category = "SurfGraphics")
	float CalculateDynamicFOV(float BaseFOV, const FVector& Velocity) const;

protected:
	UPROPERTY(EditAnywhere, Category = "SurfGraphics")
	float MaxCameraRollDegrees = 5.0f;

	UPROPERTY(EditAnywhere, Category = "SurfGraphics")
	float RollSensitivity = 0.003f;

	UPROPERTY(EditAnywhere, Category = "SurfGraphics")
	float MaxFOVAdd = 20.0f;

	UPROPERTY(EditAnywhere, Category = "SurfGraphics")
	float FOVSpeedThreshold = 3500.0f;
};
