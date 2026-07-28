// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#include "Levels/SurfTestMapBuilder.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

ASurfTestMapBuilder::ASurfTestMapBuilder()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
}

void ASurfTestMapBuilder::BeginPlay()
{
	Super::BeginPlay();
	ConstructSurfRamps();
}

void ASurfTestMapBuilder::ConstructSurfRamps()
{
	UWorld* World = GetWorld();
	if (!World) return;

	// Load Engine Cube Mesh for procedural scaling
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	UStaticMesh* RampMesh = CubeMeshAsset.Succeeded() ? CubeMeshAsset.Object : nullptr;

	if (!RampMesh) return;

	for (int32 i = 0; i < RampCount; ++i)
	{
		FString MeshName = FString::Printf(TEXT("ProceduralRamp_%d"), i);
		UStaticMeshComponent* RampComp = NewObject<UStaticMeshComponent>(this, *MeshName);
		if (RampComp)
		{
			RampComp->RegisterComponent();
			RampComp->SetStaticMesh(RampMesh);

			// Position ramps sequentially along Y-axis with 45-degree roll pitch angle
			float OffsetY = i * (RampLength + 200.0f);
			float RollAngle = (i % 2 == 0) ? RampSlopeAngle : -RampSlopeAngle;

			FVector Location = GetActorLocation() + FVector(0.0f, OffsetY, 0.0f);
			FRotator Rotation = FRotator(0.0f, 0.0f, RollAngle);
			FVector Scale = FVector(RampLength / 100.0f, 4.0f, 0.2f); // Flattened wide surf ramp

			RampComp->SetWorldLocationAndRotation(Location, Rotation);
			RampComp->SetWorldScale3D(Scale);
			RampComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}
