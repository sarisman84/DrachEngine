#pragma once
#include <cstdint>
#include <stdlib.h> 
namespace drach
{
	// Helper function to convert float to uint32_t
	union FloatIntConverter
	{
		float f;
		std::uint32_t i;
	};

	// Fast Inverse Square Root function
	float invSqrt(float x) {
		FloatIntConverter converter;
		float x2;
		const float threehalfs = 1.5f;
		converter.f = x;
		x2 = x * 0.5f;
		std::uint32_t i = converter.i; //convert the type to be a uint32_t but keep the byte structure the same
		i = 0x5f3759df - (i >> 1); //-> Fetch the value of an adress and half it by bit shifting itself.
		converter.i = i; //convert the type back to a decimal.
		converter.f = converter.f * (threehalfs - (x2 * converter.f * converter.f));//newtons method; 1st iteration
		converter.f = converter.f * (threehalfs - (x2 * converter.f * converter.f));//newtons method; 2st iteration

		return converter.f;
	}




	float frac(float x) { return x - (int)x; }
	float mod(float x, float m) { return frac(x / m) * m; }
	float uMod(float x, float m) { return mod(mod(x, m) + m, m); }
	int ceilToInt(float x) { return (int)x + 1; }

	void clamp(float& val, const float min, const float max) {
		val = min > val ? min : val;//the compile is (hopefully) smart enough to make this branchless
		val = max < val ? max : val;
	}


	//NOTE: assuming the floating point structure to be IEEE 754 standard
	float rnd_01f() {//make a random binary string and put it in the fraction part of a float
		static const unsigned int fractionMask = ((1 << 23) - 1);
		static const unsigned int Exp0 = 127 << 23;//an exponent of 0

		unsigned int rnd = rand() | (rand() << 15);//use 2 times the random function to extend the random number
		rnd &= fractionMask;//only use the bits in the fraction part of a float
		rnd |= Exp0;//set the exponent to 1

		float rndF = *((float*)&rnd);//use the bits to construct a float
		return rndF - 1.0f;//rndF is in range from 2^0 to 2^1 -> range 1 to 2;
	}
	//EXPANSION: signed floats -> make the exponent 1, by using (128 << 23), then the range will be 2 to 4 and by subtracting 3 you can optain a signed float between -1 and 1


	float rndRange(float min, float max) { return rnd_01f() * (max - min) + min; }





}