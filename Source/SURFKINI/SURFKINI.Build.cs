using UnrealBuildTool;

public class SURFKINI : ModuleRules
{
	public SURFKINI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

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
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
		});

		// Uncomment for developer tools (logging, profiling)
		// PrivateDependencyModuleNames.Add("DeveloperSettings");

		// Uncomment when adding Mass AI for crowds
		// PublicDependencyModuleNames.Add("MassEntity");
		// PublicDependencyModuleNames.Add("MassActors");
		// PublicDependencyModuleNames.Add("MassAI");
	}
}
