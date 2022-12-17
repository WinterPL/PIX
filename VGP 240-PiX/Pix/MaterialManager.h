#pragma once

#include <XEngine.h>

class MaterialManager
{
public:
	static MaterialManager* Get();

public:
	void OnNewFrame();

	void SetMaterialAmbient(X::Color ambient);
	void SetMaterialDiffuse(X::Color diffuse);
	void SetMaterialSpecular(X::Color specular);
	void SetMaterialShininess(float shininess);

	X::Color GetMaterialAmbient() const;
	X::Color GetMaterialDiffuse() const;
	X::Color GetMaterialSpecular() const;
	float GetMaterialShininess() const;
	
private:
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;
	float mShininess = 1.0f;
};