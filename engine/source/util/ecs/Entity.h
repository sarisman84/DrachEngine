#include <cstdint>
#pragma once


namespace drach
{
	namespace ecs
	{
		typedef uint32_t EntityIndex; //32 
		typedef uint32_t EntityVersion; //32
		typedef unsigned long long Entity; //Summary of Index and Version

		inline Entity nullentity = Entity(-1); //Invalid Entity
	}
}
