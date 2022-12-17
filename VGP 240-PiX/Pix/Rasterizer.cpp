#include "Rasterizer.h"
#include "DepthBuffer.h"
#include "LightManager.h"
#include "TextureCache.h"

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	Rasterizer::mColor = color;
}

void Rasterizer::SetFillMode(FillMode mode)
{
	Rasterizer::mFillMode = mode;
}

void Rasterizer::SetShadeMode(ShadeMode mode)
{
	mShadeMode = mode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& v)
{
	X::DrawPixel((int)v.pos.x, (int)v.pos.y, TextureCache::Get()->SampleColor(v.color));
}

void Rasterizer::DrawLine(const Vertex& v1,const  Vertex& v2) {

	//we lerp from v1 to v2
	//draw point
	// y = mx + b
	float dx = v2.pos.x - v1.pos.x;
	float dy = v2.pos.y - v1.pos.y;
	if (std::abs(dx) < 0.01f)
	{
		// y is straight up
		float startY, endY;
		X::Color startColor, endColor;
		if (v1.pos.y < v2.pos.y)
		{
			startY = v1.pos.y;
			endY = v2.pos.y;
		}
		else
		{
			startY = v2.pos.y;
			endY = v1.pos.y;
		}
		for (float y = startY; y <= endY; ++y)
		{
			float t = (y - startY) / (endY - startY);
			Vertex v = LerpVertex(v1, v2, t, mShadeMode == ShadeMode::Phong);
			v.color = TextureCache::Get()->SampleColor(v.color);
			if (mShadeMode == ShadeMode::Phong)
			{
				Vector3 worldPos = LerpPosition(v1.WorldPosition, v2.WorldPosition, t);
				v.color *= LightManager::Get()->ComputeLightColor(v.pos, v.WorldNormal);
			}
			DrawPoint(v);
		}
	}
	else
	{
		float m = dy / dx;
		float b = (v2.pos.y - (m * v2.pos.x));
		if (std::abs(dy) < std::abs(dx))
		{
			Vertex startV, endV;
			if (v1.pos.x < v2.pos.x)
			{
				startV = v1;
				endV = v2;
			}
			else
			{
				startV = v2;
				endV = v1;
			}
			for (float x = startV.pos.x; x <= endV.pos.x; ++x)
			{
				float t = (x - startV.pos.x) / (endV.pos.x - startV.pos.x);
				float y = startV.pos.y + (endV.pos.y - startV.pos.y) * t;
				float depth = startV.pos.z + (endV.pos.z - startV.pos.z) * t;
				if (DepthBuffer::Get()->CheckDepthBuffer((int)x,(int)y, depth))
				{
					Vertex v = LerpVertex(startV, endV, t, mShadeMode == ShadeMode::Phong);
					v.color = TextureCache::Get()->SampleColor(v.color);
					if (mShadeMode == ShadeMode::Phong)
					{
						Vector3 worldPos = LerpPosition(v1.WorldPosition, v2.WorldPosition, t);
						v.color *= LightManager::Get()->ComputeLightColor(v.pos, v.WorldNormal);
					}
					DrawPoint(v);
				}
			}
		}
		else
		{
			Vertex startV, endV;
			if (v1.pos.y < v2.pos.y)
			{
				startV = v1;
				endV = v2;
			}
			else
			{
				startV = v2;
				endV = v1;
			}
			for (float y = startV.pos.y; y <= endV.pos.y; ++y)
			{
				float t = (y - startV.pos.y) / (endV.pos.y - startV.pos.y);
				float x = startV.pos.x + (endV.pos.x - startV.pos.x) * t;
				float depth = startV.pos.z + (endV.pos.z - startV.pos.z) * t;
				if (DepthBuffer::Get()->CheckDepthBuffer((int)x, (int)y, depth))
				{
					Vertex v = LerpVertex(v1, v2, t, mShadeMode == ShadeMode::Phong);
					v.color = TextureCache::Get()->SampleColor(v.color);
					if (mShadeMode == ShadeMode::Phong)
					{
						Vector3 worldPos = LerpPosition(v1.WorldPosition, v2.WorldPosition, t);
						v.color *= LightManager::Get()->ComputeLightColor(v.pos, v.WorldNormal);
					}
					DrawPoint(v);
				}
			}
		}
	}
}

