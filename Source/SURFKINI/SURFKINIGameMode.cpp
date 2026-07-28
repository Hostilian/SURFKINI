// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#include "SURFKINIGameMode.h"
#include "SURFKINICharacter.h"
#include "Levels/SurfTestMapBuilder.h"
#include "Kismet/GameplayStatics.h"

ASURFKINIGameMode::ASURFKINIGameMode()
{
	DefaultPawnClass = ASURFKINICharacter::StaticClass();
}

void ASURFKINIGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		// Spawn procedural 45-degree surf ramps if no map builder actor exists
		AActor* ExistingBuilder = UGameplayStatics::GetActorOfClass(World, ASurfTestMapBuilder::StaticClass());
		if (!ExistingBuilder)
		{
			World->SpawnActor<ASurfTestMapBuilder>(ASurfTestMapBuilder::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator);
		}
	}
}
