#pragma once

#include "Command.h"

class CmdSetFillMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetFillMode";
	}

	const char* GetDescription() override
	{
		return
			"SetFillMode(<mode>)\n"
			"\n"
			"- Sets the rasterizer fill mode.\n"
			"- Mode can be:\n"
			"    solid\n"
			"    wireframe";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
