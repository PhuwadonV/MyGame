using UnrealBuildTool;

public class ExtendBlueprintOnlineSubsystem : ModuleRules
{
	public ExtendBlueprintOnlineSubsystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;		
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "OnlineSubsystem", "OnlineSubsystemUtils" } );
	}
}