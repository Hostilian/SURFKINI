// Copyright 2026 SURFKINI Team. Open-Source Licensed.
// Source: SurfTimer/CSGO-SurfTimer, plugins/surftimer.sp

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurfTimerStateMachine.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSurfTimerUpdated, float, ElapsedSeconds, int32, CurrentStage, bool, bIsPersonalBest);

UENUM(BlueprintType)
enum class ESurfTimerState : uint8
{
	Stopped,
	Running,
	Paused,
	Finished
};

/**
 * USurfTimerStateMachine
 * Stage/checkpoint timer state machine for surf courses.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURFKINI_API USurfTimerStateMachine : public UActorComponent
{
	GENERATED_BODY()

public:
	USurfTimerStateMachine();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Surf Timer")
	void StartTimer();

	UFUNCTION(BlueprintCallable, Category = "Surf Timer")
	void ReachStage(int32 StageIndex);

	UFUNCTION(BlueprintCallable, Category = "Surf Timer")
	void FinishTimer();

	UPROPERTY(BlueprintAssignable, Category = "Surf Timer")
	FOnSurfTimerUpdated OnTimerUpdated;

private:
	ESurfTimerState CurrentState = ESurfTimerState::Stopped;
	float ElapsedTime = 0.0f;
	int32 ActiveStage = 0;
	float PersonalBestTime = 999999.0f;
};
