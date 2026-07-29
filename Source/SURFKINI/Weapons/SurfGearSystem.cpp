// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#include "Weapons/SurfGearSystem.h"

USurfGearSystem::USurfGearSystem()
{
}

void USurfGearSystem::EquipGear(FSurfGearItem NewGear)
{
	EquippedGear.Add(NewGear);
}

float USurfGearSystem::GetTotalSpeedMultiplier() const
{
	float Multiplier = 1.0f;
	for (const FSurfGearItem& Item : EquippedGear)
	{
		Multiplier *= Item.SpeedMultiplier;
	}
	return Multiplier;
}

float USurfGearSystem::GetTotalArmorBonus() const
{
	float TotalArmor = 0.0f;
	for (const FSurfGearItem& Item : EquippedGear)
	{
		TotalArmor += Item.ArmorBonus;
	}
	return TotalArmor;
}
