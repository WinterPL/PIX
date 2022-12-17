#pragma once

#include "Command.h"

class CmdSetCullMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetCullMode";
	}

	const char* GetDescription() override
	{
		return
			"SetCullMode(<mode>)\n"
			"\n"
			"- Sets the primitive cull mode.\n"
			"- Mode can be:\n"
			"    none\n"
			"    front (i.e. clockwise)\n"
			"    back (i.e. counter-clockwise)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
