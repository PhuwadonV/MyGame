using UnrealBuildTool;

public class MyGame : ModuleRules {
	public MyGame(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });
	}
}
