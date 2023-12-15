// Copyright Eder


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
 	int32 Level = 0;
	for (FAuraLevelUpInfo LevelupInfo :LevelUpInformation)
	{
		if ( XP >= LevelupInfo.LevelUpRequirement)
		{
			Level++;
		}
	}	
	return Level;
	
	// Alternate DRUID CODE for level
	/*INIT
	
	int32 Level = 1;
	bool bSearching =true;
	while (bSearching)
	{
		if (LevelUpInformation.Num() - 1 <= Level) return Level;

		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching=false;
		}
	}
	return Level;

	END*/
}
