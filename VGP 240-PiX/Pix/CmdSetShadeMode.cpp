#include "CmdSetShadeMode.h"

#include "Rasterizer.h"

bool CmdSetShadeMode::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param as fill mode
	if (params.empty())
		return false;

	ShadeMode mode;
	if (params[0] == "flat")
		mode = ShadeMode::Flat;
	else if (params[0] == "gouraud")
		mode = ShadeMode::Gouraud;
	else if (params[0] == "phong")
		mode = ShadeMode::Phong;
	else
		return false;

	Rasterizer::Get()->SetShadeMode(mode);
	return true;
}
