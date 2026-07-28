// SURFKINI — Camera Velocity Tilt & Post-Process Component Implementation
// Reference: Valve Source SDK 2013 in_camera.cpp

#include "Graphics/SurfPostProcessComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

USurfPostProcessComponent::USurfPostProcessComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USurfPostProcessComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float USurfPostProcessComponent::CalculateCameraRoll(const FVector& Velocity, const FVector& RightVector) const
{
	// Calculate lateral velocity projection onto player right vector
	const float DotRight = FVector::DotProduct(Velocity, RightVector);
	const float RawRoll = DotRight * RollSensitivity;
	return FMath::Clamp(RawRoll, -MaxCameraRollDegrees, MaxCameraRollDegrees);
}

float USurfPostProcessComponent::CalculateDynamicFOV(float BaseFOV, const FVector& Velocity) const
{
	const float Speed = Velocity.Size();
	const float SpeedRatio = FMath::Clamp(Speed / FOVSpeedThreshold, 0.0f, 1.0f);
	return BaseFOV + (SpeedRatio * MaxFOVAdd);
}
