#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
	virtual X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const override;

	void SetPosition(const Vector3& position);
	void SetAttenuation(float constant, float linear, float quadratic);

protected:
	Vector3 mPosition;
	float mAttenConst = -1.0f;
	float mAttenLinear = 0.0f;
	float mAttenQuadratic = 0.0f;
};