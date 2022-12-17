#pragma once
#include "Vertex.h"

class Clipper
{
public:
	static Clipper* Get();
public:
	virtual ~Clipper();
	void OnNewFrame(); // Call this in Graphics::NewFrame()

	// Return true if clip test pass
	bool ClipPoint(const Vertex& v);
	bool ClipLine(Vertex& v1, Vertex& v2);
	bool ClipTriangle(std::vector<Vertex>& vertices);

	bool IsClipping() const { return mClipping; }
	void SetClipping(bool clip) { mClipping = clip; }

private:
	Clipper();
	bool mClipping = false;
};

