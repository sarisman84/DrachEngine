#pragma once
#include <cmath>
#include "Vector.h"
namespace drach
{
	template<typename T>
	class Vector2;


	template<typename T>
	class Vector3 : public Vector
	{
	public:
		Vector3();
		Vector3(const T anX, const T anY, const T anZ);
		Vector3(const Vector2<T>& aVec2);
		Vector3(const Vector3<T>& aVector3);
		Vector3(Vector3<T>&& aVector3);
	public:
		Vector3<T> operator=(const Vector3<T>& aVector3);
		Vector3<T> operator=(Vector3<T>&& aVector3);
		Vector3<T> operator+(const Vector3<T>& aVector3);
		Vector3<T> operator+(const Vector2<T>& aVector2);
		Vector3<T> operator-(const Vector3<T>& aVector3);
		Vector3<T> operator-(const Vector2<T>& aVector2);
		Vector3<T> operator*(const Vector3<T>& aVector3);
		Vector3<T> operator*(const Vector2<T>& aVector2);
		Vector3<T> operator/(const Vector3<T>& aVector3);
		Vector3<T> operator/(const Vector2<T>& aVector2);
	public:
		void operator+=(const Vector3<T>& aVector3);
		void operator+=(const Vector2<T>& aVector2);
		void operator-=(const Vector3<T>& aVector3);
		void operator-=(const Vector2<T>& aVector2);
		void operator*=(const Vector3<T>& aVector3);
		void operator*=(const Vector2<T>& aVector2);
		void operator/=(const Vector3<T>& aVector3);
		void operator/=(const Vector2<T>& aVector2);

	public:
		static Vector3<T> Cross(const Vector3<T>& aLhs, const Vector3<T>& aRhs);
		static float Dot(const Vector3<T>& aLhs, const Vector3<T>& aRhs);
		static Vector3<T> Clamp(const Vector3<T>& aSource, const Vector3<T>& aMin, const Vector3<T>& aMax);
		static Vector3<T> ClampLength(const Vector3<T>& aSource, const float aMin, const float aMax);
		static Vector3<T> Lerp(const Vector3<T>& aSource, const Vector3<T>& aTarget, const float aPercentage);
	public:
		float Length() override;
		float RawLength() override;
		Vector3<T> GetNormalized();
		void Normalize();

	private:
		T x;
		T y;
		T z;



	};
	template<typename T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aLhs, const Vector3<T>& aRhs)
	{
		return Vector3<T>();
	}
	template<typename T>
	inline float Vector3<T>::Dot(const Vector3<T>& aLhs, const Vector3<T>& aRhs)
	{
		float lengthProduct = aLhs.Length() * aRhs.Length();
		float dot = aLhs.x * aRhs.x + aLhs.y * aRhs.y + aLhs.z * aRhs.z;
		return dot / lengthProduct;
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::Clamp(const Vector3<T>& aSource, const Vector3<T>& aMin, const Vector3<T>& aMax)
	{
		Vector3<T> result;

		result.x = aSource.x > aMax.x ? aMax.x : aSource.x < aMin.x ? aMin.x : aSource.x;
		result.y = aSource.y > aMax.y ? aMax.y : aSource.y < aMin.y ? aMin.y : aSource.y;
		result.z = aSource.z > aMax.z ? aMax.z : aSource.z < aMin.z ? aMin.z : aSource.z;

		return result;
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::ClampLength(const Vector3<T>& aSource, const float aMin, const float aMax)
	{
		Vector3<T> result = aSource;
		float length = aSource.Length();

		if (length < aMin)
			result = aSource * (aMin / length);
		else if (length > aMax)
			result = aSource * (aMax / length);

		return result;
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::Lerp(const Vector3<T>& aSource, const Vector3<T>& aTarget, const float aPercentage)
	{
		return aSource + (aTarget - aSource) * aPercentage;
	}
	template<typename T>
	inline float Vector3<T>::Length()
	{
		return std::sqrt(RawLength());
	}
	template<typename T>
	inline float Vector3<T>::RawLength()
	{
		return x * x + y * y + z * z;
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::GetNormalized()
	{
		return Vector3<T>();
	}
	template<typename T>
	inline void Vector3<T>::Normalize()
	{
	}
	template<typename T>
	inline Vector3<T>::Vector3() : x(T()), y(T()), z(T())
	{
	}
	template<typename T>
	inline Vector3<T>::Vector3(const T anX, const T anY, const T anZ) : x(anX), y(anY), z(anZ)
	{
	}
	template<typename T>
	inline Vector3<T>::Vector3(const Vector2<T>& aVec2) : x(aVec2.x), y(aVec2.y), z(T())
	{
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::operator=(const Vector3<T>& aVector3)
	{
		x = aVector3.x;
		y = aVector3.y;
		z = aVector3.z;

		return *this;
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::operator=(Vector3<T>&& aVector3)
	{
		x = aVector3.x;
		y = aVector3.y;
		z = aVector3.z;

		return *this;
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& aVector3)
	{
		return { x + aVector3.x, y + aVector3.y, z + aVector3.z };
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::operator+(const Vector2<T>& aVector2)
	{
		return { x + aVector2.x, y + aVector2.y, z };
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& aVector3)
	{
		return { x - aVector3.x, y - aVector3.y, z - aVector3.z };
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::operator-(const Vector2<T>& aVector2)
	{
		return { x - aVector2.x, y - aVector2.y, z };
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::operator*(const Vector3<T>& aVector3)
	{
		return { x * aVector3.x, y * aVector3.y, z * aVector3.z };
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::operator*(const Vector2<T>& aVector2)
	{
		return { x * aVector2.x, y * aVector2.y, z };
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::operator/(const Vector3<T>& aVector3)
	{
		return { x / aVector3.x, y / aVector3.y, z / aVector3.z };
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::operator/(const Vector2<T>& aVector2)
	{
		return { x / aVector2.x, y / aVector2.y, z };
	}
	template<typename T>
	inline void Vector3<T>::operator+=(const Vector3<T>& aVector3)
	{
		x += aVector3.x;
		y += aVector3.y;
		z += aVector3.z;
	}
	template<typename T>
	inline void Vector3<T>::operator+=(const Vector2<T>& aVector2)
	{
		x += aVector2.x;
		y += aVector2.y;
	}
	template<typename T>
	inline void Vector3<T>::operator-=(const Vector3<T>& aVector3)
	{
		x -= aVector3.x;
		y -= aVector3.y;
		z -= aVector3.z;
	}
	template<typename T>
	inline void Vector3<T>::operator-=(const Vector2<T>& aVector2)
	{
		x -= aVector2.x;
		y -= aVector2.y;
	}
	template<typename T>
	inline void Vector3<T>::operator*=(const Vector3<T>& aVector3)
	{
		x *= aVector3.x;
		y *= aVector3.y;
		z *= aVector3.z;
	}
	template<typename T>
	inline void Vector3<T>::operator*=(const Vector2<T>& aVector2)
	{
		x *= aVector2.x;
		y *= aVector2.y;
	}
	template<typename T>
	inline void Vector3<T>::operator/=(const Vector3<T>& aVector3)
	{
		x /= aVector3.x;
		y /= aVector3.y;
		z /= aVector3.z;
	}
	template<typename T>
	inline void Vector3<T>::operator/=(const Vector2<T>& aVector2)
	{
		x /= aVector2.x;
		y /= aVector2.y;
	}
}