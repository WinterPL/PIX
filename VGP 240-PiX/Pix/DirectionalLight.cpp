#include "DirectionalLight.h"
#include "Camera.h"
#include "MaterialManager.h"

X::Color DirectionalLight::ComputeLightColor(const Vector3& position, const Vector3& normal) const
{
	auto cam = Camera::Get();
	auto mm = MaterialManager::Get();

	X::Color colorAmbient = mAmbient * mm->GetMaterialAmbient();

	auto dirToLight = -mDirection;
	float dot = MathHelper::Dot(dirToLight, normal);
	X::Color colorDiffuse = mDiffuse * mm->GetMaterialDiffuse() * X::Math::Max(dot, 0.0f);

	auto dirToEye = cam->GetPosition();
	auto half = MathHelper::Normalize(dirToLight + dirToEye);
	float fallOff = pow(MathHelper::Dot(half, normal), mm->GetMaterialShininess());
	X::Color colorSpecular = mSpecular * mm->GetMaterialSpecular() * X::Math::Max(fallOff, 0.0f);

	return colorAmbient + colorDiffuse + colorSpecular;
}

void DirectionalLight::SetDirection(const Vector3& direction)
{
	mDirection = direction;
}