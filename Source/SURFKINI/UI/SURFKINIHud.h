// SURFKINI — HUD Renderer Header

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SURFKINIHud.generated.h"

UCLASS()
class SURFKINI_API ASURFKINIHud : public AHUD
{
	GENERATED_BODY()

public:
	ASURFKINIHud();

	virtual void DrawHUD() override;

protected:
	/** Crosshair texture */
	UPROPERTY(EditDefaultsOnly, Category = "HUD Config")
	class UTexture2D* CrosshairTexture;

	UPROPERTY(EditDefaultsOnly, Category = "HUD Config")
	FLinearColor CrosshairColor = FLinearColor::Green;
};
