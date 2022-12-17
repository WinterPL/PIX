#include "Clipper.h"
#include "Viewport.h"

const int BIT_INSIDE = 0;	  // 0000
const int BIT_LEFT   = 1 << 1; // 0001
const int BIT_RIGHT  = 1 << 2; // 0010
const int BIT_BOTTOM = 1 << 3; // 0100
const int BIT_TOP    = 1 << 4; // 1000

enum class ClipEdge : int { Left, Bottom, Right, Top, Count };
bool IsInFront(ClipEdge edge, const Vector3& pnt)
{
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();
	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();

	switch (edge)
	{
	case ClipEdge::Left:	return pnt.x > minX;
	case ClipEdge::Bottom:	return pnt.y < maxY;
	case ClipEdge::Right:	return pnt.x < maxX;
	case ClipEdge::Top:		return pnt.y > minY;
	default:
		break;
	}
	return false;
}

Vertex ComputeIntersection(ClipEdge edge, const Vertex& v1, const Vertex& v2)
{
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();
	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();

	float t = 0.0f;
	switch (edge)
	{
	case ClipEdge::Left:
		t = (minX - v1.pos.x) / (v2.pos.x - v1.pos.x);
		break;
	case ClipEdge::Bottom:
		t = (maxY - v1.pos.y) / (v2.pos.y - v1.pos.y);
		break;
	case ClipEdge::Right:
		t = (maxX - v1.pos.x) / (v2.pos.x - v1.pos.x);
		break;
	case ClipEdge::Top:
		t = (minY - v1.pos.y) / (v2.pos.y - v1.pos.y);
		break;
	default:
		break;
	}

	return LerpVertex(v1, v2, t);
}



int GetOutputCode(float x, float y)
{
	int code = BIT_INSIDE;

	if (x < Viewport::Get()->GetMinX()) {
		code = BIT_LEFT;
	}
	else if (x > Viewport::Get()->GetMaxX()) {
		code = BIT_RIGHT;
	}
	if (y < Viewport::Get()->GetMinY()) {
		code = BIT_BOTTOM;
	}
	else if (y > Viewport::Get()->GetMaxY()) {
		code = BIT_TOP;
	}

	return code;

}

Clipper::Clipper()
{

}
Clipper::~Clipper()
{

}
Clipper* Clipper::Get()
{
	static Clipper sInstance;
	return &sInstance;
}

void Clipper::OnNewFrame()
{

}
bool Clipper::ClipPoint(const Vertex& v)
{
	if (mClipping)
	{
		float maxX = Viewport::Get()->GetMaxX();
		float maxY = Viewport::Get()->GetMaxY();
		float minX = Viewport::Get()->GetMinX();
		float minY = Viewport::Get()->GetMinY();

		return v.pos.x >= minX && v.pos.x <= maxX
			&& v.pos.y >= minY && v.pos.y <= maxY;
	}
	return true;
}
bool Clipper::ClipLine(Vertex& v1, Vertex& v2)
{
	if (mClipping)
	{
		float maxX = Viewport::Get()->GetMaxX();
		float maxY = Viewport::Get()->GetMaxY();
		float minX = Viewport::Get()->GetMinX();
		float minY = Viewport::Get()->GetMinY();
		int codeV1 = GetOutputCode(v1.pos.x, v1.pos.y);
		int codeV2 = GetOutputCode(v2.pos.x, v2.pos.y);
		bool accept = false;

		while (true)
		{
			if (!(codeV1 | codeV2))
			{
				accept = true;
				break;
			}
			else if (codeV1 & codeV2)
			{
				break;
			}
			else
			{
				float x = 0.0f, y = 0.0f;
				int outcodeOut = codeV2 > codeV1 ? codeV2 : codeV1;

				if (outcodeOut & BIT_TOP)
				{
					x = v1.pos.x + (v2.pos.x - v1.pos.x) * (maxY - v1.pos.y) / (v2.pos.y - v1.pos.y);
					y = maxY;
				}
				else if (outcodeOut & BIT_BOTTOM)
				{
					x = v1.pos.x + (v2.pos.x - v1.pos.x) * (minY - v1.pos.y) / (v2.pos.y - v1.pos.y);
					y = minY;
				}
				else if (outcodeOut & BIT_RIGHT)
				{
					y = v1.pos.y + (v2.pos.y - v1.pos.y) * (maxX - v1.pos.x) / (v2.pos.x - v1.pos.x);
					x = maxX;
				}
				else if (outcodeOut & BIT_LEFT)
				{
					y = v1.pos.y + (v2.pos.y - v1.pos.y) * (minX - v1.pos.x) / (v2.pos.x - v1.pos.x);
					x = minX;
				}
				if (outcodeOut == codeV1)
				{
					v1.pos.x = x;
					v1.pos.y = y;
					codeV1 = GetOutputCode(v1.pos.x, v1.pos.y);
				}
				else
				{
					v2.pos.x = x;
					v2.pos.y = y;
					codeV2 = GetOutputCode(v2.pos.x, v2.pos.y);
				}
			}
		}
		return accept;
	}
	return true;
}
bool Clipper::ClipTriangle(std::vector<Vertex>& vertices)
{

	if (mClipping)
	{
		std::vector<Vertex> newV;
		for (int i = 0; i < (int)ClipEdge::Count; ++i)
		{
			newV.clear();
			ClipEdge edge = (ClipEdge)i;
			for (size_t n = 0; n < vertices.size(); ++n)
			{
				size_t np1 = (n + 1) % vertices.size();
				const Vertex& v1 = vertices[n];
				const Vertex& v2 = vertices[np1];
				bool isInFront_V1 = IsInFront(edge, v1.pos);
				bool isInFront_V2 = IsInFront(edge, v2.pos);

				// simplified version
				//if (isInFront_V1 != isInFront_V2)
				//{
				//	newVertices.push_back(ComputeIntersection(edge, v1, v2));
				//}
				//if (isInFront_V2)
				//{
				//	newVertices.push_back(v2);
				//}

				if (isInFront_V1 && isInFront_V2)
				{
					newV.push_back(v2);
				}
				else if (isInFront_V1 && !isInFront_V2)
				{
					newV.push_back(ComputeIntersection(edge, v1, v2));
				}
				else if (!isInFront_V1 && isInFront_V2)
				{
					newV.push_back(ComputeIntersection(edge, v1, v2));
					newV.push_back(v2);
				}
				else 
				{

				}
			}
			vertices = newV;
		}

	}
	return true;
}