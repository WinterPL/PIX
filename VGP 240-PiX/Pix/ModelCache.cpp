#include "ModelCache.h"

ModelCache* ModelCache::Get()
{
	static ModelCache sInstance;
	return &sInstance;
}

void ModelCache::Clear()
{
	mModels.clear();
}

const Model* ModelCache::GetModel(const std::string& fileName)
{
	auto iter = std::find_if(mModels.begin(), mModels.end(), [fileName](auto& model)
		{
			return model->GetFileName() == fileName;
		});
	if (iter != mModels.end())
	{
		return iter->get();
	}

	auto& model = mModels.emplace_back(std::make_unique<Model>());
	model->Load(fileName);
	return model.get();
}