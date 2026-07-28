using UnrealBuildTool;

public class SURFKINIEditorTarget : TargetRules
{
	public SURFKINIEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("SURFKINI");
	}
}
