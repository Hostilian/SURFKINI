// SURFKINI — Physics Projectile Weapon Header

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "ProjectileWeapon.generated.h"

UCLASS()
class SURFKINI_API AProjectileWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:
	AProjectileWeapon();

protected:
	virtual void FireShot() override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Config")
	TSubclassOf<class AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Config")
	float InitialSpeed = 3000.0f;
};
