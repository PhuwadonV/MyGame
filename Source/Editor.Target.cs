using UnrealBuildTool;

public class EditorTarget : TargetRules {
	public EditorTarget(TargetInfo Target) : base(Target) {
		Type = TargetType.Editor;
		
		ExtraModuleNames.AddRange( new string[] { "MyGame" } );
	}
}
