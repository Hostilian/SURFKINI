using UnrealBuildTool;

public class SURFKINIEditorTarget : TargetRules
{
	public SURFKINIEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("SURFKINI");
	}
}
