// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SurfDedicatedServer.generated.h"

/**
 * FSurfServerBrowserEntry
 * Metadata structure for public server browser listing.
 */
USTRUCT(BlueprintType)
struct FSurfServerBrowserEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server Browser")
	FString ServerName = "SURFKINI Dedicated Arena";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server Browser")
	FString MapName = "surf_ramp_test";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server Browser")
	int32 CurrentPlayers = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server Browser")
	int32 MaxPlayers = 16;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server Browser")
	int32 PingMs = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server Browser")
	int32 TickRate = 128;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server Browser")
	FString GameModeTag = "Surf/Parkour";
};

/**
 * USurfDedicatedServer
 * Dedicated server manager supporting 64/128 tick rate loops and server browser metadata.
 */
UCLASS(BlueprintType)
class SURFKINI_API USurfDedicatedServer : public UObject
{
	GENERATED_BODY()

public:
	USurfDedicatedServer();

	UFUNCTION(BlueprintCallable, Category = "Dedicated Server")
	void InitializeServer(int32 InTargetTickRate = 128, FString InServerName = "SURFKINI Official");

	UFUNCTION(BlueprintPure, Category = "Dedicated Server")
	int32 GetTargetTickRate() const { return TargetTickRate; }

	UFUNCTION(BlueprintPure, Category = "Dedicated Server")
	FSurfServerBrowserEntry GetServerMetadata() const;

private:
	int32 TargetTickRate = 128;
	FString ServerName = "SURFKINI Dedicated Arena";
	FString ActiveMap = "surf_ramp_test";
	int32 ConnectedPlayers = 1;
};
