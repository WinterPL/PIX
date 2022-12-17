#pragma once

#include "Command.h"

class CmdSetCameraFov : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraFov";
	}

	const char* GetDescription() override
	{
		return
			"Sets camera fov";
	}

	bool Execute(const std::vector<std::string>& params) override;
};