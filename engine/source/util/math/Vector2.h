#pragma once
#include "CommonUtilities.h"
#include <cmath>
namespace drach
{
	template<typename T>
	class Vector2
	{
	public:
		Vector2();
		Vector2(const T& anX, const T& anY);
		Vector2(const Vector2<T>& anOther);
		Vector2(Vector2<T>&& anOther);
	public:
		Vector2<T> operator+(const Vector2<T>& other);
		Vector2<T> operator-(const Vector2<T>& other);
		Vector2<T> operator/(const Vector2<T>& other);
		Vector2<T> operator*(const Vector2<T>& other);
		Vector2<T> operator/(const T other);
		Vector2<T> operator*(const T other);
		Vector2<T> operator=(const Vector2<T>& other);

	public:
		void operator+=(const Vector2<T>& other);
		void operator-=(const Vector2<T>& other);
		void operator/=(const Vector2<T>& other);
		void operator*=(const Vector2<T>& other);
		void operator/=(const T other);
		void operator*=(const T other);
	public:
		const bool operator==(const Vector2<T>& anOtherVector2);
		const bool operator!=(const Vector2<T>& anOtherVector2);
	public:
		static float Dot(const Vector2<T>& aLhs, const Vector2<T>& aRhs);
		static float DotNormalized(const Vector2<T>& aLhs, const Vector2<T>& aRhs);
		static Vector2<T> Clamp(const Vector2<T>& aSource, const Vector2<T>& aMin, const Vector2<T>& aMax);
		static Vector2<T> ClampLength(const Vector2<T>& aSource, const float aMin, const float aMax);
		static Vector2<T> Lerp(const Vector2<T>& aSource, const Vector2<T>& aTarget, const float aPercentage);
	public:
		float FastLength();
		float Length();
		float SqrLength();

		Vector2<T> GetNormalized();
		void Normalize();
		Vector2<T> GetFastNormalized();
		void FastNormalize();
	public:
		T x;
		T y;
	};
	template<typename T>
	inline Vector2<T>::Vector2()
		:x(T()), y(T())
	{
	}
	template<typename T>
	inline Vector2<T>::Vector2(const T& anX, const T& anY)
		: x(anX), y(anY)
	{
	}
	template<typename T>
	inline Vector2<T>::Vector2(const Vector2<T>& anOther)
		: x(anOther.x), y(anOther.y)
	{
	}
	template<typename T>
	inline Vector2<T>::Vector2(Vector2<T>&& anOther)
		: x(std::move(anOther.x)), y(std::move(anOther.y))
	{
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& other)
	{
		Vector2<T> r;
		r.x = x + other.x;
		r.y = y + other.y;
		return r;
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::operator-(const Vector2<T>& other)
	{
		Vector2<T> r;
		r.x = x - other.x;
		r.y = y - other.y;
		return r;
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::operator/(const Vector2<T>& other)
	{
		Vector2<T> r;
		r.x = x / other.x;
		r.y = y / other.y;
		return r;
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::operator*(const Vector2<T>& other)
	{
		Vector2<T> r;
		r.x = x * other.x;
		r.y = y * other.y;
		return r;
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::operator/(const T other)
	{
		Vector2<T> r;
		r.x = x / other;
		r.y = y / other;
		return r;
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::operator*(const T other)
	{
		Vector2<T> r;
		r.x = x * other;
		r.y = y * other;
		return r;
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::operator=(const Vector2<T>& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	template<typename T>
	inline void Vector2<T>::operator+=(const Vector2<T>& other)
	{
		x = x + other.x;
		y = y + other.y;
	}
	template<typename T>
	inline void Vector2<T>::operator-=(const Vector2<T>& other)
	{
		x = x - other.x;
		y = y - other.y;
	}
	template<typename T>
	inline void Vector2<T>::operator/=(const Vector2<T>& other)
	{
		x = x / other.x;
		y = y / other.y;
	}
	template<typename T>
	inline void Vector2<T>::operator*=(const Vector2<T>& other)
	{
		x = x * other.x;
		y = y * other.y;
	}
	template<typename T>
	inline void Vector2<T>::operator/=(const T other)
	{
		x = x / other;
		y = y / other;
	}
	template<typename T>
	inline void Vector2<T>::operator*=(const T other)
	{
		x = x * other;
		y = y * other;
	}
	template<typename T>
	inline const bool Vector2<T>::operator==(const Vector2<T>& anOtherVector2)
	{
		return x == anOtherVector2.x && y == anOtherVector2.y;
	}
	template<typename T>
	inline const bool Vector2<T>::operator!=(const Vector2<T>& anOtherVector2)
	{
		return x != anOtherVector2.x && y != anOtherVector2.y;
	}
	template<typename T>
	inline float Vector2<T>::Dot(const Vector2<T>& aLhs, const Vector2<T>& aRhs)
	{
		return aLhs.x * aRhs.x + aLhs.y * aRhs.y;
	}
	template<typename T>
	inline float Vector2<T>::DotNormalized(const Vector2<T>& aLhs, const Vector2<T>& aRhs)
	{
		float lengthProduct = aLhs.Length() * aRhs.Length();
		return Dot(aLhs, aRhs) / lengthProduct;
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::Clamp(const Vector2<T>& aSource, const Vector2<T>& aMin, const Vector2<T>& aMax)
	{
		Vector2<T> r;
		r.x = aSource.x < aMin.x ? aMin.x : aSource.x > aMax.x ? aMax.x : aSource.x;
		r.y = aSource.y < aMin.y ? aMin.y : aSource.y > aMax.y ? aMax.y : aSource.y;
		return r;
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::ClampLength(const Vector2<T>& aSource, const float aMin, const float aMax)
	{
		Vector2<T> result = aSource;
		float length = aSource.Length();

		if (length < aMin)
			result = aSource * (aMin / length);
		else if (length > aMax)
			result = aSource * (aMax / length);

		return result;
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::Lerp(const Vector2<T>& aSource, const Vector2<T>& aTarget, const float aPercentage)
	{
		return aSource + (aTarget - aSource) * aPercentage;
	}
	template<typename T>
	inline float Vector2<T>::FastLength()
	{
		return 1.0f / drach::qSqrt(SqrLength());
	}
	template<typename T>
	inline float Vector2<T>::Length()
	{
		return std::sqrt(SqrLength());
	}
	template<typename T>
	inline float Vector2<T>::SqrLength()
	{
		return x * x + y * y;
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::GetNormalized()
	{
		Vector2<T> result = *this;

		float length = result.Length();

		if (length == 0)
		{
			return result;
		}

		return result / length;
	}
	template<typename T>
	inline void Vector2<T>::Normalize()
	{
		float length = Length();

		if (length == 0)
		{
			return;
		}

		x /= length;
		y /= length;
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::GetFastNormalized()
	{
		Vector2<T> result = *this;

		float length = result.FastLength();

		if (length == 0)
		{
			return result;
		}

		return result / length;
	}
	template<typename T>
	inline void Vector2<T>::FastNormalize()
	{
		float length = FastLength();

		if (length == 0)
		{
			return;
		}

		x /= length;
		y /= length;
	}

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
	typedef Vector2<uint32_t> uVector2i;
	typedef uVector2i PixelCoord;
}
