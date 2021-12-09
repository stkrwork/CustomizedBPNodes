// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class CustomizedBPNodesEditor : ModuleRules
{
	public CustomizedBPNodesEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"UnrealEd",
			"BlueprintGraph",
			"KismetCompiler",
			"Slate",
			"SlateCore",
			"EditorStyle",
			"GraphEditor",
			"CustomizedBPNodes"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PrivateIncludePaths.AddRange(Directory.GetDirectories(Path.Combine(ModuleDirectory, "Public"), "*", SearchOption.AllDirectories));
		PrivateIncludePaths.AddRange(Directory.GetDirectories(Path.Combine(ModuleDirectory, "Private"), "*", SearchOption.AllDirectories));
	}
}
