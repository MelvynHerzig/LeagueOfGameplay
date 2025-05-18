// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LeagueOfGameplay : ModuleRules
{
	public LeagueOfGameplay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.Add(ModuleDirectory);
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"NavigationSystem",
			"AIModule",
			"UMG",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "Niagara" });
	}
}
