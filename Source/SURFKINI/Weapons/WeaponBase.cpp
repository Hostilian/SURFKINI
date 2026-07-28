// SURFKINI — Base Weapon Actor Implementation

#include "Weapons/WeaponBase.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "Engine/World.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MaxAmmo;
}

void AWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWeaponBase, CurrentAmmo);
}

void AWeaponBase::StartFire()
{
	if (bIsReloading || CurrentAmmo <= 0) return;

	bIsFiring = true;
	FireShot();

	if (FireMode == EWeaponFireMode::FullAuto)
	{
		GetWorldTimerManager().SetTimer(
			FireTimerHandle,
			this,
			&AWeaponBase::FireShot,
			FireRateSeconds,
			true
		);
	}
}

void AWeaponBase::StopFire()
{
	bIsFiring = false;
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void AWeaponBase::Reload()
{
	if (bIsReloading || CurrentAmmo == MaxAmmo) return;

	StopFire();
	bIsReloading = true;

	GetWorldTimerManager().SetTimer(
		ReloadTimerHandle,
		[this]()
		{
			CurrentAmmo = MaxAmmo;
			bIsReloading = false;
		},
		ReloadDurationSeconds,
		false
	);
}

void AWeaponBase::FireShot()
{
	if (CurrentAmmo <= 0)
	{
		StopFire();
		Reload();
		return;
	}

	CurrentAmmo--;

	// Overridden by derived weapons (RifleWeapon, etc.)
}

bool AWeaponBase::ServerFireShot_Validate(FVector MuzzleLocation, FVector FireDirection)
{
	return true;
}

void AWeaponBase::ServerFireShot_Implementation(FVector MuzzleLocation, FVector FireDirection)
{
	// Server-side authoritative hit verification & damage application
}
