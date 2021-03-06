// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PythonOnlineDocsCommandlet.h"
#include "PyWrapperTypeRegistry.h"

DEFINE_LOG_CATEGORY_STATIC(LogPythonOnlineDocsCommandlet, Log, All);

UPythonOnlineDocsCommandlet::UPythonOnlineDocsCommandlet()
{
	IsServer = true;
	IsClient = true;
	IsEditor = true;
	LogToConsole = false;
	ShowErrorCount = false;
}

int32 UPythonOnlineDocsCommandlet::Main(const FString& Params)
{
	TArray<FString> Tokens;
	TArray<FString> Switches;
	TMap<FString, FString> ParamVals;
	UCommandlet::ParseCommandLine(*Params, Tokens, Switches, ParamVals);


	EPyOnlineDocsFilterFlags DocGenFlags = EPyOnlineDocsFilterFlags::IncludeNone;

	// Apply the filter flags from the command line
#define APPLY_FILTER_FLAG(NAME)							\
	if (Switches.Contains(TEXT(#NAME)))					\
	{													\
		DocGenFlags |= EPyOnlineDocsFilterFlags::NAME;	\
	}
	APPLY_FILTER_FLAG(IncludeEngine)
	APPLY_FILTER_FLAG(IncludeEnterprise)
	APPLY_FILTER_FLAG(IncludeInternal)
	APPLY_FILTER_FLAG(IncludeProject)
#undef APPLY_FILTER_FLAG

	// If we weren't given any filter flags, include everything
	if (DocGenFlags == EPyOnlineDocsFilterFlags::IncludeNone)
	{
		DocGenFlags = EPyOnlineDocsFilterFlags::IncludeAll;
	}

	UE_LOG(LogPythonOnlineDocsCommandlet, Display, TEXT("\n\nGenerating Python documentation..."));
	FPyWrapperTypeRegistry::Get().GenerateStubCodeForWrappedTypes(DocGenFlags);


	
	//UE_LOG(LogPythonOnlineDocsCommandlet, Error, TEXT("Python docs cannot be generated as the plugin was built as a stub!"));
	//return -1;



	return 0;
}
