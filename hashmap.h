
#ifndef HASHMAP_H
#define HASHMAP_H

#include <cstddef>
#include <stdexcept>

template<class K, class V>
class Map
{
    virtual bool insert(K key, V value) = 0;
    virtual bool remove(K key) = 0;
    virtual V get(K key) = 0;
    virtual bool modify(K key, V value) = 0;
};

template<class K, class V, class F>
class OHashMap : public Map<K, V>
{
public:
    struct Element
    {
        K key;
        V value;
        Element *next{ nullptr };

        Element(K k, V v) : key(k), value(v) {};
    };

private:
    static const int DEFAULT_TABLE_SIZE = 101;

    size_t _size;

    Element **_table;

    F hashFunction;

    unsigned hash(K key)
    {
        return hashFunction(key) % _size;
    }

    // other methods
    Element** searchChain(K key, unsigned hashValue);

public:
    // Constructors
    OHashMap() : _size(DEFAULT_TABLE_SIZE), _table(nullptr) {};
    OHashMap(size_t size);

    // Hashmap methods
    bool insert(K key, V value) override;
    bool remove(K key) override;
    V get(K key) override;
    bool modify(K key, V value) override;
};

template<class K, class V, class F>
typename OHashMap<K, V, F>::Element** OHashMap<K, V, F>::searchChain(K key, unsigned hashValue) 
{
    Element *current = _table[hashValue];
    Element *prev = nullptr;
    if (current == nullptr)
        return nullptr;

    while (current->next != nullptr)
    {
        if (current->key == key) {
            Element **e = new Element*[2];
            e[0] = current;
            e[1] = prev;
            return e;
        }
        prev = current;
        current->next = current;
    }
    return nullptr;
}

template<class K, class V, class F>
bool OHashMap<K, V, F>::insert(K key, V value)
{
    unsigned hashValue = hash(key);
    if(searchChain(key, hashValue) != nullptr)
    {
        return false;
    }
    Element *e = new Element(key, value);
    e->next = _table[hashValue];
    _table[hashValue] = e;
    return true;
}

template<class K, class V, class F>
V OHashMap<K, V, F>::get(K key)
{
    unsigned hashValue = hash(key);
    Element **arr = searchChain(key, hashValue);

    if (arr == nullptr) {
        throw std::out_of_range("HashMap: key doesn't exists");
    }

    return (arr[0])->value;
}

template<class K, class V, class F>
bool OHashMap<K, V, F>::remove(K key)
{
    return false;
}

template<class K, class V, class F>
bool OHashMap<K, V, F>::modify(K key, V value)
{
    return false;
}

// constructors

template<class K, class V, class F>
OHashMap<K, V, F>::OHashMap(size_t size)
{
    _table = new Element*[size];

    for (unsigned i = 0; i < size; i++) {
        _table[i] = nullptr;
    }
}

#endif