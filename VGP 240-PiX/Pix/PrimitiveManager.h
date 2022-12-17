#pragma once
#include "MathHelper.h"
#include "Vertex.h"
#include <XEngine.h>
enum class Topology
{
	Point,
	Line,
	Triangle
};

enum class CullMode
{
	None,
	Front,
	Back
};

class PrimitiveManager
{
private:
	PrimitiveManager();
	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	CullMode mCullMode = CullMode::Back;
	bool mDrawBegin = false;
	bool mApplyTransform = false;
	bool mCorrectUV = false;
public:
	virtual ~PrimitiveManager();
	static PrimitiveManager* Get();

	void OnNewFrame();

	bool BeginDraw(Topology topology, bool applyTransform);
	void AddVertex(Vertex vertex);
	bool EndDraw();
	void SetCullMode(CullMode mode);
	void SetCorrectUV(bool correctUV);
};
