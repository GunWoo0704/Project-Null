using UnrealBuildTool;
using System.Collections.Generic;

public class Project_NullEditorTarget : TargetRules
{
	public Project_NullEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;
		ExtraModuleNames.AddRange(new string[] { "Project_Null" });
	}
}
