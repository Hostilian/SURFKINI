#include "Net/SurfBandwidthOptimizer.h"

FVector USurfBandwidthOptimizer::QuantizeVector(const FVector& InVector, float Precision)
{
	return FVector(
		FMath::GridSnap(InVector.X, Precision),
		FMath::GridSnap(InVector.Y, Precision),
		FMath::GridSnap(InVector.Z, Precision)
	);
}
