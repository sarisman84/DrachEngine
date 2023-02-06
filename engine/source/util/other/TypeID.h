#pragma once
#include <cstdint>

namespace drach
{

	static inline uint32_t GetID()
	{
		static uint32_t id;
		return id++;
	}

	template<typename T>
	struct TypeID
	{
		inline static uint32_t id = GetID();
	};
}