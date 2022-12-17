#pragma once

#include "Command.h"

class CmdVertex : public Command
{
public:
	const char* GetName() override
	{
		return "AddVertex";
	}

	const char* GetDescription() override
	{
		return
			"Vertex(x, y)\n"
			"Vertex(x, y, r, g, b)\n"
			"Vertex(x, y, z)\n"
			"Vertex(x, y, z, r, g, b)\n"
			"\n"
			"- Add a single vertex.\n"
			"- If no z is specified, will default to 0.\n"
			"- If no color is specified, will default to white.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
