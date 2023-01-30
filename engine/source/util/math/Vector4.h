#pragma once
#include "CommonUtilities.h"
#include "Vector3.h"
namespace drach
{
	template<typename T>
	class Vector4
	{
	public:
		Vector4();
		Vector4(const T& anX, const T& anY, const T& anZ, const T& anW);
		Vector4(const Vector3<T>& aVector3);
		Vector4(const Vector4<T>& aVector4);
		Vector4(Vector4<T>&& aVector4);
	public:
		Vector4<T> operator=(const Vector4<T>& aVector4);
		Vector4<T> operator=(Vector4<T>&& aVector4);
		Vector4<T> operator+(const Vector4<T>& aVector4);
		Vector4<T> operator+(const Vector3<T>& aVector3);
		Vector4<T> operator-(const Vector4<T>& aVector4);
		Vector4<T> operator-(const Vector3<T>& aVector3);
		Vector4<T> operator*(const Vector4<T>& aVector4);
		Vector4<T> operator*(const Vector3<T>& aVector3);
		Vector4<T> operator/(const Vector4<T>& aVector4);
		Vector4<T> operator/(const Vector3<T>& aVector3);
		Vector4<T> operator*(const T& aVal);
		Vector4<T> operator/(const T& aVal);
	public:
		const bool operator==(const Vector4<T>& anOtherVector4);
		const bool operator!=(const Vector4<T>& anOtherVector4);
	public:
		void operator+=(const Vector4<T>& aVector4);
		void operator+=(const Vector3<T>& aVector3);
		void operator-=(const Vector4<T>& aVector4);
		void operator-=(const Vector3<T>& aVector3);
		void operator*=(const Vector4<T>& aVector4);
		void operator*=(const Vector3<T>& aVector3);
		void operator/=(const Vector4<T>& aVector4);
		void operator/=(const Vector3<T>& aVector3);
	public:
		static float Dot(const Vector4<T>& aLhs, const Vector4<T>& aRhs);
		static float DotNormalized(const Vector4<T>& aLhs, const Vector4<T>& aRhs);
		static Vector4<T> Clamp(const Vector4<T>& aSource, const Vector4<T>& aMin, const Vector4<T>& aMax);
		static Vector4<T> ClampLength(const Vector4<T>& aSource, const float aMin, const float aMax);
		static Vector4<T> Lerp(const Vector4<T>& aSource, const Vector4<T>& aTarget, const float aPercentage);
	public:
		float FastLength();
		float Length();
		float SqrLength();

