#include "Movement/SurfSubtickMovementSolver.h"

FVector USurfSubtickMovementSolver::StepPosition(FVector CurrentPos, FVector Velocity, float SubtickDelta)
{
	return CurrentPos + (Velocity * SubtickDelta);
}
