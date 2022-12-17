#pragma once

#include "Light.h"

class SpotLight : public Light
{
public:
	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const override;

	void SetPosition(Vector3 position);
	void SetDirection(Vector3 direction);
	void SetAttenuation(float constant, float linear, float quadratic);
	void SetAngle(float radian);
	void SetDecay(float decay);

protected:
	Vector3 mPosition;
	Vector3 mDirection;
	float mAttenConst = 0.0f;
	float mAttenLinear = 0.01f;
	float mAttenQuadratic = 0.0f;
	float mCosAngle = cos(0.7854f); // 45 degrees
	float mDecay = 1.0f;
};