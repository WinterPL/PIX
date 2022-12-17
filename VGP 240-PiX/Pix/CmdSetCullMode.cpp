#include "CmdSetCullMode.h"

#include "PrimitiveManager.h"

bool CmdSetCullMode::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param as fill mode
	if (params.empty())
		return false;

	CullMode mode;
	if (params[0] == "none")
		mode = CullMode::None;
	else if (params[0] == "front")
		mode = CullMode::Front;
	else if (params[0] == "back")
		mode = CullMode::Back;
	else
		return false;

	// Set cull mode
	PrimitiveManager::Get()->SetCullMode(mode);
	return true;
}
