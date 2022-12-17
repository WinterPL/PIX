#include "CmdPushScaling.h"

#include "MatrixStack.h"

bool CmdPushScaling::Execute(const std::vector<std::string>& params)
{
	// Need at least 3 params for x, y, z
	if (params.size() < 3)
		return false;

	float x = stof(params[0]);
	float y = stof(params[1]);
	float z = stof(params[2]);

	// Push a scaling matrix
	MatrixStack::Get()->PushScaling({ x, y, z });
	return true;
}
