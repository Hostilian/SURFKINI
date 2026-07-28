// SURFKINI — Surf Enemy AI Controller Header
// Controls individual meso-agent enemy NPCs riding ramps and strafe-shooting.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SurfEnemyController.generated.h"

UCLASS()
class SURFKINI_API ASurfEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	ASurfEnemyController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTreeAsset;
};
