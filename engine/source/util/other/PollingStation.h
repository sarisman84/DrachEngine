#pragma once
#include <unordered_map>
#include <memory>
#include "Object.h"
#include "TypeID.h"
namespace drach
{
	template<typename T>
	struct PtrObject : public BaseObject
	{
		T* myData = nullptr;
	};

	class PollingStation
	{
	public:
		template<typename T>
		T*& Get()
		{
			if (myData.count(TypeID<T>::id) <= 0)
			{
				myData[TypeID<T>::id] = std::make_shared<PtrObject<T>>();
			}


			return myData[TypeID<T>::id]->As<PtrObject<T>>().myData;

		}

	private:
		std::unordered_map<uint32_t, std::shared_ptr<BaseObject>> myData;
	};
}