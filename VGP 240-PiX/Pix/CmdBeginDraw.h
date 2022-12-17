#pragma once

#include "Command.h"

class CmdBeginDraw : public Command
{
public:
	const char* GetName() override
	{
		return "BeginDraw";
	}

	const char* GetDescription() override
	{
		return
			"BeginDraw(<topology>)\n"
			"\n"
			"- Begin primitive drawing.\n"
			"- Topology can be:\n"
			"    point\n"
			"    line\n"
			"    triangle\n"
			"- Optional: 3D can be true or false";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
