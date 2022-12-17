#pragma once

#include "Command.h"

class CmdPushRotationZ : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationZ";
	}

	const char* GetDescription() override
	{
		return
			"PushRotationZ(degree)\n"
			"\n"
			"- Push a rotation matrix around the Z-axis to the stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
