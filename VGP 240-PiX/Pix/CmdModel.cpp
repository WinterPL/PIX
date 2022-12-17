#include "CmdModel.h"

#include "ModelCache.h"
#include "PrimitiveManager.h"

bool CmdModel::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param for file name
	if (params.size() < 1)
		return false;

	auto model = ModelCache::Get()->GetModel(params[0]);
	auto pm = PrimitiveManager::Get();
	for (int i = 0; i < model->GetVertexCount(); ++i)
		pm->AddVertex(model->GetVertex(i));

	return true;
}
