#include "CmdPushRotationX.h"
#include "MatrixStack.h"
#include "VariableCache.h"

bool CmdPushRotationX::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param for rotation angle
	if (params.empty())
		return false;

	auto vc = VariableCache::Get();
	float degree = vc->GetFloat(params[0]);

	MatrixStack::Get()->PushRotationX(degree * 3.1416f / 180.0f);
	return true;
}