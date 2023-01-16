#pragma once

template<typename T>
class Vector2
{
public:
	Vector2(const T x, const T y)
	{
		this->x = x;
		this->y = y;
	}
	Vector2(const Vector2<T>& other)
	{
		this->x = other.x;
		this->y = other.y;
	}
	Vector2<T> operator+(const Vector2<T>& other)
	{
		Vector2<T> result;
		result.x += other.x;
		result.y += other.y;
		return result;
	}
	Vector2<T> operator-(const Vector2<T>& other)
	{
		Vector2<T> result;
		result.x -= other.x;
		result.y -= other.y;
		return result;
	}
	Vector2<T> operator/(const Vector2<T>& other)
	{
		Vector2<T> result;
		result.x /= other.x;
		result.y /= other.y;
		return result;
	}
	Vector2<T> operator*(const Vector2<T>& other)
	{
		Vector2<T> result;
		result.x *= other.x;
		result.y *= other.y;
		return result;
	}
	Vector2<T> operator/(const T other)
	{
		Vector2<T> result;
		result.x /= other;
		result.y /= other;
		return result;
	}
	Vector2<T> operator*(const T other)
	{
		Vector2<T> result;
		result.x *= other;
		result.y *= other;
		return result;
	}
	void operator+=(const Vector2<T>& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(const Vector2<T>& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator/=(const Vector2<T>& other)
	{
		x /= other.x;
		y /= other.y;
	}

	void operator*=(const Vector2<T>& other)
	{
		x *= other.x;
		y *= other.y;
	}


	void operator/=(const T other)
	{
		x /= other;
		y /= other;
	}
	void operator*=(const T other)
	{
		x *= other;
		y *= other;
	}
public:
	T x;
	T y;
};