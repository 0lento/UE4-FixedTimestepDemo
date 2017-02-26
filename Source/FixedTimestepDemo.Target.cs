// Copyright 2017 0lento. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FixedTimestepDemoTarget : TargetRules
{
	public FixedTimestepDemoTarget(TargetInfo Target)
	{
		Type = TargetType.Game;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "FixedTimestepDemo" } );
	}
}
