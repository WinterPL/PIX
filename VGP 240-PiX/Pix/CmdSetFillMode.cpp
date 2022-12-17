#include "CmdSetFillMode.h"
#include "Rasterizer.h"

bool CmdSetFillMode::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param as fill mode
	if (params.empty() || params.size() < 1)
		return false;

	FillMode mode = FillMode::Solid;
	if (params[0] == "solid")
		mode = FillMode::Solid;
	else if (params[0] == "wireframe")
		mode = FillMode::Wireframe;
	else
		return false;

	Rasterizer::Get()->SetFillMode(mode);
	return true;
}
