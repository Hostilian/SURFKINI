#include "Net/SurfNetSnapshotBuffer.h"

void USurfNetSnapshotBuffer::RecordSnapshot(int32 Tick, const FVector& Position, const FVector& Velocity)
{
	int32 Index = Tick % BUFFER_SIZE;
	History[Index].Tick = Tick;
	History[Index].Position = Position;
	History[Index].Velocity = Velocity;
}

bool USurfNetSnapshotBuffer::GetSnapshot(int32 Tick, FSurfMoveSnapshot& OutSnapshot) const
{
	int32 Index = Tick % BUFFER_SIZE;
	if (History[Index].Tick == Tick)
	{
		OutSnapshot = History[Index];
		return true;
	}
	return false;
}
