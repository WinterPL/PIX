#pragma once

#include "Command.h"

class CmdSetTexture : public Command
{
public:
	const char* GetName() override
	{
		return "SetTexture";
	}

	const char* GetDescription() override
	{
		return
			"SetTexture(fileName)\n"
			"- Set the current texture to be used.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
