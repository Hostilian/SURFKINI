// SURFKINI — HUD Renderer Implementation

#include "UI/SURFKINIHud.h"
#include "Engine/Canvas.h"

ASURFKINIHud::ASURFKINIHud()
{
}

void ASURFKINIHud::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas) return;

	// Center screen crosshairs
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	const float CrosshairSize = 4.0f;

	DrawRect(
		CrosshairColor,
		Center.X - (CrosshairSize * 0.5f),
		Center.Y - (CrosshairSize * 0.5f),
		CrosshairSize,
		CrosshairSize
	);
}
