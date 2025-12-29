#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct Vector3
	{
		float X;
		float Y;
		float Z;

		Vector3 operator+(const Vector3& other) const
		{
			return Vector3{ X + other.X, Y + other.Y, Z + other.Z };
		}

		Vector3 operator-(const Vector3& other) const
		{
			return Vector3{ X - other.X, Y - other.Y, Z - other.Z };
		}

		Vector3 operator*(const Vector3& other) const
		{
			return Vector3{ X * other.X, Y * other.Y, Z * other.Z };
		}

		Vector3 operator/(const Vector3& other) const
		{
			return Vector3{ X / other.X, Y / other.Y, Z / other.Z };
		}

		Vector3 operator+=(const Vector3& other)
		{
			X += other.X;
			Y += other.Y;
			Z += other.Z;
			return *this;
		}

		Vector3 operator-=(const Vector3& other)
		{
			X -= other.X;
			Y -= other.Y;
			Z -= other.Z;
			return *this;
		}

		Vector3 operator*=(const Vector3& other)
		{
			X *= other.X;
			Y *= other.Y;
			Z *= other.Z;
			return *this;
		}

		Vector3 operator/=(const Vector3& other)
		{
			X /= other.X;
			Y /= other.Y;
			Z /= other.Z;
			return *this;
		}

		Vector3 operator*=(const float& other)
		{
			X *= other;
			Y *= other;
			Z *= other;
			return *this;
		}

		Vector3 operator/=(const float& other)
		{
			X /= other;
			Y /= other;
			Z /= other;
			return *this;
		}
	};

	struct Vector3__Boxed 
	{
		struct Vector3__Class* klass;
		MonitorData* monitor;
		struct Vector3 fields;
	};
}
