#include "CmdSetColor.h"

#include "Rasterizer.h"
#include "VariableCache.h"

bool CmdSetColor::Execute(const std::vector<std::string>& params)
{
	// Need at least 3 params for r, g, b
	if (params.size() < 3)
		return false;

	float r = std::stof(params[0])/255;
	float g = std::stof(params[1])/255;
	float b = std::stof(params[2])/255;
	// Set color
	Rasterizer::Get()->SetColor({ r, g, b, 1.0f });
	return true;
}
