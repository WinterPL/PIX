#include "CmdPushRotationZ.h"

#include "MatrixStack.h"
#include "VariableCache.h"

bool CmdPushRotationZ::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param for rotation angle
	if (params.empty())
		return false;

	auto vc = VariableCache::Get();
	float degree = vc->GetFloat(params[0]);

	// Push a rotation Z matrix
	MatrixStack::Get()->PushRotationZ(degree * 3.1416f / 180.0f);
	return true;
}
