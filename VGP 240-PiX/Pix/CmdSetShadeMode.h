#pragma once
#include "Command.h"

class CmdSetShadeMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetShadeMode";
	}

	const char* GetDescription() override
	{
		return
			"SetShadeMode(<mode>)\n"
			"\n"
			"- Sets the primitive shade mode.\n"
			"- Mode can be:\n"
			"    Flat\n"
			"    Gouraud\n"
			"    Phong";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

