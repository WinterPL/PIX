#pragma once

#include "Command.h"

class CmdSetLightAmbient : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightAmbient";
	}

	const char* GetDescription() override
	{
		return
			"SetLightAmbient(r, g, b)\n"
			"\n"
			"- Sets the ambient values for the next light be added. Values are from 0.0 to 1.0.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetLightDiffuse : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightDiffuse";
	}

	const char* GetDescription() override
	{
		return
			"SetLightDiffuse(r, g, b)\n"
			"\n"
			"- Sets the diffuse values for the next light be added. Values are from 0.0 to 1.0.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetLightSpecular : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightSpecular";
	}

	const char* GetDescription() override
	{
		return
			"SetLightSpecular(r, g, b)\n"
			"\n"
			"- Sets the specular values for the next light be added. Values are from 0.0 to 1.0.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdAddDirectionalLight : public Command
{
public:
	const char* GetName() override
	{
		return "AddDirectionalLight";
	}

	const char* GetDescription() override
	{
		return
			"AddDirectionalLight(x, y, z)\n"
			"\n"
			"- Add a new directional light with direction(x, y, z).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdAddPointLight : public Command
{
public:
	const char* GetName() override
	{
		return "AddPointLight";
	}

	const char* GetDescription() override
	{
		return
			"AddPointLight(x, y, z, c, l, q)\n"
			"\n"
			"- Add a new point light with position(x, y, z).\n"
			"- (Optional) Specify attentuation values: constant(c), linear(l), quadratic(q).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdAddSpotLight : public Command
{
public:
	const char* GetName() override
	{
		return "AddSpotLight";
	}

	const char* GetDescription() override
	{
		return
			"AddSpotLight(x, y, z, dx, dy, dz, c, l, q, a, d)\n"
			"\n"
			"- Add a new point light with position(x, y, z), and direction(dx, dy, dz).\n"
			"- (Optional) Specify attentuation values: constant(c), linear(l), quadratic(q).\n"
			"- (Optional) Specify angle(a) and decay(d)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
