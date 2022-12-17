#pragma once

#include "Command.h"

class CmdShowViewport : public Command
{
public:
	const char* GetName() override
	{
		return "ShowViewport";
	}

	const char* GetDescription() override
	{
		return
			"ShowViewport(show)\n"
			"\n"
			"- Shows the viewport.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};