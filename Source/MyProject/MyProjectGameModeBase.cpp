// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"

AMyProjectGameModeBase::AMyProjectGameModeBase() {

	static ConstructorHelpers::FClassFinder<APawn> PawnAssets
	(TEXT("Class'/Script/MyProject.MyPlayerCPP'"));
	if (PawnAssets.Succeeded()) {
		DefaultPawnClass = PawnAssets.Class;
	}
}