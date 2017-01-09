#pragma once
#include "CommandDispatcher.h"

class FModelCommandHandler : public FCommandHandler
{
public:
	FModelCommandHandler(FCommandDispatcher* InCommandDispatcher) : FCommandHandler(InCommandDispatcher)
	{}
	void RegisterCommands();

	FExecStatus LoadUAsset(const TArray<FString>& Path);
};
