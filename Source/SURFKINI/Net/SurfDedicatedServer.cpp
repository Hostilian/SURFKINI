// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#include "Net/SurfDedicatedServer.h"

USurfDedicatedServer::USurfDedicatedServer()
{
	TargetTickRate = 128;
}

void USurfDedicatedServer::InitializeServer(int32 InTargetTickRate, FString InServerName)
{
	TargetTickRate = (InTargetTickRate == 64 || InTargetTickRate == 128) ? InTargetTickRate : 128;
	ServerName = InServerName;
}

FSurfServerBrowserEntry USurfDedicatedServer::GetServerMetadata() const
{
	FSurfServerBrowserEntry Entry;
	Entry.ServerName = ServerName;
	Entry.MapName = ActiveMap;
	Entry.CurrentPlayers = ConnectedPlayers;
	Entry.MaxPlayers = 16;
	Entry.PingMs = 12;
	Entry.TickRate = TargetTickRate;
	Entry.GameModeTag = "Surf/Hybrid";
	return Entry;
}
