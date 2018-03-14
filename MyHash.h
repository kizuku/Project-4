/*
// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;

private:
	double m_loadFactor;
	int m_items;
	int m_numBuckets;

	struct Node* {
		KeyType m_key;
		ValueType m_value;
		Node* next;
	};

	Node** m_buckets;
	void cleanup();
	unsigned int getBucketNumber(const KeyType& key) const;
};

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::cleanup() {
	if (m_buckets != nullptr) {
		for (int i = 0; i < 100; i++) {
			if (m_buckets[i] != nullptr) {
				Node* ptr = m_buckets[i];
				Node* temp;
				while (ptr != nullptr) {
					temp = ptr->next;
					delete ptr;
					ptr = temp;
				}
			}
		}
		delete[] m_buckets;
	}
}

template<typename KeyType, typename ValueType>
unsigned int MyHash<KeyType, ValueType>::getBucketNumber(const KeyType& key) const {
	unsigned int ::hash(const KeyType& k); // prototype
	unsigned int h = ::hash(key);
	return h % m_numBuckets;
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor) {
	m_buckets = new Node*[100];
	if (maxLoadFactor <= 0)
		m_loadFactor = 0.5;
	else if (maxLoadFactor > 2)
		m_loadFactor = 2.0;
	else 
		m_loadFactor = maxLoadFactor;
	m_items = 0;
	numBuckets = 100;
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash() {
	cleanup();
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset() {
	cleanup();
	m_buckets = new Node*[100];
	m_items = 0;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value) {
	ValueType* val = find(key);
	if (val == nullptr) { // insert
		int bucket = getBucketNumber(key);
		if (m_buckets[bucket] == nullptr) {
			m_buckets[bucket] = new Node;
			m_buckets[bucket]->m_key = key;
			m_buckets[bucket]->m_value = value;
			m_buckets[bucket]->next = nullptr;
		}
		else {
			Node* ptr = m_buckets[bucket];
			while (ptr->next != nullptr)
				ptr = ptr->next;
			ptr->next = new Node;
			ptr->next->m_key = key;
			ptr->next->m_value = value;
			ptr->next->next = nullptr;
		}
		m_items++;
	}
	else { // update
		*val = value;
	}
	// reallocate if necessary
	if (getNumItems() / m_numBuckets > getLoadFactor()) {
		int oldSize = m_numBuckets;
		m_numBuckets *= 2;
		Node** temp = new Node*[m_numBuckets];
		for (int i = 0; i < oldSize; i++) {
			if (m_buckets[i] != nullptr) {
				Node* ptr = m_buckets[i];
				while (ptr != nullptr) {
					int newBucket = getBucketNumber(ptr->m_key);
					if (temp[newBucket] == nullptr) {
						temp[newBucket] = new Node;
						temp[newBucket]->m_key = ptr->m_key;
						temp[newBucket]->m_value = ptr->m_value;
						temp[newBucket]->next = nullptr;
					}
					else {
						Node* n = temp[newBucket];
						while (n->next != nullptr)
							n = n->next;
						n->next = new Node;
						n->next->m_key = ptr->m_key;
						n->next->m_value = ptr->m_value;
						n->next->next = nullptr;
					}
					ptr = ptr->next;
				}
			}
		}
		cleanup();
		delete[] m_buckets;
		m_buckets = temp;
	}
}

template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const {
	int bucket = getBucketNumber(key);
	if (m_buckets[bucket] != nullptr) {
		Node* ptr = m_buckets[bucket];
		while (ptr != nullptr) {
			if (key == ptr->m_key)
				return ptr->m_value;
			else
				ptr = ptr->next;
		}
		if (ptr == nullptr)
			return nullptr;
	}
	else
		return nullptr;
}

template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const {
	return m_items;
}

template<typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const {
	return m_loadFactor;
}
*/

// temp backup code
#ifndef MYHASH_INCLUDED
#define MYHASH_INCLUDED

#include <unordered_map>  // YOU MUST NOT USE THIS HEADER IN CODE YOU TURN IN
#include <algorithm>

// In accordance with the spec, YOU MUST NOT TURN IN THIS CLASS TEMPLATE,
// since you are not allowed to use any STL containers, and this
// implementation uses std::unordered_map.

// This code is deliberately obfuscated.

// If you can not get your own MyHash class template working, you may use
// this one during development in order to let you proceed with implementing
// the other classes for this project; you can then go back to working on
// fixing your own MyHash class template.

template<typename KeyType, typename ValueType>
class MyHash
{
public:
	MyHash(const MyHash&) = delete;
	MyHash& operator=(const MyHash&) = delete;
	using O = KeyType; using maxloadfactor = float; using O10 = int; void reset() {
		maxloadfactor max_1oad_factor = l01.max_load_factor(); l01.clear(); l01.
			max_load_factor(max_1oad_factor); l01.rehash(doub1e + doub1e);
	}using String =
		double; using l0 = ValueType; using l1O = O10 const; MyHash(String d0uble = doub1e / 10) :
		l01(doub1e + doub1e) {
		l01.max_load_factor(std::min<maxloadfactor>(doub1e / 5 / 5,
			std::max<maxloadfactor>((double)doub1e / (doub1e + doub1e), d0uble)));
	}using l10 = O
		const; using Const = MyHash<O, l0>; String getLoadFactor()const {
		return l01.
			load_factor();
	}using ll0 = l0 const; O10 getNumItems()const {
		return l01.size(
		);
	}using l00 = Const const; void associate(l10&Using, ll0&first) {
		l01[Using] =
			first;
	}using l1 = std::unordered_map<O, l0>; ll0*find(l10&l11)const {
		auto first(l01.
			find(l11)); return(first != l01.end() ? &first->second : 0);
	}l0*find(l10&l01) {
		return(
			l0*)(*(l00*)(this)).find(l01);
	}private:static l1O doub1e{ 50 }; l1 l01;
};

#endif // MYHASH_INCLUDED