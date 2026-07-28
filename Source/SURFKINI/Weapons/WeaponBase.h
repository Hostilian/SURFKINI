// SURFKINI — Base Weapon Actor Header
// Abstract foundation for weapons, fire rate, ammo, recoil, and damage logic.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponFireMode : uint8
{
	SemiAuto  UMETA(DisplayName = "Semi-Automatic"),
	FullAuto  UMETA(DisplayName = "Full-Automatic"),
	Burst     UMETA(DisplayName = "Burst-Fire")
};

UCLASS(Abstract)
class SURFKINI_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

	virtual void BeginPlay() override;

	/** Primary fire request */
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Weapon")
	virtual void StartFire();

	/** Primary fire stop */
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Weapon")
	virtual void StopFire();

	/** Reload request */
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Weapon")
	virtual void Reload();

	// ── Accessors ──
	UFUNCTION(BlueprintPure, Category = "SURFKINI|Weapon")
	int32 GetCurrentAmmo() const { return CurrentAmmo; }

	UFUNCTION(BlueprintPure, Category = "SURFKINI|Weapon")
	int32 GetMaxAmmo() const { return MaxAmmo; }

	UFUNCTION(BlueprintPure, Category = "SURFKINI|Weapon")
	bool IsReloading() const { return bIsReloading; }

protected:
	/** Core weapon shot implementation (overridden by Rifle, Shotgun, etc.) */
	virtual void FireShot();

	/** Server RPC for fire validation */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFireShot(FVector MuzzleLocation, FVector FireDirection);

	// ── Weapon Parameters ──
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Config")
	FString WeaponName = "Base Weapon";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Config")
	EWeaponFireMode FireMode = EWeaponFireMode::FullAuto;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Config")
	float BaseDamage = 30.0f; // 30 HP base damage

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Config")
	float ArmorRatio = 0.70f; // CS-style armor penetration (70% damage to health, 30% absorbed by armor)

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Config")
	float FireRateSeconds = 0.10f; // 600 RPM

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Config")
	float EffectiveRange = 10000.0f; // 100 meters

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Config")
	int32 MaxAmmo = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Config")
	float ReloadDurationSeconds = 2.2f;

	// ── Weapon State ──
	UPROPERTY(Replicated, VisibleInstanceOnly, Category = "Weapon State")
	int32 CurrentAmmo = 30;

	bool bIsFiring = false;
	bool bIsReloading = false;
	float LastFireTime = 0.0f;
	FTimerHandle FireTimerHandle;
	FTimerHandle ReloadTimerHandle;
};
