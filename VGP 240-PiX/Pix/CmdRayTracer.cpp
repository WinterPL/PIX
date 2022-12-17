#include "CmdRayTracer.h"

#include "RayTracer.h"
#include "VariableCache.h"

bool CmdBeginRayTracing::Execute(const std::vector<std::string>& params)
{
	return RayTracer::Get()->BeginDraw();
}

bool CmdEndRayTracing::Execute(const std::vector<std::string>& params)
{
	return RayTracer::Get()->EndDraw();
}

bool CmdRTSphere::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 7)
		return false;

	auto vc = VariableCache::Get();
	float x = vc->GetFloat(params[0]);
	float y = vc->GetFloat(params[1]);
	float z = vc->GetFloat(params[2]);
	float rad = vc->GetFloat(params[3]);
	float r = vc->GetFloat(params[4]);
	float g = vc->GetFloat(params[5]);
	float b = vc->GetFloat(params[6]);
	float ri = 0;
	if (params.size() > 7)
		ri = vc->GetFloat(params[7]);

	RayTracer::Get()->AddObject({ { x, y, z }, rad }, { r, g, b, 1.0f }, ri);
	return true;
}

bool CmdRTLight::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 6)
		return false;

	auto vc = VariableCache::Get();
	float x = vc->GetFloat(params[0]);
	float y = vc->GetFloat(params[1]);
	float z = vc->GetFloat(params[2]);
	float r = vc->GetFloat(params[3]);
	float g = vc->GetFloat(params[4]);
	float b = vc->GetFloat(params[5]);

	RayTracer::Get()->AddLight({ x, y, z }, { r, g, b, 1.0f });
	return true;
}