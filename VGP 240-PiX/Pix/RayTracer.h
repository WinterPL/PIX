#pragma once

#include "MathHelper.h"
#include <XEngine.h>

class RayTracer
{
public:
	static RayTracer* Get();

public:
	void OnNewFrame();

	bool BeginDraw();
	void AddObject(Sphere sphere, X::Color color, float ri);
	void AddLight(Vector3 position, X::Color color);
	bool EndDraw();

private:
	X::Color Trace(Ray ray, int depth);

	struct Object
	{
		Sphere sphere;
		X::Color color;
		float refractionIndex = 0;

		bool IsOpaque() const
		{
			return refractionIndex == 0;
		}
	};

	struct Light
	{
		Vector3 position;
		X::Color color;
		float attenC = 1.0f;
		float attenL = 0.0f;
		float attenQ = 0.001f;
	};

	std::vector<Object> mObjects;
	std::vector<Light> mLights;
	float mAmbient = 0.0f;
};