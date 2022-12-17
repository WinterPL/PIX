#pragma once

#include "Command.h"

class CmdSetCameraNear : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraNear";
	}

	const char* GetDescription() override
	{
		return
			"Sets near value for the camera";
	}

	bool Execute(const std::vector<std::string>& params) override;
};