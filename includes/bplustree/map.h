#ifndef MAP_H
#define MAP_H
#include <cassert>
#include <iostream>
#include <iomanip>
#include "../../includes/bplustree/btree_array_funcs.h"
#include "../../includes/bplustree/bplustree.h"
using namespace std;

template <typename K, typename V>
struct Pair
{
    K key;
    V value;

    Pair(const K &k = K(), const V &v = V())
    {
        key = k;
        value = v;
    }
    friend ostream &operator<<(ostream &outs, const Pair<K, V> &print_me)
    {
        outs << print_me.key << ":" << print_me.value;
        return outs;
    }
    friend bool operator==(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator<(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key < rhs.key;
    }
    friend bool operator>(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key > rhs.key;
    }
    friend bool operator<=(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key <= rhs.key;
    }
    friend Pair<K, V> operator+(const Pair<K, V> &lhs, const Pair<K, V> &rhs) // data[i] + entry
    {
        return rhs;
    }
};

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V>> map_base;
    class Iterator
    {
    public:
        friend class Map;
        Iterator(typename map_base::Iterator it = typename map_base::Iterator())
        {
            _it = it;
        }
        Iterator operator++(int unused)
        {
            Iterator temp = _it;
            _it++;
            return temp;
        }
        Iterator operator++()
        {
            _it++;
            return this;
        }
        Pair<K, V> operator*()
        {
            return *_it;
        }
        friend bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs._it == rhs._it;
        }
        friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs._it != rhs._it;
        }

    private:
        typename map_base::Iterator _it;
    };

    Map();
    //  Iterators
    Iterator begin();
    Iterator end();

    //  Capacity
    int size() const;
    bool empty() const;

    //  Element Access
    V &operator[](const K &key);
    V &at(const K &key);
    const V &at(const K &key) const;

    //  Modifiers
    void insert(const K &k, const V &v);
    void erase(const K &key);
    void clear();
    V get(const K &key);

    //  Operations:
    Iterator find(const K &key)
    {
        return Iterator(map.find(key));
    }
    bool contains(const Pair<K, V> &target) const;

    // I have not writtent hese yet, but we will need them:
    int count(const K &key)
    {
        Iterator it;
        while (it = begin(), it != end(), it++)
        {
            key_count++;
        }
        return key_count;
    }
    Iterator lower_bound(const K &key)
    {
        Iterator it = map.end();
        for (it = map.begin(); it != map.end(); it++)
        {
            if (*it > key)
            {
                return it;
            }
            if (*it == key)
            {
                return it;
            }
        }
        return it;
    }
    Iterator upper_bound(const K &key)
    {
        Iterator it = map.end();
        for (it = map.begin(); it != map.end(); it++)
        {
            if (*it > key)
            {
                return it;
            }
        }
        return it;
    }
    int equal_range(const K &key)
    {
        return -1;
    }

    bool is_valid() { return map.is_valid(); }

    friend ostream &operator<<(ostream &outs, const Map<K, V> &print_me)
    {
        outs << print_me.map << endl;
        return outs;
    }

private:
    int key_count;
    BPlusTree<Pair<K, V>> map;
};

template <typename K, typename V>
Map<K, V>::Map()
{
    key_count = 0;
}

// Iterators
template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::begin()
{
    return map.begin();
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::end()
{
    return map.end();
}

//  Capacity
template <typename K, typename V>
int Map<K, V>::size() const
{
    return map.size();
}

template <typename K, typename V>
bool Map<K, V>::empty() const
{
    // Iterator walker;
    // for (walker = begin(); walker != end(); walker++)
    // {
    //     key_count++;
    // }

    if (key_count == 0)
    {
        return true;
    }
    return false;
}

//  Element Access
template <typename K, typename V>
V &Map<K, V>::operator[](const K &key)
{
    bool debug = true;
    if (debug)
    {
        // cout << "In [] op" << endl;
    }
    return at(key);
}
template <typename K, typename V>
V &Map<K, V>::at(const K &key)
{
    // cout << "calling at" << endl;
    return map.get(key).value;
}
template <typename K, typename V>
const V &Map<K, V>::at(const K &key) const
{
    return map.get(key).value;
}

//  Modifiers
template <typename K, typename V>
void Map<K, V>::insert(const K &k, const V &v)
{
    map.insert(Pair<K, V>(k, v));
}
template <typename K, typename V>
void Map<K, V>::erase(const K &key)
{
}
template <typename K, typename V>
void Map<K, V>::clear()
{
    map.clear_tree();
}

template <typename K, typename V>
V Map<K, V>::get(const K &key)
{
    // cout << "calling get(maps)" << endl;

    return map.get(key).value;
}

//  Operations: //I moved this up
// template <typename K, typename V>
// typename Map<K, V>::Iterator find(const K &key)
// {
//     return Iterator(map.find(key));
// }

template <typename K, typename V>
bool Map<K, V>::contains(const Pair<K, V> &target) const
{
    return map.contains(target);
}
#endif
