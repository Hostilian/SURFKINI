// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#include "Levels/SurfTestMapBuilder.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"

ASurfTestMapBuilder::ASurfTestMapBuilder()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	CubeMesh = nullptr;
}

void ASurfTestMapBuilder::BeginPlay()
{
	Super::BeginPlay();

	// Safely load Engine Cube Mesh at runtime without ConstructorHelpers assertion crash
	if (!CubeMesh)
	{
		CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
	}

	ConstructEnvironmentLighting();
	ConstructSpawnPlatform();
	ConstructSurfRamps();
}

void ASurfTestMapBuilder::ConstructEnvironmentLighting()
{
	UWorld* World = GetWorld();
	if (!World) return;

	// Spawn Directional Sun Light
	ADirectionalLight* SunLight = World->SpawnActor<ADirectionalLight>(FVector(0.0f, 0.0f, 1000.0f), FRotator(-45.0f, -45.0f, 0.0f));
	if (SunLight && SunLight->GetLightComponent())
	{
		SunLight->GetLightComponent()->SetIntensity(3.5f);
		SunLight->GetLightComponent()->SetLightColor(FLinearColor(1.0f, 0.95f, 0.85f));
		SunLight->GetLightComponent()->SetCastShadows(true);
	}

	// Spawn Ambient Sky Light
	ASkyLight* SkyLight = World->SpawnActor<ASkyLight>(FVector(0.0f, 0.0f, 1200.0f), FRotator::ZeroRotator);
	if (SkyLight && SkyLight->GetLightComponent())
	{
		SkyLight->GetLightComponent()->SetIntensity(1.0f);
		SkyLight->GetLightComponent()->SetLightColor(FLinearColor(0.6f, 0.8f, 1.0f));
	}

}

void ASurfTestMapBuilder::ConstructSpawnPlatform()
{
	UWorld* World = GetWorld();
	if (!World || !CubeMesh) return;

	// Spawn Platform (Elevated Start Area)
	UStaticMeshComponent* SpawnComp = NewObject<UStaticMeshComponent>(this, TEXT("SpawnPlatformComp"));
	if (SpawnComp)
	{
		SpawnComp->RegisterComponent();
		SpawnComp->SetStaticMesh(CubeMesh);
		SpawnComp->SetWorldLocationAndRotation(GetActorLocation() + FVector(0.0f, -500.0f, 300.0f), FRotator::ZeroRotator);
		SpawnComp->SetWorldScale3D(FVector(15.0f, 15.0f, 0.5f)); // 1500x1500x50 platform
		SpawnComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ASurfTestMapBuilder::ConstructSurfRamps()
{
	UWorld* World = GetWorld();
	if (!World || !CubeMesh) return;

	for (int32 i = 0; i < RampCount; ++i)
	{
		FString MeshName = FString::Printf(TEXT("ProceduralRamp_%d"), i);
		UStaticMeshComponent* RampComp = NewObject<UStaticMeshComponent>(this, *MeshName);
		if (RampComp)
		{
			RampComp->RegisterComponent();
			RampComp->SetStaticMesh(CubeMesh);

			// Position ramps sequentially along Y-axis with alternating 45-degree roll angle
			float OffsetY = i * (RampLength + 400.0f);
			float RollAngle = (i % 2 == 0) ? RampSlopeAngle : -RampSlopeAngle;
			float PosX = (i % 2 == 0) ? 200.0f : -200.0f;

			FVector Location = GetActorLocation() + FVector(PosX, OffsetY + 1000.0f, -i * 300.0f);
			FRotator Rotation = FRotator(0.0f, 0.0f, RollAngle);
			FVector Scale = FVector(RampLength / 100.0f, 6.0f, 0.2f); // Flat wide surf ramp wedge

			RampComp->SetWorldLocationAndRotation(Location, Rotation);
			RampComp->SetWorldScale3D(Scale);
			RampComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}
