#pragma once

#include "Command.h"

class CmdPushRotationY : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationY";
	}

	const char* GetDescription() override
	{
		return
			"PushRotationY(degree)\n"
			"\n"
			"- Push a rotation matrix around the Y-axis to the stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
