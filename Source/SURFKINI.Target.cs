using UnrealBuildTool;

public class SURFKINITarget : TargetRules
{
	public SURFKINITarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("SURFKINI");
	}
}
