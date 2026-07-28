// SURFKINI — Game Mode Implementation

#include "SURFKINIGameMode.h"
#include "SURFKINICharacter.h"
#include "UObject/ConstructorHelpers.h"

ASURFKINIGameMode::ASURFKINIGameMode()
{
	// Set default pawn to our custom surf character
	DefaultPawnClass = ASURFKINICharacter::StaticClass();
}
