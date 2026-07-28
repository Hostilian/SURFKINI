// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SURFKINIGameMode.generated.h"

UCLASS(minimalapi)
class ASURFKINIGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASURFKINIGameMode();

protected:
	virtual void BeginPlay() override;
};
