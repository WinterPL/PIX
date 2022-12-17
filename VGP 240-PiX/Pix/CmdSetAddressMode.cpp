#include "CmdSetAddressMode.h"

#include "TextureCache.h"

bool CmdSetAddressMode::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param as address mode
	if (params.empty())
		return false;

	AddressMode mode;
	if (params[0] == "clamp")
		mode = AddressMode::Clamp;
	else if (params[0] == "wrap")
		mode = AddressMode::Wrap;
	else
		return false;

	// Set address mode
	TextureCache::Get()->SetAddressMode(mode);
	return true;
}
