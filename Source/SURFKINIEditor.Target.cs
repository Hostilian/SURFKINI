using UnrealBuildTool;

public class SURFKINIEditorTarget : TargetRules
{
	public SURFKINIEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("SURFKINI");
	}
}
