using UnrealBuildTool;

public class SURFKINI : ModuleRules
{
	public SURFKINI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",      // UE5 enhanced input system
			"NetCore",            // Networking foundations
			"OnlineSubsystem",    // Multiplayer / matchmaking
			"PhysicsCore",        // Physics queries for surf collision
			"UMG",                // UI widgets (SpeedMeterWidget)
			"AIModule",           // Behavior Trees and AIControllers
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore"
		});
	}
}
