// SURFKINI — Hitscan Rifle Weapon Header

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "RifleWeapon.generated.h"

UCLASS()
class SURFKINI_API ARifleWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:
	ARifleWeapon();

protected:
	virtual void FireShot() override;

	/** Spawns immediate tracer line and impact particle effect */
	void PlayFireEffects(const FVector& HitLocation);
};
