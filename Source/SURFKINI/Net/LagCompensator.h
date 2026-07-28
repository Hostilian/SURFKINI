// SURFKINI — Lag Compensation Hitbox Rewind System Header

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LagCompensator.generated.h"

USTRUCT()
struct FHitboxHistoryFrame
{
	GENERATED_BODY()

	float Timestamp = 0.0f;
	FVector Location = FVector::ZeroVector;
	FRotator Rotation = FRotator::ZeroRotator;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURFKINI_API ULagCompensator : public UActorComponent
{
	GENERATED_BODY()

public:
	ULagCompensator();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Rewinds actor hitboxes to a past timestamp for server hit validation */
	void RewindActor(AActor* TargetActor, float TargetTimestamp);

	/** Restores actor hitboxes to current server position */
	void RestoreActor(AActor* TargetActor);

private:
	// Ring buffer of historical positions (1000ms window)
	TArray<FHitboxHistoryFrame> HistoryBuffer;
	static constexpr int32 MaxHistoryFrames = 64;
};
