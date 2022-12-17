#pragma once

struct Vector2
{
	float x, y;

	constexpr Vector2() noexcept : x(0.0f), y(0.0f) {}
	constexpr Vector2(float x, float y) noexcept : x(x), y(y) {}

	~Vector2() {};

	Vector2 operator-() const { return { -x, -y }; }

	Vector2 operator+(Vector2 b) const { return { x + b.x, y + b.y }; }
	Vector2 operator-(Vector2 b) const { return { x - b.x, y - b.y }; }
	Vector2 operator*(float s) const { return { x * s, y * s }; }
	//Vector2 operator/(float s) { x/s; y/s; return *this; }

	Vector2& operator/=(float s) { x /= s; y /= s; return *this; }
};
