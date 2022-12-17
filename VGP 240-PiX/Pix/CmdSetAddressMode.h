#pragma once

#include "Command.h"

class CmdSetAddressMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetAddressMode";
	}

	const char* GetDescription() override
	{
		return
			"SetAddressMode(<mode>)\n"
			"\n"
			"- Sets the texture address mode.\n"
			"- Mode can be:\n"
			"    clamp\n"
			"    wrap";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
