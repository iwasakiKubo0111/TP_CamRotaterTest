// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TP_CamRotaterTest : ModuleRules
{
	public TP_CamRotaterTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Slate", "SlateCore" });//UMG“ü‚ê‚È‚¢‚Æƒrƒ‹ƒh‚ª’Ê‚ç‚È‚¢
	}
}
