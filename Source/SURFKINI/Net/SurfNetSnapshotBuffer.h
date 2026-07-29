#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SurfNetSnapshotBuffer.generated.h"

USTRUCT(BlueprintType)
struct FSurfMoveSnapshot
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "SURFKINI|Net")
	int32 Tick = 0;

	UPROPERTY(BlueprintReadWrite, Category = "SURFKINI|Net")
	FVector Position = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, Category = "SURFKINI|Net")
	FVector Velocity = FVector::ZeroVector;
};

UCLASS(BlueprintType)
class SURFKINI_API USurfNetSnapshotBuffer : public UObject
{
	GENERATED_BODY()

private:
	static constexpr int32 BUFFER_SIZE = 128;
	FSurfMoveSnapshot History[BUFFER_SIZE];

public:
	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Net")
	void RecordSnapshot(int32 Tick, const FVector& Position, const FVector& Velocity);

	UFUNCTION(BlueprintCallable, Category = "SURFKINI|Net")
	bool GetSnapshot(int32 Tick, FSurfMoveSnapshot& OutSnapshot) const;
};
