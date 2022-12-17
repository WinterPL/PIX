#include "RayTracer.h"

#include "Camera.h"
#include <cmath>

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	// Source: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
	void Fresnel(Vector3 i, Vector3 n, float refractionIndex, float& kr, float& kt)
	{
		float cosi = X::Math::Clamp(-1.0f, 1.0f, MathHelper::Dot(i, n));
		float etai = 1, etat = refractionIndex;
		if (cosi > 0)
			std::swap(etai, etat);

		// Compute sini using Snell's law
		float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));

		// Total internal reflection
		kr = 1.0f;
		if (sint < 1)
		{
			float cost = sqrtf(std::max(0.f, 1 - sint * sint));
			cosi = fabsf(cosi);
			float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
			float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
			kr = (Rs * Rs + Rp * Rp) / 2;
		}

		// As a consequence of the conservation of energy, transmittance is given by:
		kt = 1 - kr;
	}
}

RayTracer* RayTracer::Get()
{
	static RayTracer sInstance;
	return &sInstance;
}

void RayTracer::OnNewFrame()
{
	mObjects.clear();
	mLights.clear();
}

bool RayTracer::BeginDraw()
{
	return true;
}

void RayTracer::AddObject(Sphere sphere, X::Color color, float ri)
{
	mObjects.push_back({ sphere, color, ri });
}

void RayTracer::AddLight(Vector3 position, X::Color color)
{
	mLights.push_back({ position, color });
}

bool RayTracer::EndDraw()
{
	auto camera = Camera::Get();

	int columns = static_cast<int>(gResolutionX);
	int rows = static_cast<int>(gResolutionY);

	Matrix4 matView = camera->GetViewMatrix();
	Vector3 camPos = camera->GetPosition();
	float aspect = (float)columns / (float)rows;

	Vector3 screenCenter = camPos + camera->GetDirection();
	Vector3 xAxis = { matView._11, matView._21, matView._31 };
	Vector3 yAxis = { matView._12, matView._22, matView._32 };
	Vector3 p0 = screenCenter - (xAxis * aspect) + yAxis;
	Vector3 p1 = screenCenter + (xAxis * aspect) + yAxis;
	Vector3 p2 = screenCenter - (xAxis * aspect) - yAxis;

	//    p0 +---------------+ p1
	//       |               |
	//       |       +       |
	//       |               |
	//    p2 +---------------+

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			float u = (float)x / columns;
			float v = (float)y / rows;
			Vector3 pointOnScreen = p0 + (p1 - p0) * u + (p2 - p0) * v;

			Ray primaryRay;
			primaryRay.origin = camPos;
			primaryRay.direction = MathHelper::Normalize(pointOnScreen - camPos);
			X::DrawPixel(x, y, Trace(primaryRay, 3));
		}
	}

	return true;
}

X::Color RayTracer::Trace(Ray ray, int depth)
{
	// If we reached our recursion depth, we are done
	if (depth <= 0)
		return X::Colors::Black;

	Object* objHit = nullptr;
	float closestDistance = FLT_MAX;
	X::Color closestColor;
	Vector3 closestPoint;
	Vector3 closestNormal;

	for (auto& obj : mObjects)
	{
		float distanceToSphere;
		if (MathHelper::Intersect(ray, obj.sphere, distanceToSphere))
		{
			if (distanceToSphere >= 0 && distanceToSphere < closestDistance)
			{
				objHit = &obj;
				closestDistance = distanceToSphere;
				closestColor = obj.color;
				closestPoint = ray.origin + (ray.direction * distanceToSphere);
				closestNormal = MathHelper::Normalize(closestPoint - obj.sphere.center);
			}
		}
	}

	// If ray is not hitting anything, there is no more color contribution
	if (objHit == nullptr)
		return X::Colors::Black;

	X::Color color;

	// If object is opaque, compute illumination from light
	if (objHit->IsOpaque())
	{
		for (auto& light : mLights)
		{
			float distanceToLight = MathHelper::Magnitude(light.position - closestPoint);
			Vector3 dirToLight = (light.position - closestPoint) / distanceToLight;

			bool occluded = false;
			for (auto& obj : mObjects)
			{
				Ray shadowRay;
				shadowRay.origin = closestPoint + (closestNormal * 0.001f);
				shadowRay.direction = dirToLight;

				float distanceToObj;
				if (MathHelper::Intersect(shadowRay, obj.sphere, distanceToObj) &&
					distanceToObj > 0.0f && distanceToObj + 0.1f < distanceToLight)
				{
					occluded = true;
					break;
				}
			}

			float intensity = mAmbient;
			if (!occluded)
			{
				float diffuse = MathHelper::Dot(dirToLight, closestNormal);
				if (diffuse > 0.0f)
				{
					float atten = 1.0f / (light.attenC + (light.attenL * distanceToLight) + (light.attenQ * distanceToLight * distanceToLight));
					intensity = X::Math::Clamp(intensity + (diffuse * atten), 0.0f, 1.0f);
				}
			}

			color += light.color * closestColor * intensity;
		}
	}
	// If object is transparent, compute reflection and refraction
	else
	{
		// For transparent objects, we may be casting ray from within the object
		bool inside = false;
		if (MathHelper::Dot(ray.direction, closestNormal) > 0)
		{
			inside = true;
			closestNormal = -closestNormal;
		}

		Ray reflectRay;
		reflectRay.origin = closestPoint + (closestNormal * 0.001f);
		reflectRay.direction = ray.direction - (closestNormal * 2.0f * MathHelper::Dot(ray.direction, closestNormal));
		X::Color reflectColor = Trace(reflectRay, depth - 1);

		float eta = inside ? objHit->refractionIndex : 1.0f / objHit->refractionIndex;
		float cosi = -MathHelper::Dot(ray.direction, closestNormal);
		float k = 1 - eta * eta * (1 - cosi * cosi);
		Ray refractRay;
		refractRay.origin = closestPoint - (closestNormal * 0.001f);
		refractRay.direction = MathHelper::Normalize(ray.direction * eta + closestNormal * (eta * cosi - sqrt(k)));
		X::Color refractColor = Trace(refractRay, depth - 1);

		float kr, kt;
		Fresnel(ray.direction, closestNormal, objHit->refractionIndex, kr, kt);

		color = closestColor * (reflectColor * kr + refractColor * kt);
	}

	color.r = X::Math::Clamp(color.r, 0.0f, 1.0f);
	color.g = X::Math::Clamp(color.g, 0.0f, 1.0f);
	color.b = X::Math::Clamp(color.b, 0.0f, 1.0f);
	return color;
}