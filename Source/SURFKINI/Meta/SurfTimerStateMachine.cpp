// Copyright 2026 SURFKINI Team. Open-Source Licensed.
// Source: SurfTimer/CSGO-SurfTimer, plugins/surftimer.cpp

#include "Meta/SurfTimerStateMachine.h"

USurfTimerStateMachine::USurfTimerStateMachine()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USurfTimerStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentState == ESurfTimerState::Running)
	{
		ElapsedTime += DeltaTime;
		bool bIsPB = (ElapsedTime < PersonalBestTime);
		OnTimerUpdated.Broadcast(ElapsedTime, ActiveStage, bIsPB);
	}
}

void USurfTimerStateMachine::StartTimer()
{
	ElapsedTime = 0.0f;
	ActiveStage = 1;
	CurrentState = ESurfTimerState::Running;
}

void USurfTimerStateMachine::ReachStage(int32 StageIndex)
{
	if (CurrentState == ESurfTimerState::Running)
	{
		ActiveStage = StageIndex;
	}
}

void USurfTimerStateMachine::FinishTimer()
{
	if (CurrentState == ESurfTimerState::Running)
	{
		CurrentState = ESurfTimerState::Finished;
		if (ElapsedTime < PersonalBestTime)
		{
			PersonalBestTime = ElapsedTime;
		}
		OnTimerUpdated.Broadcast(ElapsedTime, ActiveStage, ElapsedTime <= PersonalBestTime);
	}
}
