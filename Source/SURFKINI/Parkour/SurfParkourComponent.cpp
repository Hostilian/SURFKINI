// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#include "Parkour/SurfParkourComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"

USurfParkourComponent::USurfParkourComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	ParkourState = ESurfParkourState::None;
}

void USurfParkourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool USurfParkourComponent::DetectWallRun(const FVector& Velocity, FVector& OutWallNormal)
{
	AActor* Owner = GetOwner();
	if (!Owner || !GetWorld()) return false;

	FVector RightVector = Owner->GetActorRightVector();
	FVector Start = Owner->GetActorLocation();
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);

	// Check right wall
	bool bHitRight = GetWorld()->LineTraceSingleByChannel(Hit, Start, Start + (RightVector * WallRunCheckDistance), ECC_WorldStatic, QueryParams);
	if (bHitRight && Hit.ImpactNormal.Z < 0.3f)
	{
		OutWallNormal = Hit.ImpactNormal;
		ParkourState = ESurfParkourState::WallRunning;
		return true;
	}

	// Check left wall
	bool bHitLeft = GetWorld()->LineTraceSingleByChannel(Hit, Start, Start - (RightVector * WallRunCheckDistance), ECC_WorldStatic, QueryParams);
	if (bHitLeft && Hit.ImpactNormal.Z < 0.3f)
	{
		OutWallNormal = Hit.ImpactNormal;
		ParkourState = ESurfParkourState::WallRunning;
		return true;
	}

	ParkourState = ESurfParkourState::None;
	return false;
}

bool USurfParkourComponent::DetectVaultOrMantle(FVector& OutTargetLocation)
{
	AActor* Owner = GetOwner();
	if (!Owner || !GetWorld()) return false;

	FVector ForwardVector = Owner->GetActorForwardVector();
	FVector Start = Owner->GetActorLocation();
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);

	bool bHitWall = GetWorld()->LineTraceSingleByChannel(Hit, Start, Start + (ForwardVector * 80.0f), ECC_WorldStatic, QueryParams);
	if (bHitWall)
	{
		FVector HighStart = Start + FVector(0, 0, MaxMantleHeight) + (ForwardVector * 40.0f);
		FVector DownTrace = HighStart - FVector(0, 0, MaxMantleHeight);
		FHitResult DownHit;

		if (GetWorld()->LineTraceSingleByChannel(DownHit, HighStart, DownTrace, ECC_WorldStatic, QueryParams))
		{
			OutTargetLocation = DownHit.ImpactPoint;
			ParkourState = ESurfParkourState::Mantling;
			return true;
		}
	}

	return false;
}
