// SURFKINI — Surf Wind Shear & Audio Modulation Implementation
// Reference: Valve Source SDK 2013 soundpanning.cpp

#include "Audio/SurfAudioComponent.h"
#include "Math/UnrealMathUtility.h"

USurfAudioComponent::USurfAudioComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USurfAudioComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float USurfAudioComponent::CalculateWindVolume(const FVector& Velocity) const
{
	const float Speed = Velocity.Size();
	return FMath::Clamp(Speed / MaxWindSpeed, 0.0f, 1.0f);
}

float USurfAudioComponent::CalculateWindPitch(const FVector& Velocity) const
{
	const float Speed = Velocity.Size();
	const float Ratio = FMath::Clamp(Speed / MaxWindSpeed, 0.0f, 1.0f);
	return BasePitch + (Ratio * MaxPitchAdd);
}
