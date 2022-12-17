#include "MatrixStack.h"


MatrixStack::MatrixStack()
{

}

MatrixStack* MatrixStack::Get()
{
	static MatrixStack sInstance;

	return &sInstance;
}

void MatrixStack::OnNewFrame()
{
	mCombinedTransform = Matrix4::Identity();
	mMatrices.clear();
}

void MatrixStack::PushTranslation(Vector3 d)
{
	// translation
	Matrix4 transMatrix = Matrix4::Translation(d);
	mMatrices.push_back(transMatrix);
	mCombinedTransform = transMatrix * mCombinedTransform;
}
void MatrixStack::PushRotationX(float radian)
{
	// rot
	Matrix4 rotMatrix = Matrix4::RotationX(radian);
	mMatrices.push_back(rotMatrix);
	mCombinedTransform = rotMatrix * mCombinedTransform;
}
void MatrixStack::PushRotationY(float radian)
{
	// rot
	Matrix4 rotMatrix = Matrix4::RotationY(radian);
	mMatrices.push_back(rotMatrix);
	mCombinedTransform = rotMatrix * mCombinedTransform;
}
void MatrixStack::PushRotationZ(float radian)
{
	// rot
	Matrix4 rotMatrix = Matrix4::RotationZ(radian);
	mMatrices.push_back(rotMatrix);
	mCombinedTransform = rotMatrix * mCombinedTransform;

}
void MatrixStack::PushScaling(Vector3 s)
{
	// rot
	Matrix4 scaleMatrix = Matrix4::Scaling(s);
	mMatrices.push_back(scaleMatrix);
	mCombinedTransform = scaleMatrix * mCombinedTransform;

}
void MatrixStack::PopMatrix()
{
	if (!mMatrices.empty())
	{
		auto matrix = mMatrices.back();
		mMatrices.pop_back();
		mCombinedTransform = MathHelper::Inverse(matrix) * mCombinedTransform;
	}
}