// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurfRuntimeLevelEditor.generated.h"

USTRUCT(BlueprintType)
struct FSurfEditorObjectData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Editor")
	FString ObjectType = "Ramp";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Editor")
	FVector Location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Editor")
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Editor")
	FVector Scale = FVector(1.0f, 1.0f, 1.0f);
};

UCLASS()
class SURFKINI_API ASurfRuntimeLevelEditor : public AActor
{
	GENERATED_BODY()

public:
	ASurfRuntimeLevelEditor();

	UFUNCTION(BlueprintCallable, Category = "Level Editor")
	void SpawnEditorObject(FString ObjectType, FVector WorldLocation, FRotator WorldRotation, FVector ObjectScale);

	UFUNCTION(BlueprintCallable, Category = "Level Editor")
	FString ExportMapToJson() const;

	UFUNCTION(BlueprintCallable, Category = "Level Editor")
	bool ImportMapFromJson(const FString& JsonData);

	UFUNCTION(BlueprintPure, Category = "Level Editor")
	FVector SnapToGrid(FVector RawLocation, float GridSize = 100.0f) const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Editor")
	TArray<FSurfEditorObjectData> PlacedObjects;
};
