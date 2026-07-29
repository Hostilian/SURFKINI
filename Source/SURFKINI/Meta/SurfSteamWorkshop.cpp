// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#include "Meta/SurfSteamWorkshop.h"

USurfSteamWorkshop::USurfSteamWorkshop()
{
}

bool USurfSteamWorkshop::PublishMapToWorkshop(FString MapFilePath, FString Title, FString Description)
{
	// Steamworks ISteamUGC API integration point
	return !MapFilePath.IsEmpty() && !Title.IsEmpty();
}

bool USurfSteamWorkshop::DownloadWorkshopMap(uint64 WorkshopFileId)
{
	// Steamworks DownloadItem integration point
	return WorkshopFileId > 0;
}
