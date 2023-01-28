#pragma once
namespace drach
{
	struct BaseObject
	{
		template<typename Type>
		Type& As()
		{
			return *static_cast<Type*>(this);
		}
	};


	template<typename Value>
	struct Object : public BaseObject
	{
		Value myData;
	};

}