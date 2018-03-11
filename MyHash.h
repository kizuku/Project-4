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
	return h % 100;
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
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash() {
	cleanup();
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::reset() {
	cleanup();
	m_buckets = new Node*[100];
	m_items = 0;
}

// what if 2 diff words have same key?
template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value) {
	ValueType* val = find(key);
	if (val == nullptr) { // insert
		int bucket = getBucketNumber(key);
		m_buckets[bucket] = new Node(key, value);
		m_items++;
	}
	else { // update
		*val = value;
	}
}

// needs to be implemented
template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const {
	int bucket = getBucketNumber(key);
	if (m_buckets[bucket] != nullptr)
		return m_buckets[bucket];
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
