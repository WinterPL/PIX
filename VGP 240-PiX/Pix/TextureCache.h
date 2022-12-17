#pragma once

#include "Texture.h"

class TextureCache
{
public:
	static TextureCache* Get();

public:
	void Clear();

	void SetTexture(const std::string& fileName);
	void SetAddressMode(AddressMode mode);

	X::Color SampleColor(X::Color uv) const;

private:
	std::vector<std::unique_ptr<Texture>> mTextures;
	const Texture* mCurrentTexture = nullptr;
	AddressMode mAddressMode = AddressMode::Clamp;
};
