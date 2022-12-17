#include "MaterialManager.h"

MaterialManager* MaterialManager::Get()
{
	static MaterialManager sInstance;
	return &sInstance;
}

void MaterialManager::OnNewFrame()
{
	mAmbient = X::Colors::White;
	mDiffuse = X::Colors::White;
	mSpecular = X::Colors::White;
	mShininess = 1.0f;
}

void MaterialManager::SetMaterialAmbient(X::Color ambient)
{
	mAmbient = ambient;
}

void MaterialManager::SetMaterialDiffuse(X::Color diffuse)
{
	mDiffuse = diffuse;
}

void MaterialManager::SetMaterialSpecular(X::Color specular)
{
	mSpecular = specular;
}

void MaterialManager::SetMaterialShininess(float shininess)
{
	mShininess = shininess;
}

X::Color MaterialManager::GetMaterialAmbient() const
{
	return mAmbient;
}

X::Color MaterialManager::GetMaterialDiffuse() const
{
	return mDiffuse;
}

X::Color MaterialManager::GetMaterialSpecular() const
{
	return mSpecular;
}

float MaterialManager::GetMaterialShininess() const
{
	return mShininess;
}

