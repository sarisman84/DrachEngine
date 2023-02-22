#pragma once

#include <string>
#include <functional>

namespace drach
{
	struct StringID
	{
		size_t myID;

		StringID()
		{
			myID = size_t(-1);
		}
		StringID(const std::string& aStr)
		{
			myID = std::hash<std::string_view>()(aStr);
		}

		StringID(const char* aStr)
		{
			myID = std::hash<std::string_view>()(aStr);
		}

		StringID(const StringID& someOther)
		{
			myID = someOther.myID;
		}

		StringID(StringID&& someOther) noexcept
		{
			myID = someOther.myID;
		}

		StringID operator=(const StringID& someOther)
		{
			myID = someOther.myID;
			return *this;
		}

		StringID operator=(StringID&& someOther) noexcept
		{
			myID = someOther.myID;
			return *this;
		}

		bool operator==(const StringID& other) const {
			return myID == other.myID;
		}

		bool operator!=(const StringID& other) const {
			return myID != other.myID;
		}

		bool operator <(const StringID& other) const
		{
			return myID < other.myID;
		}


		bool operator >(const StringID& other) const
		{
			return myID > other.myID;
		}
	};


	struct StringIDHash
	{
		std::size_t operator()(const StringID& id) const
		{
			return id.myID;
		}
	};

}