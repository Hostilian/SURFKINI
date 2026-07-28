using UnrealBuildTool;

public class SURFKINITarget : TargetRules
{
	public SURFKINITarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("SURFKINI");
	}
}
