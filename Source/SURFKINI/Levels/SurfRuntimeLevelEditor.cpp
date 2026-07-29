// Copyright 2026 SURFKINI Team. Open-Source Licensed.

#include "Levels/SurfRuntimeLevelEditor.h"

ASurfRuntimeLevelEditor::ASurfRuntimeLevelEditor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASurfRuntimeLevelEditor::SpawnEditorObject(FString ObjectType, FVector WorldLocation, FRotator WorldRotation, FVector ObjectScale)
{
	FSurfEditorObjectData Data;
	Data.ObjectType = ObjectType;
	Data.Location = SnapToGrid(WorldLocation);
	Data.Rotation = WorldRotation;
	Data.Scale = ObjectScale;

	PlacedObjects.Add(Data);
}

FVector ASurfRuntimeLevelEditor::SnapToGrid(FVector RawLocation, float GridSize) const
{
	if (GridSize <= 0.0f) return RawLocation;
	return FVector(
		FMath::RoundToFloat(RawLocation.X / GridSize) * GridSize,
		FMath::RoundToFloat(RawLocation.Y / GridSize) * GridSize,
		FMath::RoundToFloat(RawLocation.Z / GridSize) * GridSize
	);
}

FString ASurfRuntimeLevelEditor::ExportMapToJson() const
{
	FString JsonOutput = "{\n  \"map_version\": \"1.0\",\n  \"objects\": [\n";
	for (int32 i = 0; i < PlacedObjects.Num(); ++i)
	{
		const FSurfEditorObjectData& Obj = PlacedObjects[i];
		JsonOutput += FString::Printf(
			TEXT("    { \"type\": \"%s\", \"pos\": [%.1f, %.1f, %.1f], \"rot\": [%.1f, %.1f, %.1f] }%s\n"),
			*Obj.ObjectType, Obj.Location.X, Obj.Location.Y, Obj.Location.Z,
			Obj.Rotation.Pitch, Obj.Rotation.Yaw, Obj.Rotation.Roll,
			(i == PlacedObjects.Num() - 1) ? "" : ","
		);
	}
	JsonOutput += "  ]\n}";
	return JsonOutput;
}

bool ASurfRuntimeLevelEditor::ImportMapFromJson(const FString& JsonData)
{
	return !JsonData.IsEmpty();
}
