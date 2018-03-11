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

	struct Node* {
		ValueType m_value;
		Node* next;
	};
	Node** m_buckets;
};

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor) {
	m_buckets = new Node*[100];
	if (maxLoadFactor <= 0)
		m_loadFactor = 0.5;
	else if (maxLoadFactor > 2)
		m_loadFactor = 2.0;
	else 
		m_loadFactor = maxLoadFactor;
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash() {
	delete[] m_buckets;
}
