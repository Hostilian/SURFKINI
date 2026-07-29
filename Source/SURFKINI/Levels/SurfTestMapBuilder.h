// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "SurfTestMapBuilder.generated.h"

/**
 * ASurfTestMapBuilder
 * Procedurally generates 45-degree surf ramps, spawn platform, sun/sky lighting, and environment geometry at runtime.
 */
UCLASS()
class SURFKINI_API ASurfTestMapBuilder : public AActor
{
	GENERATED_BODY()

public:
	ASurfTestMapBuilder();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Surf Geometry")
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surf Geometry")
	UStaticMesh* CubeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surf Geometry")
	int32 RampCount = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surf Geometry")
	float RampLength = 4000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surf Geometry")
	float RampSlopeAngle = 45.0f;

	void ConstructEnvironmentLighting();
	void ConstructSpawnPlatform();
	void ConstructSurfRamps();
};
