#pragma once

#include <XEngine.h>

enum class AddressMode
{
	Clamp,
	Wrap
};

class Texture // Only loads 24-bit BMPs
{
public:
	void Load(const std::string& fileName);

	const std::string& GetFileName() const;

	X::Color GetPixel(float u, float v, AddressMode mode) const;

private:
	std::string mFileName;
	std::unique_ptr<X::Color[]> mPixels;
	int mWidth = 0;
	int mHeight = 0;
};