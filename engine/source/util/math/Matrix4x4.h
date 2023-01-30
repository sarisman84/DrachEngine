#pragma once
#include "CommonUtilities.h"
#include "Vector4.h"
#include "Vector3.h"

#include <cassert>

namespace drach
{
	enum class RotationAxis
	{
		X, Y, Z
	};
	template<typename T>
	class Matrix4x4
	{
		union
		{
			Vector4<T> myRows[4];
			T myData[16];
			T myArray[4][4];
		};
	public:
		Matrix4x4();
		Matrix4x4(const T someData[16]);
		Matrix4x4(const Vector4<T> someRows[4]);
		Matrix4x4(const Matrix4x4<T>& aMatrix);
		Matrix4x4(Matrix4x4<T>&& aMatrix);
	public:
		Matrix4x4<T> operator+(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T> operator-(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T> operator/(const Matrix4x4<T>& aMatrix);
	public:
		void operator+=(const Matrix4x4<T>& aMatrix);
		void operator-=(const Matrix4x4<T>& aMatrix);
		void operator*=(const Matrix4x4<T>& aMatrix);
		void operator/=(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T> operator=(const Matrix4x4<T>& aMatrix);
	public:
		const bool operator==(const Matrix4x4<T>& aMatrix);
		const bool operator!=(const Matrix4x4<T>& aMatrix);
	public:
		static void Decompose(const Matrix4x4<T>& aMatrix, Vector3<T>& aPos, Vector3<T>& aRot, Vector3<T>& aSize);
		static Matrix4x4<T> TRS(const Vector3<T>& aPos, const Vector3<T>& aRot, const Vector3<T>& aSize);
	public:
		Vector3<T> Forward();
		Vector3<T> Up();
		Vector3<T> Right();

		void SetPosition(const Vector3<T>& aVector3);
		void SetSize(const Vector3<T>& aVector3);
		void SetRotation(const Vector3<T>& aVector3);
		void ResetRotation();

		Vector3<T> GetPosition();
		Vector3<T> GetSize();
		Vector3<T> GetRotation();

	public:
		static T Determinant(const Matrix4x4<T>& aMatrix);
		static Matrix4x4<T> Transpose(const Matrix4x4<T>& aMatrix);
		static Matrix4x4<T> GetInverse(const Matrix4x4<T>& aMatrix);
		static Matrix4x4<T> GetInverse(const Matrix4x4<T>& aMatrix, const T& aDeterminant);
		static Matrix4x4<T> GetFastInverse(const Matrix4x4<T>& aMatrix);

		static Matrix4x4<T> CreateTranslateMatrix(const Vector3<T>& aPos);
		static Matrix4x4<T> CreateRotationMatrix(const RotationAxis& anAxis, const T someValueInRadians);
		static Matrix4x4<T> CreateRotationMatrix(const Vector3<T>& aPichYawRoll);
		static Matrix4x4<T> CreateScaleMatrix(const Vector3<T>& aScale);

	public:
		T& operator()(const uint32_t aRow, const uint32_t aCollum);
		Vector4<T>& GetRow(const uint32_t anIndex);
	};



	template<typename T>
	inline T Matrix4x4<T>::Determinant(const Matrix4x4<T>& aMatrix)
	{
		return
			aMatrix.myArray[0][3] * aMatrix.myArray[1][2] * aMatrix.myArray[2][1] * aMatrix.myArray[3][0] - aMatrix.myArray[0][2] * aMatrix.myArray[1][3] * aMatrix.myArray[2][1] * aMatrix.myArray[3][0] -
			aMatrix.myArray[0][3] * aMatrix.myArray[1][1] * aMatrix.myArray[2][2] * aMatrix.myArray[3][0] + aMatrix.myArray[0][1] * aMatrix.myArray[1][3] * aMatrix.myArray[2][2] * aMatrix.myArray[3][0] +
			aMatrix.myArray[0][2] * aMatrix.myArray[1][1] * aMatrix.myArray[2][3] * aMatrix.myArray[3][0] - aMatrix.myArray[0][1] * aMatrix.myArray[1][2] * aMatrix.myArray[2][3] * aMatrix.myArray[3][0] -
			aMatrix.myArray[0][3] * aMatrix.myArray[1][2] * aMatrix.myArray[2][0] * aMatrix.myArray[3][1] + aMatrix.myArray[0][2] * aMatrix.myArray[1][3] * aMatrix.myArray[2][0] * aMatrix.myArray[3][1] +
			aMatrix.myArray[0][3] * aMatrix.myArray[1][0] * aMatrix.myArray[2][2] * aMatrix.myArray[3][1] - aMatrix.myArray[0][0] * aMatrix.myArray[1][3] * aMatrix.myArray[2][2] * aMatrix.myArray[3][1] -
			aMatrix.myArray[0][2] * aMatrix.myArray[1][0] * aMatrix.myArray[2][3] * aMatrix.myArray[3][1] + aMatrix.myArray[0][0] * aMatrix.myArray[1][2] * aMatrix.myArray[2][3] * aMatrix.myArray[3][1] +
			aMatrix.myArray[0][3] * aMatrix.myArray[1][1] * aMatrix.myArray[2][0] * aMatrix.myArray[3][2] - aMatrix.myArray[0][1] * aMatrix.myArray[1][3] * aMatrix.myArray[2][0] * aMatrix.myArray[3][2] -
			aMatrix.myArray[0][3] * aMatrix.myArray[1][0] * aMatrix.myArray[2][1] * aMatrix.myArray[3][2] + aMatrix.myArray[0][0] * aMatrix.myArray[1][3] * aMatrix.myArray[2][1] * aMatrix.myArray[3][2] +
			aMatrix.myArray[0][1] * aMatrix.myArray[1][0] * aMatrix.myArray[2][3] * aMatrix.myArray[3][2] - aMatrix.myArray[0][0] * aMatrix.myArray[1][1] * aMatrix.myArray[2][3] * aMatrix.myArray[3][2] -
			aMatrix.myArray[0][2] * aMatrix.myArray[1][1] * aMatrix.myArray[2][0] * aMatrix.myArray[3][3] + aMatrix.myArray[0][1] * aMatrix.myArray[1][2] * aMatrix.myArray[2][0] * aMatrix.myArray[3][3] +
			aMatrix.myArray[0][2] * aMatrix.myArray[1][0] * aMatrix.myArray[2][1] * aMatrix.myArray[3][3] - aMatrix.myArray[0][0] * aMatrix.myArray[1][2] * aMatrix.myArray[2][1] * aMatrix.myArray[3][3] -
			aMatrix.myArray[0][1] * aMatrix.myArray[1][0] * aMatrix.myArray[2][2] * aMatrix.myArray[3][3] + aMatrix.myArray[0][0] * aMatrix.myArray[1][1] * aMatrix.myArray[2][2] * aMatrix.myArray[3][3];
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::Transpose(const Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T> r;
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				r.myData[j][i] = aMatrix.myData[i][j];
			}
		}

		return r;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::GetInverse(const Matrix4x4<T>& aMatrix)
	{
		T inv[16];

		inv[0] =
			aMatrix.myData[5] * aMatrix.myData[10] * aMatrix.myData[15] -
			aMatrix.myData[5] * aMatrix.myData[11] * aMatrix.myData[14] -
			aMatrix.myData[9] * aMatrix.myData[6] * aMatrix.myData[15] +
			aMatrix.myData[9] * aMatrix.myData[7] * aMatrix.myData[14] +
			aMatrix.myData[13] * aMatrix.myData[6] * aMatrix.myData[11] -
			aMatrix.myData[13] * aMatrix.myData[7] * aMatrix.myData[10];

		inv[4] = -aMatrix.myData[4] * aMatrix.myData[10] * aMatrix.myData[15] +
			aMatrix.myData[4] * aMatrix.myData[11] * aMatrix.myData[14] +
			aMatrix.myData[8] * aMatrix.myData[6] * aMatrix.myData[15] -
			aMatrix.myData[8] * aMatrix.myData[7] * aMatrix.myData[14] -
			aMatrix.myData[12] * aMatrix.myData[6] * aMatrix.myData[11] +
			aMatrix.myData[12] * aMatrix.myData[7] * aMatrix.myData[10];

		inv[8] = aMatrix.myData[4] * aMatrix.myData[9] * aMatrix.myData[15] -
			aMatrix.myData[4] * aMatrix.myData[11] * aMatrix.myData[13] -
			aMatrix.myData[8] * aMatrix.myData[5] * aMatrix.myData[15] +
			aMatrix.myData[8] * aMatrix.myData[7] * aMatrix.myData[13] +
			aMatrix.myData[12] * aMatrix.myData[5] * aMatrix.myData[11] -
			aMatrix.myData[12] * aMatrix.myData[7] * aMatrix.myData[9];

		inv[12] = -aMatrix.myData[4] * aMatrix.myData[9] * aMatrix.myData[14] +
			aMatrix.myData[4] * aMatrix.myData[10] * aMatrix.myData[13] +
			aMatrix.myData[8] * aMatrix.myData[5] * aMatrix.myData[14] -
			aMatrix.myData[8] * aMatrix.myData[6] * aMatrix.myData[13] -
			aMatrix.myData[12] * aMatrix.myData[5] * aMatrix.myData[10] +
			aMatrix.myData[12] * aMatrix.myData[6] * aMatrix.myData[9];

		inv[1] = -aMatrix.myData[1] * aMatrix.myData[10] * aMatrix.myData[15] +
			aMatrix.myData[1] * aMatrix.myData[11] * aMatrix.myData[14] +
			aMatrix.myData[9] * aMatrix.myData[2] * aMatrix.myData[15] -
			aMatrix.myData[9] * aMatrix.myData[3] * aMatrix.myData[14] -
			aMatrix.myData[13] * aMatrix.myData[2] * aMatrix.myData[11] +
			aMatrix.myData[13] * aMatrix.myData[3] * aMatrix.myData[10];

		inv[5] = aMatrix.myData[0] * aMatrix.myData[10] * aMatrix.myData[15] -
			aMatrix.myData[0] * aMatrix.myData[11] * aMatrix.myData[14] -
			aMatrix.myData[8] * aMatrix.myData[2] * aMatrix.myData[15] +
			aMatrix.myData[8] * aMatrix.myData[3] * aMatrix.myData[14] +
			aMatrix.myData[12] * aMatrix.myData[2] * aMatrix.myData[11] -
			aMatrix.myData[12] * aMatrix.myData[3] * aMatrix.myData[10];

		inv[9] = -aMatrix.myData[0] * aMatrix.myData[9] * aMatrix.myData[15] +
			aMatrix.myData[0] * aMatrix.myData[11] * aMatrix.myData[13] +
			aMatrix.myData[8] * aMatrix.myData[1] * aMatrix.myData[15] -
			aMatrix.myData[8] * aMatrix.myData[3] * aMatrix.myData[13] -
			aMatrix.myData[12] * aMatrix.myData[1] * aMatrix.myData[11] +
			aMatrix.myData[12] * aMatrix.myData[3] * aMatrix.myData[9];

		inv[13] = aMatrix.myData[0] * aMatrix.myData[9] * aMatrix.myData[14] -
			aMatrix.myData[0] * aMatrix.myData[10] * aMatrix.myData[13] -
			aMatrix.myData[8] * aMatrix.myData[1] * aMatrix.myData[14] +
			aMatrix.myData[8] * aMatrix.myData[2] * aMatrix.myData[13] +
			aMatrix.myData[12] * aMatrix.myData[1] * aMatrix.myData[10] -
			aMatrix.myData[12] * aMatrix.myData[2] * aMatrix.myData[9];

		inv[2] = aMatrix.myData[1] * aMatrix.myData[6] * aMatrix.myData[15] -
			aMatrix.myData[1] * aMatrix.myData[7] * aMatrix.myData[14] -
			aMatrix.myData[5] * aMatrix.myData[2] * aMatrix.myData[15] +
			aMatrix.myData[5] * aMatrix.myData[3] * aMatrix.myData[14] +
			aMatrix.myData[13] * aMatrix.myData[2] * aMatrix.myData[7] -
			aMatrix.myData[13] * aMatrix.myData[3] * aMatrix.myData[6];

		inv[6] = -aMatrix.myData[0] * aMatrix.myData[6] * aMatrix.myData[15] +
			aMatrix.myData[0] * aMatrix.myData[7] * aMatrix.myData[14] +
			aMatrix.myData[4] * aMatrix.myData[2] * aMatrix.myData[15] -
			aMatrix.myData[4] * aMatrix.myData[3] * aMatrix.myData[14] -
			aMatrix.myData[12] * aMatrix.myData[2] * aMatrix.myData[7] +
			aMatrix.myData[12] * aMatrix.myData[3] * aMatrix.myData[6];

		inv[10] = aMatrix.myData[0] * aMatrix.myData[5] * aMatrix.myData[15] -
			aMatrix.myData[0] * aMatrix.myData[7] * aMatrix.myData[13] -
			aMatrix.myData[4] * aMatrix.myData[1] * aMatrix.myData[15] +
			aMatrix.myData[4] * aMatrix.myData[3] * aMatrix.myData[13] +
			aMatrix.myData[12] * aMatrix.myData[1] * aMatrix.myData[7] -
			aMatrix.myData[12] * aMatrix.myData[3] * aMatrix.myData[5];

		inv[14] = -aMatrix.myData[0] * aMatrix.myData[5] * aMatrix.myData[14] +
			aMatrix.myData[0] * aMatrix.myData[6] * aMatrix.myData[13] +
			aMatrix.myData[4] * aMatrix.myData[1] * aMatrix.myData[14] -
			aMatrix.myData[4] * aMatrix.myData[2] * aMatrix.myData[13] -
			aMatrix.myData[12] * aMatrix.myData[1] * aMatrix.myData[6] +
			aMatrix.myData[12] * aMatrix.myData[2] * aMatrix.myData[5];

		inv[3] = -aMatrix.myData[1] * aMatrix.myData[6] * aMatrix.myData[11] +
			aMatrix.myData[1] * aMatrix.myData[7] * aMatrix.myData[10] +
			aMatrix.myData[5] * aMatrix.myData[2] * aMatrix.myData[11] -
			aMatrix.myData[5] * aMatrix.myData[3] * aMatrix.myData[10] -
			aMatrix.myData[9] * aMatrix.myData[2] * aMatrix.myData[7] +
			aMatrix.myData[9] * aMatrix.myData[3] * aMatrix.myData[6];

		inv[7] = aMatrix.myData[0] * aMatrix.myData[6] * aMatrix.myData[11] -
			aMatrix.myData[0] * aMatrix.myData[7] * aMatrix.myData[10] -
			aMatrix.myData[4] * aMatrix.myData[2] * aMatrix.myData[11] +
			aMatrix.myData[4] * aMatrix.myData[3] * aMatrix.myData[10] +
			aMatrix.myData[8] * aMatrix.myData[2] * aMatrix.myData[7] -
			aMatrix.myData[8] * aMatrix.myData[3] * aMatrix.myData[6];

		inv[11] = -aMatrix.myData[0] * aMatrix.myData[5] * aMatrix.myData[11] +
			aMatrix.myData[0] * aMatrix.myData[7] * aMatrix.myData[9] +
			aMatrix.myData[4] * aMatrix.myData[1] * aMatrix.myData[11] -
			aMatrix.myData[4] * aMatrix.myData[3] * aMatrix.myData[9] -
			aMatrix.myData[8] * aMatrix.myData[1] * aMatrix.myData[7] +
			aMatrix.myData[8] * aMatrix.myData[3] * aMatrix.myData[5];

		inv[15] = aMatrix.myData[0] * aMatrix.myData[5] * aMatrix.myData[10] -
			aMatrix.myData[0] * aMatrix.myData[6] * aMatrix.myData[9] -
			aMatrix.myData[4] * aMatrix.myData[1] * aMatrix.myData[10] +
			aMatrix.myData[4] * aMatrix.myData[2] * aMatrix.myData[9] +
			aMatrix.myData[8] * aMatrix.myData[1] * aMatrix.myData[6] -
			aMatrix.myData[8] * aMatrix.myData[2] * aMatrix.myData[5];

		T det = aMatrix.myData[0] * inv[0] + aMatrix.myData[1] * inv[4] + aMatrix.myData[2] * inv[8] + aMatrix.myData[3] * inv[12];

		//if (det == 0)
		//	return false;

		det = T(1.0) / det;

		Matrix4x4<T> returnMatrix;
		for (int i = 0; i < 16; i++)
		{
			returnMatrix[i] = inv[i] * det;
		}

		return returnMatrix;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::GetInverse(const Matrix4x4<T>& aMatrix, const T& aDeterminant)
	{
		T inv[16];

		inv[0] =
			aMatrix.myData[5] * aMatrix.myData[10] * aMatrix.myData[15] -
			aMatrix.myData[5] * aMatrix.myData[11] * aMatrix.myData[14] -
			aMatrix.myData[9] * aMatrix.myData[6] * aMatrix.myData[15] +
			aMatrix.myData[9] * aMatrix.myData[7] * aMatrix.myData[14] +
			aMatrix.myData[13] * aMatrix.myData[6] * aMatrix.myData[11] -
			aMatrix.myData[13] * aMatrix.myData[7] * aMatrix.myData[10];

		inv[4] = -aMatrix.myData[4] * aMatrix.myData[10] * aMatrix.myData[15] +
			aMatrix.myData[4] * aMatrix.myData[11] * aMatrix.myData[14] +
			aMatrix.myData[8] * aMatrix.myData[6] * aMatrix.myData[15] -
			aMatrix.myData[8] * aMatrix.myData[7] * aMatrix.myData[14] -
			aMatrix.myData[12] * aMatrix.myData[6] * aMatrix.myData[11] +
			aMatrix.myData[12] * aMatrix.myData[7] * aMatrix.myData[10];

		inv[8] = aMatrix.myData[4] * aMatrix.myData[9] * aMatrix.myData[15] -
			aMatrix.myData[4] * aMatrix.myData[11] * aMatrix.myData[13] -
			aMatrix.myData[8] * aMatrix.myData[5] * aMatrix.myData[15] +
			aMatrix.myData[8] * aMatrix.myData[7] * aMatrix.myData[13] +
			aMatrix.myData[12] * aMatrix.myData[5] * aMatrix.myData[11] -
			aMatrix.myData[12] * aMatrix.myData[7] * aMatrix.myData[9];

		inv[12] = -aMatrix.myData[4] * aMatrix.myData[9] * aMatrix.myData[14] +
			aMatrix.myData[4] * aMatrix.myData[10] * aMatrix.myData[13] +
			aMatrix.myData[8] * aMatrix.myData[5] * aMatrix.myData[14] -
			aMatrix.myData[8] * aMatrix.myData[6] * aMatrix.myData[13] -
			aMatrix.myData[12] * aMatrix.myData[5] * aMatrix.myData[10] +
			aMatrix.myData[12] * aMatrix.myData[6] * aMatrix.myData[9];

		inv[1] = -aMatrix.myData[1] * aMatrix.myData[10] * aMatrix.myData[15] +
			aMatrix.myData[1] * aMatrix.myData[11] * aMatrix.myData[14] +
			aMatrix.myData[9] * aMatrix.myData[2] * aMatrix.myData[15] -
			aMatrix.myData[9] * aMatrix.myData[3] * aMatrix.myData[14] -
			aMatrix.myData[13] * aMatrix.myData[2] * aMatrix.myData[11] +
			aMatrix.myData[13] * aMatrix.myData[3] * aMatrix.myData[10];

		inv[5] = aMatrix.myData[0] * aMatrix.myData[10] * aMatrix.myData[15] -
			aMatrix.myData[0] * aMatrix.myData[11] * aMatrix.myData[14] -
			aMatrix.myData[8] * aMatrix.myData[2] * aMatrix.myData[15] +
			aMatrix.myData[8] * aMatrix.myData[3] * aMatrix.myData[14] +
			aMatrix.myData[12] * aMatrix.myData[2] * aMatrix.myData[11] -
			aMatrix.myData[12] * aMatrix.myData[3] * aMatrix.myData[10];

		inv[9] = -aMatrix.myData[0] * aMatrix.myData[9] * aMatrix.myData[15] +
			aMatrix.myData[0] * aMatrix.myData[11] * aMatrix.myData[13] +
			aMatrix.myData[8] * aMatrix.myData[1] * aMatrix.myData[15] -
			aMatrix.myData[8] * aMatrix.myData[3] * aMatrix.myData[13] -
			aMatrix.myData[12] * aMatrix.myData[1] * aMatrix.myData[11] +
			aMatrix.myData[12] * aMatrix.myData[3] * aMatrix.myData[9];

		inv[13] = aMatrix.myData[0] * aMatrix.myData[9] * aMatrix.myData[14] -
			aMatrix.myData[0] * aMatrix.myData[10] * aMatrix.myData[13] -
			aMatrix.myData[8] * aMatrix.myData[1] * aMatrix.myData[14] +
			aMatrix.myData[8] * aMatrix.myData[2] * aMatrix.myData[13] +
			aMatrix.myData[12] * aMatrix.myData[1] * aMatrix.myData[10] -
			aMatrix.myData[12] * aMatrix.myData[2] * aMatrix.myData[9];

		inv[2] = aMatrix.myData[1] * aMatrix.myData[6] * aMatrix.myData[15] -
			aMatrix.myData[1] * aMatrix.myData[7] * aMatrix.myData[14] -
			aMatrix.myData[5] * aMatrix.myData[2] * aMatrix.myData[15] +
			aMatrix.myData[5] * aMatrix.myData[3] * aMatrix.myData[14] +
			aMatrix.myData[13] * aMatrix.myData[2] * aMatrix.myData[7] -
			aMatrix.myData[13] * aMatrix.myData[3] * aMatrix.myData[6];

		inv[6] = -aMatrix.myData[0] * aMatrix.myData[6] * aMatrix.myData[15] +
			aMatrix.myData[0] * aMatrix.myData[7] * aMatrix.myData[14] +
			aMatrix.myData[4] * aMatrix.myData[2] * aMatrix.myData[15] -
			aMatrix.myData[4] * aMatrix.myData[3] * aMatrix.myData[14] -
			aMatrix.myData[12] * aMatrix.myData[2] * aMatrix.myData[7] +
			aMatrix.myData[12] * aMatrix.myData[3] * aMatrix.myData[6];

		inv[10] = aMatrix.myData[0] * aMatrix.myData[5] * aMatrix.myData[15] -
			aMatrix.myData[0] * aMatrix.myData[7] * aMatrix.myData[13] -
			aMatrix.myData[4] * aMatrix.myData[1] * aMatrix.myData[15] +
			aMatrix.myData[4] * aMatrix.myData[3] * aMatrix.myData[13] +
			aMatrix.myData[12] * aMatrix.myData[1] * aMatrix.myData[7] -
			aMatrix.myData[12] * aMatrix.myData[3] * aMatrix.myData[5];

		inv[14] = -aMatrix.myData[0] * aMatrix.myData[5] * aMatrix.myData[14] +
			aMatrix.myData[0] * aMatrix.myData[6] * aMatrix.myData[13] +
			aMatrix.myData[4] * aMatrix.myData[1] * aMatrix.myData[14] -
			aMatrix.myData[4] * aMatrix.myData[2] * aMatrix.myData[13] -
			aMatrix.myData[12] * aMatrix.myData[1] * aMatrix.myData[6] +
			aMatrix.myData[12] * aMatrix.myData[2] * aMatrix.myData[5];

		inv[3] = -aMatrix.myData[1] * aMatrix.myData[6] * aMatrix.myData[11] +
			aMatrix.myData[1] * aMatrix.myData[7] * aMatrix.myData[10] +
			aMatrix.myData[5] * aMatrix.myData[2] * aMatrix.myData[11] -
			aMatrix.myData[5] * aMatrix.myData[3] * aMatrix.myData[10] -
			aMatrix.myData[9] * aMatrix.myData[2] * aMatrix.myData[7] +
			aMatrix.myData[9] * aMatrix.myData[3] * aMatrix.myData[6];

		inv[7] = aMatrix.myData[0] * aMatrix.myData[6] * aMatrix.myData[11] -
			aMatrix.myData[0] * aMatrix.myData[7] * aMatrix.myData[10] -
			aMatrix.myData[4] * aMatrix.myData[2] * aMatrix.myData[11] +
			aMatrix.myData[4] * aMatrix.myData[3] * aMatrix.myData[10] +
			aMatrix.myData[8] * aMatrix.myData[2] * aMatrix.myData[7] -
			aMatrix.myData[8] * aMatrix.myData[3] * aMatrix.myData[6];

		inv[11] = -aMatrix.myData[0] * aMatrix.myData[5] * aMatrix.myData[11] +
			aMatrix.myData[0] * aMatrix.myData[7] * aMatrix.myData[9] +
			aMatrix.myData[4] * aMatrix.myData[1] * aMatrix.myData[11] -
			aMatrix.myData[4] * aMatrix.myData[3] * aMatrix.myData[9] -
			aMatrix.myData[8] * aMatrix.myData[1] * aMatrix.myData[7] +
			aMatrix.myData[8] * aMatrix.myData[3] * aMatrix.myData[5];

		inv[15] = aMatrix.myData[0] * aMatrix.myData[5] * aMatrix.myData[10] -
			aMatrix.myData[0] * aMatrix.myData[6] * aMatrix.myData[9] -
			aMatrix.myData[4] * aMatrix.myData[1] * aMatrix.myData[10] +
			aMatrix.myData[4] * aMatrix.myData[2] * aMatrix.myData[9] +
			aMatrix.myData[8] * aMatrix.myData[1] * aMatrix.myData[6] -
			aMatrix.myData[8] * aMatrix.myData[2] * aMatrix.myData[5];

		T det = aDeterminant;

		//if (det == 0)
		//	return false;

		det = T(1.0) / det;

		Matrix4x4<T> returnMatrix;
		for (int i = 0; i < 16; i++)
		{
			returnMatrix[i] = inv[i] * det;
		}

		return returnMatrix;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse(const Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T> inv = aMatrix;

		auto t1 = aMatrix.myRows[0].Dot(aMatrix.myRows[3]);
		auto t2 = aMatrix.myRows[1].Dot(aMatrix.myRows[3]);
		auto t3 = aMatrix.myRows[2].Dot(aMatrix.myRows[3]);

		inv.myRows[3] = { 0,0,0,1 };

		inv = Transpose(inv);
		inv.myRows[3] = { -t1, -t2, -t3, 1 };
		return inv;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateTranslateMatrix(const Vector3<T>& aPos)
	{
		Matrix4x4<T> m;
		m.GetRow(4) = { aPos.x, aPos.y, aPos.z, 1 };

		return m;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationMatrix(const RotationAxis& anAxis, const T someValueInRadians)
	{
		switch (anAxis)
		{
		case RotationAxis::X:
			Matrix4x4<T> m;
			m(2, 2) = std::cos(someValueInRadians);
			m(2, 3) = std::sin(someValueInRadians);
			m(3, 2) = -std::sin(someValueInRadians);
			m(3, 3) = std::cos(someValueInRadians);
			return m;
		case RotationAxis::Y:
			Matrix4x4<T> m;
			m(1, 1) = std::cos(someValueInRadians);
			m(1, 3) = -std::sin(someValueInRadians);
			m(3, 1) = std::sin(someValueInRadians);
			m(3, 3) = std::cos(someValueInRadians);
			return m;
		case RotationAxis::Z:
			Matrix4x4<T> m;
			m(1, 1) = std::cos(someValueInRadians);
			m(1, 2) = std::sin(someValueInRadians);
			m(2, 1) = -std::sin(someValueInRadians);
			m(2, 2) = std::cos(someValueInRadians);
			return m;
		default:
			break;
		}

		return Matrix4x4<T>();
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationMatrix(const Vector3<T>& aPichYawRoll)
	{
		Matrix4x4<T> m;
		Vector4<T> quaternion;
		{//TODO: Move quaternion stuff to its own class - Spyro

			T cy = std::cos(aPichYawRoll.y * T(0.5));
			T sy = std::sin(aPichYawRoll.y * T(0.5));
			T cr = std::cos(aPichYawRoll.z * T(0.5));
			T sr = std::sin(aPichYawRoll.z * T(0.5));
			T cp = std::cos(aPichYawRoll.x * T(0.5));
			T sp = std::sin(aPichYawRoll.x * T(0.5));

			quaternion.w = cy * cr * cp + sy * sr * sp;
			quaternion.x = cy * sr * cp - sy * cr * sp;
			quaternion.y = cy * cr * sp + sy * sr * cp;
			quaternion.z = sy * cr * cp - cy * sr * sp;

		}

		T qxx(quaternion.y * quaternion.y);
		T qyy(quaternion.z * quaternion.z);
		T qzz(quaternion.w * quaternion.w);

		T qxz(quaternion.y * quaternion.w);
		T qxy(quaternion.y * quaternion.z);
		T qyz(quaternion.z * quaternion.w);

		T qwx(quaternion.x * quaternion.y);
		T qwy(quaternion.x * quaternion.z);
		T qwz(quaternion.x * quaternion.w);

		m.myRows[0].x = T(1) - T(2) * (qyy + qzz);
		m.myRows[0].y = T(2) * (qxy + qwz);
		m.myRows[0].z = T(2) * (qxz - qwy);

		m.myRows[1].x = T(2) * (qxy - qwz);
		m.myRows[1].y = T(1) - T(2) * (qxx + qzz);
		m.myRows[1].z = T(2) * (qyz + qwx);

		m.myRows[2].x = T(2) * (qxz + qwy);
		m.myRows[2].y = T(2) * (qyz - qwx);
		m.myRows[2].z = T(1) - T(2) * (qxx + qyy);

		m.myArray[0][3] = m.myArray[1][3] = m.myArray[2][3] = 0;
		m.myArray[3][3] = 1;

		return m;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateScaleMatrix(const Vector3<T>& aScale)
	{
		Matrix4x4<T> m;
		m(1, 1) = aScale.x;
		m(2, 2) = aScale.y;
		m(3, 3) = aScale.z;
		return m;
	}

	template<typename T>
	inline T& Matrix4x4<T>::operator()(const uint32_t aRow, const uint32_t aCollum)
	{
		uint32_t row = aRow - 1;
		uint32_t collum = aCollum - 1;

		assert(row >= 0 && row < 4 && "Invalid index");
		assert(collum >= 0 && collum < 4 && "Invalid index");
		return myArray[aRow - 1][aCollum - 1];
	}

	template<typename T>
	inline Vector4<T>& Matrix4x4<T>::GetRow(const uint32_t anIndex)
	{
		uint32_t i = anIndex + 1;
		assert(i >= 0 && i < 4 && "Invalid index");
		return myRows[i];
	}

	template<typename T>
	inline Matrix4x4<T>::Matrix4x4()
	{
		myRows[0] = { 1,0,0,0 };
		myRows[1] = { 0,1,0,0 };
		myRows[2] = { 0,0,1,0 };
		myRows[3] = { 0,0,0,1 };
	}

	template<typename T>
	inline Matrix4x4<T>::Matrix4x4(const T someData[16])
	{
		myArray = someData;
	}

	template<typename T>
	inline Matrix4x4<T>::Matrix4x4(const Vector4<T> someRows[4])
	{
		myRows = someRows;
	}

	template<typename T>
	inline Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& aMatrix)
	{
		memcpy(myData, aMatrix.myData, sizeof(myData));
	}

	template<typename T>
	inline Matrix4x4<T>::Matrix4x4(Matrix4x4<T>&& aMatrix)
	{
		for (size_t i = 0; i < 16; i++)
		{
			memcpy(myArray[i], aMatrix.myArray[i], sizeof(T));
		}
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4<T>& aMatrix)
	{
		//Open.AI Bot answer: Needs some validation but should work - Spyro
		Matrix4x4<T> m;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m.myArray[i][j] = myArray[i][j] + aMatrix.myArray[i][j];
			}
		}


		return m;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4<T>& aMatrix)
	{
		//Open.AI Bot answer: Needs some validation but should work - Spyro
		Matrix4x4<T> m;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m.myArray[i][j] = myArray[i][j] - aMatrix.myArray[i][j];
			}
		}


		return m;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T>& aMatrix)
	{
		//Open.AI Bot answer: Needs validation - Spyro
		Matrix4x4<T> m;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m.myArray[i][j] = 0;
				for (int k = 0; k < 4; k++)
				{
					m.myArray[i][j] += myArray[i][k] * aMatrix.myArray[k][j];
				}
			}
		}

		return m;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::operator/(const Matrix4x4<T>& aMatrix)
	{

		//Open.AI Bot answer: Needs validation - Spyro
		//Basically, instead of dividing, im taking the inverse of the input matrix 
		//then multiplying the current matrix with the inverse of the input to get an approximation of division.
		Matrix4x4<T> m;
		Matrix4x4<T> invMatrix;

		T det = Determinant(aMatrix); //Get the deternimant of the input.
		invMatrix = Matrix4x4<T>::GetInverse(aMatrix, det); //Get the inverse of the input.
		m = *this * invMatrix; //multiply current with inverse of input.

		return m;
	}

	template<typename T>
	inline void Matrix4x4<T>::operator+=(const Matrix4x4<T>& aMatrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				myArray[i][j] = myArray[i][j] + aMatrix.myArray[i][j];
			}
		}
	}

