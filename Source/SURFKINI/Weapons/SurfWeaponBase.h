#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurfWeaponBase.generated.h"

UCLASS(Abstract)
class SURFKINI_API ASurfWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASurfWeaponBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SURFKINI|Weapon")
	FString WeaponName = TEXT("Kinetic Rifle");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SURFKINI|Weapon")
	float BaseDamage = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SURFKINI|Weapon")
	int32 MaxAmmo = 30;

	UPROPERTY(BlueprintReadOnly, Category = "SURFKINI|Weapon")
	int32 CurrentAmmo = 30;

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Weapon")
	virtual bool CanFire() const;

	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Weapon")
	virtual bool FireWeapon(const FVector& MuzzleLocation, const FVector& Direction);
};
