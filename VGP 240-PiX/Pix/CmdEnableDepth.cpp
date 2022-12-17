#include "CmdEnableDepth.h"

#include "DepthBuffer.h"

bool CmdEnableDepth::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param as on or off
	if (params.empty())
		return false;

	const bool enabled = params[0] == "true";

	// Enable depth buffer
	DepthBuffer::Get()->SetEnabled(enabled);
	return true;
}
