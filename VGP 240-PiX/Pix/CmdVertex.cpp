#include "CmdVertex.h"

#include "PrimitiveManager.h"
#include "VariableCache.h"

bool CmdVertex::Execute(const std::vector<std::string>& params)
{
	
	float x = 0.0f, y = 0.0f, z = 0.0f;
	float r = 255.f, g = 255.f, b = 255.f;
	if (params.size() == 2)
	{
		x = stof(params[0]);
		y = stof(params[1]);
	}
	else if (params.size() == 3)
	{
		x = stof(params[0]);
		y = stof(params[1]);
		z = stof(params[2]);
	}
	else if (params.size() == 5)
	{
		x = stof(params[0]);
		y = stof(params[1]);
		r = stof(params[2]);
		g = stof(params[3]);
		b = stof(params[4]);
	}
	else if (params.size() == 6)
	{
		x = stof(params[0]);
		y = stof(params[1]);
		z = stof(params[2]);
		r = stof(params[3]);
		g = stof(params[4]);
		b = stof(params[5]);
	}
	else
	{
		return false;
	}
	Vertex v;
	v.pos.x = x;
	v.pos.y = y;
	v.pos.z = z;
	v.color = X::Color(r/255, g/255, b/255, 1.0f);
	PrimitiveManager::Get()->AddVertex(v);
	return true;
}
