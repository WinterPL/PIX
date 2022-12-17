#pragma once
#include "MathHelper.h"

class Camera
{
public:
	static Camera* Get();
public:
	void OnNewFrame();

	void SetPosition(Vector3 position); // CmdSetCameraPosition
	void SetDirection(Vector3 direction); // CmdSetCameraDirection
	void SetNearPlane(float nearPlane);
	void SetFarPlane(float farPlane);
	void SetFOV(float fov);

	Matrix4 GetViewMatrix() const;
	Matrix4 GetProjectionMatrix() const;

	const Vector3& GetPosition() const { return mPosition; }
	const Vector3& GetDirection() const { return mDirection; }
private:
	Vector3 mPosition; // default: 0, 0, 0
	Vector3 mDirection; // default: 0, 0, 1

	float mNearPlane; // default: 0.01
	float mFarPlane; // default: 100
	float mFOV; // default: 1.57
};
