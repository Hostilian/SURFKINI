#include "Net/SurfDeltaCompressor.h"

int32 USurfDeltaCompressor::CompressXor(int32 BaseVal, int32 NewVal)
{
	return BaseVal ^ NewVal;
}
