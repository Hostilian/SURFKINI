// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#include "UI/SurfHUDWidget.h"

USurfHUDWidget::USurfHUDWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DisplaySpeed = 0.0f;
	DisplayStrafeSync = 100.0f;
	DisplayHealth = 100.0f;
	DisplayArmor = 100.0f;
	DisplayAmmo = 30;
	DisplayReserveAmmo = 90;
}

void USurfHUDWidget::UpdateSpeedometer(float CurrentSpeed)
{
	DisplaySpeed = CurrentSpeed;
}

void USurfHUDWidget::UpdateStrafeSync(float SyncPercentage)
{
	DisplayStrafeSync = FMath::Clamp(SyncPercentage, 0.0f, 100.0f);
}

void USurfHUDWidget::UpdateVitals(float Health, float Armor)
{
	DisplayHealth = FMath::Max(0.0f, Health);
	DisplayArmor = FMath::Max(0.0f, Armor);
}

void USurfHUDWidget::UpdateAmmo(int32 CurrentAmmo, int32 ReserveAmmo)
{
	DisplayAmmo = CurrentAmmo;
	DisplayReserveAmmo = ReserveAmmo;
}
