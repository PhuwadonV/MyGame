using UnrealBuildTool;

public class ExtendBlueprintEngine : ModuleRules {
	public ExtendBlueprintEngine(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;		
		
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine" } );
	}
}
