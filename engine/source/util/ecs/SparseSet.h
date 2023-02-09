#pragma once
#include <cstdint>
#include <memory>
namespace drach
{
	template<typename T>
	class sparseSet
	{
	public:
		sparseSet(const uint32_t aCapacity = 10);
		~sparseSet();
		T& operator[](const uint32_t anIndex);
		void insert(const T& anElement);
		const bool erase(const uint32_t anIndex);
		const bool erase(const T& anElement);
		const bool contains(const T& anElement);
		const uint32_t findIndex(const T& anElement);
		void clear();
		const uint32_t size() const;
		void reserve(const uint32_t aCustomSize = uint32_t(-1));
	private:

	private:
		uint32_t* mySparseIndex;
		uint32_t* myDenseIndex;
		T** myDataContainer;
		uint32_t myCount;
		uint32_t myDataIndex;
		uint32_t myDenseCapacity;
		uint32_t mySparseSize;
	};


	template<typename T>
	inline sparseSet<T>::sparseSet(const uint32_t aCapacity)
	{
		myDenseCapacity = aCapacity;
		mySparseSize = aCapacity * 2;

		mySparseIndex = new uint32_t[mySparseSize];
		myDenseIndex = new uint32_t[myDenseCapacity];
		myDataContainer = new T[myDenseCapacity];

		myCount = 0;
		myDataIndex = 0;
	}
	template<typename T>
	inline sparseSet<T>::~sparseSet()
	{
		delete[] mySparseIndex;
		delete[] myDenseIndex;
		delete[] myDataContainer;
	}
	template<typename T>
	inline T& sparseSet<T>::operator[](const uint32_t anIndex)
	{
		return *myDataContainer[myDenseIndex[mySparseIndex[anIndex]]];
	}
	template<typename T>
	inline void sparseSet<T>::insert(const T& anElement)
	{
		if (myCount >= myDenseCapacity)
			reserve(myDenseCapacity * 2);

		myDenseIndex[myCount] = myDataIndex;
		mySparseIndex[myDataIndex] = myCount;
		myDataContainer[myDataIndex] = new T(anElement)

			myCount++;
		myDataIndex++;


	}
	template<typename T>
	inline const bool sparseSet<T>::erase(const uint32_t anIndex)
	{
		delete myDataContainer[mySparseIndex[anIndex]];

		uint32_t temp = myDenseIndex[myCount - 1];
		myDenseIndex[mySparseIndex[anIndex]] = temp;
		mySparseIndex[temp] = mySparseIndex[anIndex];

		myCount--;

		return true;
	}
	template<typename T>
	inline const bool sparseSet<T>::erase(const T& anElement)
	{
		uint32_t foundIndex = findIndex(anElement);

		if (foundIndex != uint32_t(-1))
			return false;

		return drach::sparseSet<T>::erase(foundIndex);
	}
	template<typename T>
	inline const bool sparseSet<T>::contains(const T& anElement)
	{
		return findIndex(anElement) != uint32_t(-1);
	}
	template<typename T>
	inline const uint32_t sparseSet<T>::findIndex(const T& anElement)
	{
		for (size_t i = 0; i < myCount; ++i)
		{
			if (myDataContainer[i] == anElement)
				return mySparseIndex[i];
		}
		return uint32_t(-1);
	}
	template<typename T>
	inline void sparseSet<T>::clear()
	{
		myCount = 0;
		delete[] myDataContainer;
		myDataContainer = new T[myDenseCapacity];
	}
	template<typename T>
	inline const uint32_t sparseSet<T>::size() const
	{
		return myCount;
	}
	template<typename T>
	inline void sparseSet<T>::reserve(const uint32_t aCustomSize)
	{
		if (aCustomSize <= myCount) return;

		uint32_t* newDenseContainer = new uint32_t[aCustomSize];
		T* newMirrorContainer = new T[aCustomSize];

		memcpy(newDenseContainer, myDenseIndex, myCount * sizeof(uint32_t));
		memcpy(newMirrorContainer, myDataContainer, myCount * sizeof(T));

		delete[] myDenseIndex;
		delete[] myDataContainer;

		myDenseIndex = newDenseContainer;
		myDataContainer = newMirrorContainer;

		myDenseCapacity = aCustomSize;

	}
}