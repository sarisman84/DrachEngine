#pragma once
#include <unordered_map>
#include <vector>

template<typename KeyT, typename ValT>
class SMap//a sparse set, but with any type as key type (basically works like unordered map, but the ValueTypes are stored in contigous memory)	
{
private:
	std::unordered_map<KeyT, int> sparse; // To store indexes of actual elements
	std::vector<KeyT> invSparse;		  // To go from index back to the Key (only really needed for deletion)		NOTE: should always have the same size as dense[]
	std::vector<ValT> dense;			  // To store actual set elements

public:
	SMap(int cap = 0) : 
		sparse(cap), invSparse(cap), dense(cap) {}

	~SMap() {}


	// If element is present, returns index of element in dense[]. Else returns -1.
	int search(const KeyT& key) const {
		auto itr = sparse.find(key);
		if (itr == sparse.end())//didnt find any
			return -1;
		return itr->second;
	}
	inline bool contains(const KeyT& key) const { return search(key) != -1; }

	// Inserts a new element into set
	void insert(const KeyT& key, const ValT& val) {
		if (contains(key))//do not allow duplicate keys
			return;

		sparse[key] = dense.size();//connect the key to the next dense index
		invSparse.push_back(key);//also connect the inverse
		dense.push_back(val);//store the value at the next dense index
	}

	// Deletes an element
	void erase(const KeyT& key) {
		int idx = search(key);
		if (idx == -1)//cant delete what doesnt exist
			return;

		int last = dense.size() - 1;
		dense[idx] = std::move(dense[last]);//move the last element back
		invSparse[idx] = std::move(invSparse[last]);
		sparse[invSparse[last]] = idx;//make the key that pointed to n-1 now point to idx

		//delete stuff
		sparse.erase(key);
		dense.erase(dense.end() - 1);
		invSparse.erase(invSparse.end() - 1);
	}

	// Prints contents of set
	void print() const {
		for (int i = 0; i < dense.size(); i++)
			std::cout << dense[i] << ", ";
			//printf("%d ", dense[i]);
		printf("\n");
	}

	// Removes all elements from set
	void clear() {
		sparse.clear();
		invSparse.clear();
		dense.clear();
	}

	ValT& operator[](const KeyT& key) {
		return dense[sparse[key]];
	}

	// Finds intersection of this set with s and returns pointer to result.
	//SMap* intersection(SMap& s);

	// A function to find union of two sets Time Complexity-O(n1+n2)
	//SMap* setUnion(SMap& s);
};

