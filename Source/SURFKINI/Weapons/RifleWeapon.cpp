// SURFKINI — Hitscan Rifle Weapon Implementation

#include "Weapons/RifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ARifleWeapon::ARifleWeapon()
{
	WeaponName = "Assault Rifle";
	FireMode = EWeaponFireMode::FullAuto;
	BaseDamage = 35.0f;
	ArmorRatio = 0.70f;
	FireRateSeconds = 0.09f; // ~666 RPM
	MaxAmmo = 30;
}

void ARifleWeapon::FireShot()
{
	Super::FireShot();

	APawn* InstigatorPawn = Cast<APawn>(GetOwner());
	if (!InstigatorPawn) return;

	FVector CameraLocation;
	FRotator CameraRotation;
	InstigatorPawn->GetActorEyesViewPoint(CameraLocation, CameraRotation);

	const FVector TraceEnd = CameraLocation + (CameraRotation.Vector() * EffectiveRange);

	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(InstigatorPawn);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		CameraLocation,
		TraceEnd,
		ECC_Visibility,
		QueryParams
	);

	const FVector TargetImpact = bHit ? Hit.ImpactPoint : TraceEnd;

	// Visual feedback
	PlayFireEffects(TargetImpact);

	// Server validation RPC call
	if (InstigatorPawn->IsLocallyControlled())
	{
		ServerFireShot(CameraLocation, CameraRotation.Vector());
	}
}

void ARifleWeapon::PlayFireEffects(const FVector& HitLocation)
{
	#if WITH_EDITOR
	// Debug line draw for hitscan verification in editor
	DrawDebugLine(GetWorld(), GetActorLocation(), HitLocation, FColor::Red, false, 1.0f, 0, 1.5f);
	#endif
}
