#pragma once

#include "Vertex.h"

class Model
{
public:
	void Load(const std::string& fileName);

	const std::string& GetFileName() const;
	Vertex GetVertex(int index) const;
	int GetVertexCount() const;

private:
	std::string mFileName;
	std::vector<Vertex> mVerticies;
};