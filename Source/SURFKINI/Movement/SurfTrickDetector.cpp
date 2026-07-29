#include "Movement/SurfTrickDetector.h"

bool USurfTrickDetector::Detect360Spin(float AccumulatedYawDeg)
{
	return FMath::Abs(AccumulatedYawDeg) >= 360.0f;
}
