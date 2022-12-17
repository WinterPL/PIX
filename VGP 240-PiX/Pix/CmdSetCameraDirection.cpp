#include "CmdSetCameraDirection.h"
#include "Camera.h"
#include "VariableCache.h"

bool CmdSetCameraDirection::Execute(const std::vector<std::string>& params)
{
	// Need at least 3 params for x, y, z
	if (params.size() < 3)
		return false;

	auto vc = VariableCache::Get();
	float x = vc->GetFloat(params[0]);
	float y = vc->GetFloat(params[1]);
	float z = vc->GetFloat(params[2]);

	Camera::Get()->SetDirection({ x, y, z });
	return true;
}