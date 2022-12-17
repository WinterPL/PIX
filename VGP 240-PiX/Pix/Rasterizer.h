#pragma once

#include "Vertex.h"
#include <XEngine.h>

enum class FillMode //As2
{
	Solid,
	Wireframe
};

enum class ShadeMode
{
	Flat,
	Gouraud,
	Phong
};

class Rasterizer
{
public:
	static Rasterizer* Get();

	void SetColor(X::Color color);
	void SetFillMode(FillMode mode);
	void SetShadeMode(ShadeMode mode);
	ShadeMode GetShadeMode() { return mShadeMode; }

	void DrawPoint(int x, int y);

	void DrawPoint(const Vertex& v);//As2
	void DrawLine(const Vertex& v1, const Vertex& v2);//As2
	void DrawTriangle(Vertex v1, Vertex v2, Vertex v3);//As2

private:
	void DrawTriangleFilled(const Vertex& v1, const Vertex& v2, const Vertex& v3);

	X::Color mColor = X::Colors::White;
	FillMode mFillMode = FillMode::Solid;
	ShadeMode mShadeMode = ShadeMode::Gouraud;
};

