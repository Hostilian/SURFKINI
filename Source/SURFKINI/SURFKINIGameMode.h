// SURFKINI — Game Mode Header
// Sets SURFKINICharacter as the default pawn.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SURFKINIGameMode.generated.h"

/**
 * SURFKINIGameMode
 *
 * Minimal game mode for the surf FPS.
 * Assigns the custom character class as default pawn.
 * Server-authoritative: all physics runs here.
 */
UCLASS(minimalapi)
class ASURFKINIGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASURFKINIGameMode();
};
