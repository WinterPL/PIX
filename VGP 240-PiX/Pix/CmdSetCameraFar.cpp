#include "CmdSetCameraFar.h"
#include "Camera.h"
#include "VariableCache.h"

bool CmdSetCameraFar::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
		return false;

	float value = VariableCache::Get()->GetFloat(params[0]);
	Camera::Get()->SetFarPlane(value);
	return true;
}
