#pragma once

#include "Command.h"

class CmdSetClipping : public Command
{
public:
	const char* GetName() override
	{
		return "SetClipping";
	}

	const char* GetDescription() override
	{
		return
			"SetClipping(enable)\n"
			"\n"
			"- Enables Clipping.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};