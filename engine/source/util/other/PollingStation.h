#pragma once
#include <unordered_map>
#include <memory>
#include "Object.h"
#include "TypeID.h"
namespace drach
{
	class PollingStation
	{
	public:
		template<typename T>
		void Register(T& aPtr)
		{
			myData[TypeID<T>().id] = static_cast<void*>(&aPtr);
		}

		template<typename T>
		T* Get()
		{
			return static_cast<T*>(myData[TypeID<T>().id]);
		}

	private:
		std::unordered_map<uint32_t, void*> myData;
	};
}