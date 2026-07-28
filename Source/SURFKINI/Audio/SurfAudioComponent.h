// SURFKINI — Surf Wind Shear & Audio Modulation Component
// Adapted from Valve Source SDK 2013 soundpanning.cpp & UE Audio Engine.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurfAudioComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURFKINI_API USurfAudioComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USurfAudioComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Calculates dynamic wind shear volume based on surf velocity */
	UFUNCTION(BlueprintPure, Category = "SurfAudio")
	float CalculateWindVolume(const FVector& Velocity) const;

	/** Calculates audio pitch shift for high speed wind whistle */
	UFUNCTION(BlueprintPure, Category = "SurfAudio")
	float CalculateWindPitch(const FVector& Velocity) const;

protected:
	UPROPERTY(EditAnywhere, Category = "SurfAudio")
	float MaxWindSpeed = 3000.0f;

	UPROPERTY(EditAnywhere, Category = "SurfAudio")
	float BasePitch = 1.0f;

	UPROPERTY(EditAnywhere, Category = "SurfAudio")
	float MaxPitchAdd = 0.5f;
};
