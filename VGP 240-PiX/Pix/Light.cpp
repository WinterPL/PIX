#include "Light.h"

void Light::SetAmbient(X::Color ambient)
{
	mAmbient = ambient;
}

void Light::SetDiffuse(X::Color diffuse)
{
	mDiffuse = diffuse;
}

void Light::SetSpecular(X::Color specular)
{
	mSpecular = specular;
}