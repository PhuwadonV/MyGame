using UnrealBuildTool;

public class ExtendBlueprint : ModuleRules
{
	public ExtendBlueprint(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;		
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "OnlineSubsystem" } );
		//PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
