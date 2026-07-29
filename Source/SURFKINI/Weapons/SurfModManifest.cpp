// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#include "Weapons/SurfModManifest.h"

USurfModSystem::USurfModSystem()
{
}

bool USurfModSystem::ValidateModManifest(const FSurfModManifest& Manifest) const
{
	return !Manifest.ModID.IsEmpty() && !Manifest.ModName.IsEmpty();
}
