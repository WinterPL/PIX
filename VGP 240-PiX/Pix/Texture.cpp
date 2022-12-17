#include "Texture.h"

namespace
{
#pragma pack(push, 1)
	struct BitmapFileHeader
	{
		uint16_t type;			// Magic identifier
		uint32_t size;			// File size in bytes
		uint16_t reserved1;
		uint16_t reserved2;
		uint32_t offset;		// Byte offset to image data
	};

	struct BitmapInfoHeader
	{
		uint32_t size;					// Header size in bytes
		int width, height;				// Width and height of image
		uint16_t planes;				// Number of colour planes
		uint16_t bits;					// Bits per pixel
		uint32_t compression;			// Compression type
		uint32_t imageSize;				// Image size in bytes
		int xResolution, yResolution;	// Pixels per meter
		uint32_t numColors;				// Number of colours
		uint32_t importantColors;		// Important colours
	};

	// Add 1 to the row_stride until it is divisible with align_stride
	uint32_t MakeStrideAligned(uint32_t rowStride, uint32_t alignStride)
	{
		uint32_t newStride = rowStride;
		while (newStride % alignStride != 0) {
			newStride++;
		}
		return newStride;
	}
#pragma pack(pop)
}

void Texture::Load(const std::string& fileName)
{
	mFileName = fileName;

	FILE* file = nullptr;
	fopen_s(&file, fileName.c_str(), "rb");
	if (file == nullptr)
		return;

	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;
	fread(&fileHeader, sizeof(fileHeader), 1, file);
	fread(&infoHeader, sizeof(infoHeader), 1, file);

	if (infoHeader.bits != 24)
	{
		fclose(file);
		return;
	}

	mWidth = infoHeader.width;
	mHeight = infoHeader.height;
	mPixels = std::make_unique<X::Color[]>(mWidth * mHeight);

	fseek(file, fileHeader.offset, SEEK_SET);

	uint32_t rowStride = mWidth * infoHeader.bits / 8;
	uint32_t paddedStride = MakeStrideAligned(rowStride, 4);
	std::vector<uint8_t> paddingBytes(paddedStride - rowStride);

	for (int j = 0; j < mHeight; ++j)
	{
		for (int i = 0; i < mWidth; ++i)
		{
			uint8_t r, g, b;
			fread(&b, sizeof(uint8_t), 1, file);
			fread(&g, sizeof(uint8_t), 1, file);
			fread(&r, sizeof(uint8_t), 1, file);
			uint32_t index = i + ((mHeight - j - 1) * mWidth);
			mPixels[index] = { r / 255.0f, g / 255.0f, b / 255.0f, 1.0f };
		}
		fread((char*)paddingBytes.data(), paddingBytes.size(), 1, file);
	}

	fclose(file);
}

const std::string& Texture::GetFileName() const
{
	return mFileName;
}

X::Color Texture::GetPixel(float u, float v, AddressMode mode) const
{
	int uIndex = static_cast<int>(u * (mWidth - 1));
	int vIndex = static_cast<int>(v * (mHeight - 1));
	switch (mode)
	{
	case AddressMode::Clamp:
	{
		uIndex = std::clamp(uIndex, 0, mWidth - 1);
		vIndex = std::clamp(vIndex, 0, mHeight - 1);
	}
	break;
	case AddressMode::Wrap:
	{
		uIndex = uIndex % mWidth;
		vIndex = vIndex % mHeight;
	}
	break;
	}
	return mPixels[uIndex + (vIndex * mWidth)];
}