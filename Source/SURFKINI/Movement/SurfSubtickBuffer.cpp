#include "Movement/SurfSubtickBuffer.h"

bool USurfSubtickBuffer::IsBufferedJumpValid(int32 LastJumpMs, int32 LastGroundedMs, int32 CurrentTimeMs)
{
	bool bBufferValid = (CurrentTimeMs - LastJumpMs) <= 80;
	bool bCoyoteValid = (CurrentTimeMs - LastGroundedMs) <= 100;
	return bBufferValid && bCoyoteValid;
}
