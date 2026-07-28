// SURFKINI — Surf Ramp Test Map Level Script Actor Implementation

#include "Levels/SurfRampTestMap.h"
#include "Engine/World.h"
#include "Engine/StaticMeshActor.h"

ASurfRampTestMap::ASurfRampTestMap()
{
}

void ASurfRampTestMap::BeginPlay()
{
	Super::BeginPlay();

	// Spawn initial CS surf test ramps (45° angled ramp wedge at origin)
	SpawnSurfRamp(FVector(0.0f, 0.0f, 100.0f), FRotator(45.0f, 0.0f, 0.0f), FVector(10.0f, 2.0f, 10.0f));
}

void ASurfRampTestMap::SpawnSurfRamp(FVector Location, FRotator Rotation, FVector Scale)
{
	UWorld* World = GetWorld();
	if (!World) return;

	FActorSpawnParameters SpawnParams;
	AStaticMeshActor* RampActor = World->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), Location, Rotation, SpawnParams);
	if (RampActor)
	{
		RampActor->SetActorScale3D(Scale);
	}
}