		Vector4<T> GetNormalized();
		void Normalize();
		Vector4<T> GetFastNormalized();
		void FastNormalize();
	public:
		T x;
		T y;
		T z;
		T w;
	};
	template<typename T>
	inline Vector4<T>::Vector4() : x(T()), y(T()), z(T()), w(T())
	{
	}
	template<typename T>
	inline Vector4<T>::Vector4(const T& anX, const T& anY, const T& anZ, const T& anW)
		: x(anX), y(anY), z(anZ), w(anW)
	{
	}
	template<typename T>
	inline Vector4<T>::Vector4(const Vector3<T>& aVector3)
		: x(aVector3.x), y(aVector3.y), z(aVector3.z), w(T())
	{
	}
	template<typename T>
	inline Vector4<T>::Vector4(const Vector4<T>& aVector4)
		: x(aVector4.x), y(aVector4.y), z(aVector4.z), w(aVector4.w)
	{
	}
	template<typename T>
	inline Vector4<T>::Vector4(Vector4<T>&& aVector4)
		: x(std::move(aVector4.x)), y(std::move(aVector4.y)), z(std::move(aVector4.z)), w(std::move(aVector4.w))
	{
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::operator=(const Vector4<T>& aVector4)
	{
		x = aVector4.x;
		y = aVector4.y;
		z = aVector4.z;
		w = aVector4.w;
		return *this;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::operator=(Vector4<T>&& aVector4)
	{
		x = std::move(aVector4.x);
		y = std::move(aVector4.y);
		z = std::move(aVector4.z);
		w = std::move(aVector4.w);
		return *this;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::operator+(const Vector4<T>& aVector4)
	{
		Vector4<T> r;
		r.x = x + aVector4.x;
		r.y = y + aVector4.y;
		r.z = z + aVector4.z;
		r.w = w + aVector4.w;
		return r;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::operator+(const Vector3<T>& aVector3)
	{
		Vector4<T> r;
		r.x = x + aVector3.x;
		r.y = y + aVector3.y;
		r.z = z + aVector3.z;

		return r;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::operator-(const Vector4<T>& aVector4)
	{
		Vector4<T> r;
		r.x = x - aVector4.x;
		r.y = y - aVector4.y;
		r.z = z - aVector4.z;
		r.w = w - aVector4.w;
		return r;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::operator-(const Vector3<T>& aVector3)
	{
		Vector4<T> r;
		r.x = x - aVector3.x;
		r.y = y - aVector3.y;
		r.z = z - aVector3.z;
		return r;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::operator*(const Vector4<T>& aVector4)
	{
		Vector4<T> r;
		r.x = x * aVector4.x;
		r.y = y * aVector4.y;
		r.z = z * aVector4.z;
		r.w = w * aVector4.w;
		return r;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::operator*(const Vector3<T>& aVector3)
	{
		Vector4<T> r;
		r.x = x * aVector3.x;
		r.y = y * aVector3.y;
		r.z = z * aVector3.z;

		return r;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::operator/(const Vector4<T>& aVector4)
	{
		Vector4<T> r;
		r.x = x / aVector4.x;
		r.y = y / aVector4.y;
		r.z = z / aVector4.z;
		r.w = w / aVector4.w;
		return r;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::operator/(const Vector3<T>& aVector3)
	{
		Vector4<T> r;
		r.x = x / aVector3.x;
		r.y = y / aVector3.y;
		r.z = z / aVector3.z;

		return r;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::operator*(const T& aVal)
	{
		Vector4<T> r;
		r.x = x * aVal;
		r.y = y * aVal;
		r.z = z * aVal;
		r.w = w * aVal;
		return r;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::operator/(const T& aVal)
	{
		Vector4<T> r;
		r.x = x / aVal;
		r.y = y / aVal;
		r.z = z / aVal;
		r.w = w / aVal;
		return r;
	}
	template<typename T>
	inline const bool Vector4<T>::operator==(const Vector4<T>& anOtherVector4)
	{
		return x == anOtherVector4.x && y == anOtherVector4.y && z == anOtherVector4.z && w == anOtherVector4.w;
	}
	template<typename T>
	inline const bool Vector4<T>::operator!=(const Vector4<T>& anOtherVector4)
	{
		return x != anOtherVector4.x && y != anOtherVector4.y && z != anOtherVector4.z && w != anOtherVector4.w;;
	}
	template<typename T>
	inline void Vector4<T>::operator+=(const Vector4<T>& aVector4)
	{
		x += aVector4.x;
		y += aVector4.y;
		z += aVector4.z;
		w += aVector4.w;

	}
	template<typename T>
	inline void Vector4<T>::operator+=(const Vector3<T>& aVector3)
	{
		x += aVector3.x;
		y += aVector3.y;
		z += aVector3.z;
	}
	template<typename T>
	inline void Vector4<T>::operator-=(const Vector4<T>& aVector4)
	{
		x -= aVector4.x;
		y -= aVector4.y;
		z -= aVector4.z;
		w -= aVector4.w;
	}
	template<typename T>
	inline void Vector4<T>::operator-=(const Vector3<T>& aVector3)
	{
		x -= aVector3.x;
		y -= aVector3.y;
		z -= aVector3.z;
	}
	template<typename T>
	inline void Vector4<T>::operator*=(const Vector4<T>& aVector4)
	{
		x *= aVector4.x;
		y *= aVector4.y;
		z *= aVector4.z;
		w *= aVector4.w;
	}
	template<typename T>
	inline void Vector4<T>::operator*=(const Vector3<T>& aVector3)
	{
		x *= aVector3.x;
		y *= aVector3.y;
		z *= aVector3.z;

	}
	template<typename T>
	inline void Vector4<T>::operator/=(const Vector4<T>& aVector4)
	{
		x /= aVector4.x;
		y /= aVector4.y;
		z /= aVector4.z;
		w /= aVector4.w;
	}
	template<typename T>
	inline void Vector4<T>::operator/=(const Vector3<T>& aVector3)
	{
		x /= aVector3.x;
		y /= aVector3.y;
		z /= aVector3.z;

	}
	template<typename T>
	inline float Vector4<T>::Dot(const Vector4<T>& aLhs, const Vector4<T>& aRhs)
	{
		return aLhs.x * aRhs.x + aLhs.y * aRhs.y + aLhs.z * aRhs.z + aLhs.w * aRhs.w;
	}
	template<typename T>
	inline float Vector4<T>::DotNormalized(const Vector4<T>& aLhs, const Vector4<T>& aRhs)
	{
		float lengthProduct = aLhs.Length() * aRhs.Length();
		return Dot(aLhs, aRhs) / lengthProduct;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::Clamp(const Vector4<T>& aSource, const Vector4<T>& aMin, const Vector4<T>& aMax)
	{
		Vector4<T> result;

		result.x = aSource.x > aMax.x ? aMax.x : aSource.x < aMin.x ? aMin.x : aSource.x;
		result.y = aSource.y > aMax.y ? aMax.y : aSource.y < aMin.y ? aMin.y : aSource.y;
		result.z = aSource.z > aMax.z ? aMax.z : aSource.z < aMin.z ? aMin.z : aSource.z;
		result.w = aSource.w > aMax.w ? aMax.w : aSource.w < aMin.w ? aMin.w : aSource.w;

		return result;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::ClampLength(const Vector4<T>& aSource, const float aMin, const float aMax)
	{
		Vector4<T> result = aSource;
		float length = aSource.Length();

		if (length < aMin)
			result = aSource * (aMin / length);
		else if (length > aMax)
			result = aSource * (aMax / length);

		return result;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::Lerp(const Vector4<T>& aSource, const Vector4<T>& aTarget, const float aPercentage)
	{
		return aSource + (aTarget - aSource) * aPercentage;
	}
	template<typename T>
	inline float Vector4<T>::FastLength()
	{
		return 1.0f / drach::qSqrt(SqrLength());
	}
	template<typename T>
	inline float Vector4<T>::Length()
	{
		return std::sqrt(SqrLength());
	}
	template<typename T>
	inline float Vector4<T>::SqrLength()
	{
		return x * x + y * y + z * z + w * w;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::GetNormalized()
	{
		Vector4<T> result = *this;

		float length = result.Length();

		if (length == 0)
		{
			return result;
		}

		return result / length;
	}
	template<typename T>
	inline void Vector4<T>::Normalize()
	{
		float length = Length();

		if (length == 0)
		{
			return;
		}

		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::GetFastNormalized()
	{
		Vector4<T> result = *this;

		float length = result.FastLength();

		if (length == 0)
		{
			return result;
		}

		return result / length;
	}
	template<typename T>
	inline void Vector4<T>::FastNormalize()
	{
		float length = FastLength();

		if (length == 0)
		{
			return;
		}

		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}


	typedef Vector4<float> Vector4f;
	typedef Vector4<int> Vector4i;
	typedef Vector4<uint32_t> uVector4i;
}