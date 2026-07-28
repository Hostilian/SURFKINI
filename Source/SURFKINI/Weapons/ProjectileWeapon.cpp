// SURFKINI — Physics Projectile Weapon Implementation

#include "Weapons/ProjectileWeapon.h"
#include "Engine/World.h"

AProjectileWeapon::AProjectileWeapon()
{
	WeaponName = "Plasma Launcher";
	FireMode = EWeaponFireMode::SemiAuto;
	BaseDamage = 60.0f;
	ArmorRatio = 0.80f;
	FireRateSeconds = 0.40f;
	MaxAmmo = 10;
}

void AProjectileWeapon::FireShot()
{
	Super::FireShot();

	APawn* InstigatorPawn = Cast<APawn>(GetOwner());
	if (!InstigatorPawn) return;

	FVector CameraLocation;
	FRotator CameraRotation;
	InstigatorPawn->GetActorEyesViewPoint(CameraLocation, CameraRotation);

	if (InstigatorPawn->IsLocallyControlled())
	{
		ServerFireShot(CameraLocation, CameraRotation.Vector());
	}
}
