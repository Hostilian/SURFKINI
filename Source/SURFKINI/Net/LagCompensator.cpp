// SURFKINI — Lag Compensation Hitbox Rewind System Implementation

#include "Net/LagCompensator.h"
#include "GameFramework/Actor.h"

ULagCompensator::ULagCompensator()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULagCompensator::BeginPlay()
{
	Super::BeginPlay();
}

void ULagCompensator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Owner = GetOwner();
	if (!Owner) return;

	FHitboxHistoryFrame Frame;
	Frame.Timestamp = GetWorld()->GetTimeSeconds();
	Frame.Location = Owner->GetActorLocation();
	Frame.Rotation = Owner->GetActorRotation();

	HistoryBuffer.Add(Frame);
	if (HistoryBuffer.Num() > MaxHistoryFrames)
	{
		HistoryBuffer.RemoveAt(0);
	}
}

void ULagCompensator::RewindActor(AActor* TargetActor, float TargetTimestamp)
{
	// Interpolate history buffer to find state at TargetTimestamp
}

void ULagCompensator::RestoreActor(AActor* TargetActor)
{
	// Restore to latest frame
}
