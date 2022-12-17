#include "CmdPushTranslation.h"
#include "MatrixStack.h"
#include "VariableCache.h"

bool CmdPushTranslation::Execute(const std::vector<std::string>& params)
{
	// Need at least 3 params for x, y, z
	if (params.size() < 3)
		return false;

	auto vc = VariableCache::Get();
	float x = vc->GetFloat(params[0]);
	float y = vc->GetFloat(params[1]);
	float z = vc->GetFloat(params[2]);

	// Push a translation matrix
	MatrixStack::Get()->PushTranslation({ x, y, z });
	return true;
}