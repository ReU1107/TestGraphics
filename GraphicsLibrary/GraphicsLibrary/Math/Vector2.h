#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "Matrix4x4.h"

struct Vector2 : DirectX::XMFLOAT2
{
	Vector2()
		: DirectX::XMFLOAT2(0.0f, 0.0f)
	{
	}

	Vector2(float x, float y)
		: DirectX::XMFLOAT2(x, y)
	{
	}

	inline Vector2 operator+(const Vector2& other) const
	{
		Vector2 v;
		v.x = this->x + other.x;
		v.y = this->y + other.y;
		return v;
	}
	inline Vector2 operator-(const Vector2& other) const
	{
		Vector2 v;
		v.x = this->x - other.x;
		v.y = this->y - other.y;
		return v;
	}

	inline Vector2 operator*(const Vector2& other) const
	{
		Vector2 v;
		v.x = this->x * other.x;
		v.y = this->y * other.y;
		return v;
	}

	inline Vector2 operator/(const Vector2& other) const
	{
		Vector2 v;
		v.x = this->x / other.x;
		v.y = this->y / other.y;
		return v;
	}

	inline Vector2 operator+(float other) const
	{
		Vector2 v;
		v.x = this->x + other;
		v.y = this->y + other;
		return v;
	}

	inline Vector2 operator-(float other) const
	{
		Vector2 v;
		v.x = this->x - other;
		v.y = this->y - other;
		return v;
	}

	inline Vector2 operator*(float other) const
	{
		Vector2 v;
		v.x = this->x * other;
		v.y = this->y * other;
		return v;
	}

	inline Vector2 operator/(float other) const
	{
		Vector2 v;
		v.x = this->x / other;
		v.y = this->y / other;
		return v;
	}

	inline Vector2 operator+=(const Vector2& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	inline Vector2& operator-=(const Vector2& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	inline Vector2& operator*=(const Vector2& other)
	{
		this->x *= other.x;
		this->y *= other.y;
		return *this;
	}

	inline Vector2& operator/=(const Vector2& other)
	{
		this->x /= other.x;
		this->y /= other.y;
		return *this;
	}

	inline Vector2& operator+=(float other)
	{
		this->x += other;
		this->y += other;
		return *this;
	}

	inline Vector2& operator-=(float other)
	{
		this->x -= other;
		this->y -= other;
		return *this;
	}

	inline Vector2& operator*=(float other)
	{
		this->x *= other;
		this->y *= other;
		return *this;
	}

	inline Vector2& operator/=(float other)
	{
		this->x /= other;
		this->y /= other;
		return *this;
	}

	inline bool operator<(const Vector2& other)
	{
		float l = this->LengthSq();
		float r = other.LengthSq();
		// ベクトルの長さ比較(小さいなら)
		if (l < r)
		{
			return true;
		}

		return false;
	}

	inline bool operator>(const Vector2& other)
	{
		float l = this->LengthSq();
		float r = other.LengthSq();
		// ベクトルの長さ比較(大きいなら)
		if (l > r)
		{
			return true;
		}

		return false;
	}

	float LengthSq() const
	{
		return (this->x * this->x) + (this->y * this->y);
	}

	float Length() const
	{
		return sqrtf((this->x * this->x) + (this->y * this->y));
	}

};