	template<typename T>
	inline void Matrix4x4<T>::operator-=(const Matrix4x4<T>& aMatrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				myArray[i][j] = myArray[i][j] - aMatrix.myArray[i][j];
			}
		}
	}

	template<typename T>
	inline void Matrix4x4<T>::operator*=(const Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T> m;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m.myArray[i][j] = 0;
				for (int k = 0; k < 4; k++)
				{
					m.myArray[i][j] += myArray[i][k] * aMatrix.myArray[k][j];
				}
			}
		}


		myData = memcpy(myData, m.myData, sizeof(myData));
	}

	template<typename T>
	inline void Matrix4x4<T>::operator/=(const Matrix4x4<T>& aMatrix)
	{
		//Open.AI Bot answer: Needs validation - Spyro
		//Basically, instead of dividing, im taking the inverse of the input matrix 
		//then multiplying the current matrix with the inverse of the input to get an approximation of division.
		Matrix4x4<T> m;
		Matrix4x4<T> invMatrix;

		T det = Determinant(aMatrix); //Get the deternimant of the input.
		invMatrix = Matrix4x4<T>::GetInverse(aMatrix, det); //Get the inverse of the input.
		m = *this * invMatrix; //multiply current with inverse of input.


		myData = memcpy(myData, m.myData, sizeof(myData));
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::operator=(const Matrix4x4<T>& aMatrix)
	{
		memcpy(myData, aMatrix.myData, sizeof(myData));
		return *this;
	}

	template<typename T>
	inline const bool Matrix4x4<T>::operator==(const Matrix4x4<T>& aMatrix)
	{
		return std::memcmp(myData, aMatrix.myData, sizeof(16));
	}

	template<typename T>
	inline const bool Matrix4x4<T>::operator!=(const Matrix4x4<T>& aMatrix)
	{
		return !std::memcmp(myData, aMatrix.myData, sizeof(16));;
	}



	template<typename T>
	inline void Matrix4x4<T>::Decompose(const Matrix4x4<T>& aMatrix, Vector3<T>& aPos, Vector3<T>& aRot, Vector3<T>& aSize)
	{
		const Matrix4x4<T>& mat = aMatrix;
		Vector4f scaleX = { mat(1,1),mat(1,2) ,mat(1,3) ,mat(1,4) };
		Vector4f scaleY = { mat(2,1),mat(2,2) ,mat(2,3) ,mat(2,4) };
		Vector4f scaleZ = { mat(3,1),mat(3,2) ,mat(3,3) ,mat(3,4) };

		aSize.x = scaleX.Length();
		aSize.y = scaleY.Length();
		aSize.z = scaleZ.Length();

		scaleX.Normalize();
		scaleY.Normalize();
		scaleZ.Normalize();

		aRot.x = atan2f(scaleY.z, scaleZ.z);
		aRot.y = atan2f(-scaleX.z, sqrtf(scaleY.z * scaleY.z + scaleZ.z * scaleZ.z));
		aRot.z = atan2f(scaleX.y, scaleX.x);

		aPos.x = mat.GetPosition().x;
		aPos.y = mat.GetPosition().y;
		aPos.z = mat.GetPosition().z;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::TRS(const Vector3<T>& aPos, const Vector3<T>& aRot, const Vector3<T>& aSize)
	{
		Matrix4x4<T> m;

		m = CreateScaleMatrix(aSize) * Matrix4x4<T>::CreateRotationMatrix(aRot) * CreateTranslateMatrix(aPos) * m;

		return m;
	}

	template<typename T>
	inline Vector3<T> Matrix4x4<T>::Forward()
	{
		auto forward = GetRow(3);
		return Vector3<T>(forward.x, forward.y, forward.z);
	}

	template<typename T>
	inline Vector3<T> Matrix4x4<T>::Up()
	{
		auto up = GetRow(2);
		return Vector3<T>(up.x, up.y, up.z);
	}

	template<typename T>
	inline Vector3<T> Matrix4x4<T>::Right()
	{
		auto right = GetRow(1);
		return Vector3<T>(right.x, right.y, right.z);
	}

	template<typename T>
	inline void Matrix4x4<T>::SetPosition(const Vector3<T>& aVector3)
	{
		Vector4<T>& pos = GetRow(4);
		pos.x = aVector3.x;
		pos.y = aVector3.y;
		pos.z = aVector3.z;
	}

	template<typename T>
	inline void Matrix4x4<T>::SetSize(const Vector3<T>& aVector3)
	{
		myArray[0][0] = aVector3.x;
		myArray[1][1] = aVector3.y;
		myArray[2][2] = aVector3.z;
	}

	template<typename T>
	inline void Matrix4x4<T>::SetRotation(const Vector3<T>& aVector3)
	{
		ResetRotation();
		*this *= Matrix4x4<T>::CreateRotationMatrix(aVector3);
	}

	template<typename T>
	inline void Matrix4x4<T>::ResetRotation()
	{
		myArray[1][1] = 1;
		myArray[1][2] = 0;
		myArray[2][1] = 0;
		myArray[2][2] = 1;
		myArray[0][0] = 1;
		myArray[0][2] = 0;
		myArray[2][0] = 0;
		myArray[0][1] = 0;
		myArray[1][0] = 0;
	}

	template<typename T>
	inline Vector3<T> Matrix4x4<T>::GetPosition()
	{
		Vector3<T>& pos = GetRow(4);
		return Vector3<T>(pos.x, pos.y, pos.z);
	}

	template<typename T>
	inline Vector3<T> Matrix4x4<T>::GetSize()
	{
		return Vector3<T>(*this(1, 1), *this(2, 2), *this(3, 3));
	}

	template<typename T>
	inline Vector3<T> Matrix4x4<T>::GetRotation()
	{
		Vector3<T> pos, size, rot;
		Decompose(pos, rot, size);
		return rot;
	}

	typedef Matrix4x4<float> Matrix4x4f;

}