void Rasterizer::DrawTriangle(Vertex v1, Vertex v2, Vertex v3)
{
	if (mShadeMode == ShadeMode::Flat)
	{
		v2.color = v1.color;
		v3.color = v1.color;

		Vector3 faceNorm = MathHelper::Normalize(MathHelper::Cross((v2.pos - v1.pos),
			(v3.pos - v1.pos)));
		v1.Normal = faceNorm;
		v2.Normal = faceNorm;
		v3.Normal = faceNorm;
	}

	switch (mFillMode)
	{
	case FillMode::Wireframe:
		DrawLine(v1, v2);
		DrawLine(v2, v3);
		DrawLine(v3, v1);
		break;
	case FillMode::Solid:
	{
		std::vector<Vertex> sortedVertexes;
		sortedVertexes.push_back(v1);
		sortedVertexes.push_back(v2);
		sortedVertexes.push_back(v3);
		std::sort(sortedVertexes.begin(), sortedVertexes.end(), [](const Vertex& lhs, const Vertex& rhs) { return lhs.pos.y < rhs.pos.y; });
		DrawTriangleFilled(sortedVertexes[0], sortedVertexes[1], sortedVertexes[2]);
		break;
	}
	default:
		break;
	}
}

void Rasterizer::DrawTriangleFilled(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
	// Order vertices from top to bottom
	Vertex yOrder[3] = { v1, v2, v3 };
	Vertex temp;
	if (yOrder[1].pos.y < yOrder[0].pos.y)
	{
		temp = yOrder[0]; yOrder[0] = yOrder[1]; yOrder[1] = temp;
	}
	if (yOrder[2].pos.y < yOrder[1].pos.y)
	{
		temp = yOrder[1]; yOrder[1] = yOrder[2]; yOrder[2] = temp;
	}
	if (yOrder[1].pos.y < yOrder[0].pos.y)
	{
		temp = yOrder[0]; yOrder[0] = yOrder[1]; yOrder[1] = temp;
	}

	// Check for a flat line along y
	if (v1.pos.y != v2.pos.y && v1.pos.y != v3.pos.y && v2.pos.y != v3.pos.y)
	{
		// No flat line, split the triangles and process separately

		// Find vertex to split triangles
		float t = (yOrder[1].pos.y - yOrder[0].pos.y) / (yOrder[2].pos.y - yOrder[0].pos.y);
		Vertex splitVertex = LerpVertex(yOrder[0], yOrder[2], t);

		// draw two new triangles seperately
		DrawTriangleFilled(yOrder[0], splitVertex, yOrder[1]);
		DrawTriangleFilled(yOrder[1], splitVertex, yOrder[2]);
	}
	else
	{
		int yTop = static_cast<int>(yOrder[0].pos.y);
		int yBottom = static_cast<int>(yOrder[2].pos.y);
		int yRange = yBottom - yTop + 1;

		if (yOrder[0].pos.y == yOrder[1].pos.y)
		{
			// Flat top
			int leftTop, rightTop;
			if (yOrder[0].pos.x < yOrder[1].pos.x)
			{
				leftTop = 0;
				rightTop = 1;
			}
			else
			{
				leftTop = 1;
				rightTop = 0;
			}

			for (int y = yTop; y <= yBottom; ++y)
			{
				float t = static_cast<float>(y - yTop) / (yRange - 1);
				Vertex left = LerpVertex(yOrder[leftTop], yOrder[2], t);
				Vertex right = LerpVertex(yOrder[rightTop], yOrder[2], t);
				left.pos.y = right.pos.y = (float)y;
				DrawLine(left, right);
			}
		}
		else
		{
			// Flat bottom
			int leftBottom, rightBottom;
			if (yOrder[1].pos.x < yOrder[2].pos.x)
			{
				leftBottom = 1;
				rightBottom = 2;
			}
			else
			{
				leftBottom = 2;
				rightBottom = 1;
			}

			for (int y = yTop; y <= yBottom; ++y)
			{
				float t = static_cast<float>(y - yTop) / (yRange - 1);
				Vertex left = LerpVertex(yOrder[0], yOrder[leftBottom], t);
				Vertex right = LerpVertex(yOrder[0], yOrder[rightBottom], t);
				left.pos.y = right.pos.y = (float)y;
				DrawLine(left, right);
			}
		}
	}
}
