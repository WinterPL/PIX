#include "CmdSetCameraNear.h"
#include "Camera.h"
#include "VariableCache.h"

bool CmdSetCameraNear::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
		return false;

	float value = VariableCache::Get()->GetFloat(params[0]);
	Camera::Get()->SetNearPlane(value);
	return true;
}