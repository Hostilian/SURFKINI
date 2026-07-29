#include "Weapons/SurfWeaponBase.h"

ASurfWeaponBase::ASurfWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	CurrentAmmo = MaxAmmo;
}

bool ASurfWeaponBase::CanFire() const
{
	return CurrentAmmo > 0;
}

bool ASurfWeaponBase::FireWeapon(const FVector& MuzzleLocation, const FVector& Direction)
{
	if (!CanFire())
	{
		return false;
	}

	CurrentAmmo--;
	return true;
}
