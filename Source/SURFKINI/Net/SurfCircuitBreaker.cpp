#include "Net/SurfCircuitBreaker.h"

bool USurfCircuitBreaker::ShouldAllowRpc(int32 Failures, int32 Threshold)
{
	return Failures < Threshold;
}
