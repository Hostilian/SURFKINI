#include "Net/SurfInputCompressor.h"

uint8 USurfInputCompressor::PackMoveFlags(bool bForward, bool bBack, bool bLeft, bool bRight, bool bJump, bool bCrouch)
{
	uint8 Flags = 0;
	if (bForward) Flags |= (1 << 0);
	if (bBack)    Flags |= (1 << 1);
	if (bLeft)    Flags |= (1 << 2);
	if (bRight)   Flags |= (1 << 3);
	if (bJump)    Flags |= (1 << 4);
	if (bCrouch)  Flags |= (1 << 5);
	return Flags;
}
