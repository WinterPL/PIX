#include "Graphics.h"

#include "DepthBuffer.h"
#include "MaterialManager.h"
#include "Viewport.h"
#include "Camera.h"
#include "MatrixStack.h"
#include "LightManager.h"
#include "PrimitiveManager.h"

void Graphics::NewFrame()
{
	DepthBuffer::Get()->OnNewFrame();
	MaterialManager::Get()->OnNewFrame();
	Viewport::Get()->OnNewFrame();
	Camera::Get()->OnNewFrame();
	MatrixStack::Get()->OnNewFrame();
	LightManager::Get()->OnNewFrame();
	PrimitiveManager::Get()->OnNewFrame();
}