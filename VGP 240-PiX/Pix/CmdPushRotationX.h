#pragma once

#include "Command.h"

class CmdPushRotationX : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationX";
	}

	const char* GetDescription() override
	{
		return
			"PushRotationX(degree)\n"
			"\n"
			"- Push a rotation matrix around the X-axis to the stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
