#include "CmdSetTexture.h"
#include "TextureCache.h"

bool CmdSetTexture::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param for file name
	if (params.size() < 1)
		return false;

	// Set and load the texture
	TextureCache::Get()->SetTexture(params[0]);
	return true;
}
